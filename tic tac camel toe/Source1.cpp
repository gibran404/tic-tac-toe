
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits> 

using namespace std;

class Game
{
    enum class Player  //Pre Defined Values for Human, AI and Blanks
    {
        none = ' ',
        human = 'X',
        computer = 'O'
    };

    struct Move //Keeping score
    {
        int x = 0;
        int y = 0;
    };

    Player board[3][3];
    int size;
    int movnum;

public:
    /*
    Game(int s)
    {
        board = new Player[s];
        for (int x = 0; x < s; x++)
        {
            board[x] = new Player[s];
        }
    }
    */
    Game()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = Player::none; //Initializes as '-' on the board
            }
        }
    }
  

    void printBoard()
    {
        /*
        system("CLS");
        cout << "+-----------------+";
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            for (int j = 0; j < 3; j++)
            {
                cout << setw(3) << static_cast<char>(board[i][j]); // Used for conversion of an integer based display to a character based display to be more in line with our enumarated class  
                cout << setw(3) << " |";
            }
        }
        cout << endl << "+-----------------+" << endl;
        */
        int loc = 0;
        system("CLS");
        cout << endl;
        for (int x = 0; x < 3; x++)
        {
            cout << "       |     |     \n";

            for (int y = 0; y < 3; y++)
            {
                if (y == 0)
                    cout << "  ";
                cout << "  " << static_cast<char>(board[x][y]);
                if (y == 2)
                {
                    cout << endl;
                }
                else
                    cout << "  |";
            }
            cout << "      " << ++loc << "|    ";
            cout << ++loc << "|   ";
            cout << ++loc << endl;
            if (x != 2)
                cout << "  =====|=====|=====" << endl;
        }
    }

    bool isTie()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }//bool isTie() const { return available == 0; } Better way, don't know jack shit on how to implement it properly though.

    bool checkWin(Player player)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;

            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }

        // Check diagonals. Need to implement a formula soon.
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    Move minimax()
    {
        int score = numeric_limits<int>::max(); //Used to keep the score in check for a value that could go over
        Move move;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;

                    int temp = maxSearch();

                    if (temp < score)
                    {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }

        return move;
    }

    //Need to understand how this properly works. Fast ka senior sonay chala gaya tha
    int maxSearch()
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::human;
                    score = max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        return score;
    }

    int minSearch()
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    score = min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        return score;
    }

    void getHumanMove()
    {
        /*
        bool fail = true;
        int x = -1, y = -1;

        do
        {
            cout << "Your Move: ";

            char c;
            cin >> c;
            x = c - '0';
            cin >> c;
            y = c - '0';

            fail = board[x][y] != Player::none;

            cin.clear();
            cin.ignore(::numeric_limits<streamsize>::max(), '\n'); //Sets the maximum number of characters to ignore.

        } while (fail);

        board[x][y] = Player::human;
        */
        int loc;
        do
        {   
            cout << "Your Move: ";
            cin >> loc;
        } while (loc < 1 || loc >9);

        if (loc == 1)
            board[0][0] = Player::human;
        else if (loc == 2)
            board[0][1] = Player::human;
        else if (loc == 3)
            board[0][2] = Player::human;
        else if (loc == 4)
            board[1][0] = Player::human;
        else if (loc == 5)
            board[1][1] = Player::human;
        else if (loc == 6)
            board[1][2] = Player::human;
        else if (loc == 7)
            board[2][0] = Player::human;
        else if (loc == 8)
            board[2][1] = Player::human;
        else if (loc == 9)
            board[2][2] = Player::human;
        else
        {
            cout << "wrong input";
            cin >> loc;
        }
    }

    void play()
    {
        int turn = 0;

        printBoard();
        cout << "Enter your move in coordinate form[row, col]. ex: 02" << endl;

        do
        {
            // human move
            if (turn % 2 ==0)
            {
                getHumanMove();
                printBoard();

                if (checkWin(Player::human))
                {
                    cout << "You shouldn't be able to win, this code has a problem" << endl;
                    break;
                }
            }
            else if (turn % 2 !=0)
            {
                cout << endl;
                cout << "Computer Move: ";

                Move aimove = minimax();
                cout << aimove.x << aimove.y << endl;
                board[aimove.x][aimove.y] = Player::computer;
                printBoard();
                if (checkWin(Player::computer))
                {
                    cout << "Computer Wins" << endl;
                    break;
                }
            }
            if (isTie())
            {
                cout << endl << "* Tie *" << endl;
                break;
            }

            turn++;

        } while (turn<9);//for dynamic (turn < s*s)
    }
};

int main()
{
    Game tictactoe;
    tictactoe.play();
    system("pause");
}