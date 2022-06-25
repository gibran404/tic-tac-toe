
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class TicTac
{
    enum class Player
    {
        blank = ' ',
        P1 = 'O',
        P2 = 'X'
    };
    struct Move
    {
        int x = 0;
        int y = 0;
    };
    int size;
    int P1score;
    int P2score;
    int drawscore;
    bool DualPlayer;
    Player board[3][3];//3 size by default
    int remMoves;
public:
    TicTac()//dualplayer is assigned in cunstructor
    {
        size = 3;
        P1score = 0;
        drawscore = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = Player::blank;
            }
        }
    }
    void Menu()
    {
        cout << "\t\tTIC TAC TOE GAME\n";
        cout << "\n\t     Made by Hanan and Momin\n\n";
        cout << "\n   Enter 1 for SinglePlayer and 2 for DualPlayer\n";
        int choice;
        do
        {
            cin >> choice;

            if (choice == 1)
                DualPlayer = false;
            else if (choice == 2)
                DualPlayer = true;
            else
                cout << "Wrong input, enter again\n";
        } while (choice != 1 && choice != 2);
    }

    void play()
    {
        bool turn = 0;
        bool breaker = false;
        Menu();
        printBoard();
        do
        {
            if (turn == 0)
            {
                getHumanMove();
                remMoves--;
                if (checkWin(Player::P1))
                {
                    P1score++;
                    cout << "P1 wins! \n";
                    breaker = true;
                }
            }
            else if (DualPlayer == true)//runs for DualPlayer
            {
                getHumanMove();
                remMoves--;
                if (checkWin(Player::P2))
                {
                    P1score++;
                    cout << "P2 wins! \n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tP2 Wins: " << P2score;
                    breaker = true;
                }
            }
            else if (DualPlayer == false)//runs for SinglePlayer
            {
                cout << "\nComputer Move: ";

                Move aimove = minimax();

                cout << aimove.x << aimove.y << "\n";

                board[aimove.x][aimove.y] = Player::P2;
                remMoves--;
                if (checkWin(Player::P2))
                {
                    P2score++;
                    cout << "Computer Wins\n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tComputer Wins: " << P2score;
                    breaker = true;
                }
            }

            if (isTie())
            {
                drawscore++;
                cout << "\n" << "* Tie *\n";        
                cout << "Draws: " << drawscore << "\tP1 Win: " << P1score;
                if (DualPlayer == true)
                    cout << "\tP2 Wins: ";
                else
                    cout << "Computer Wins: ";

                cout << P2score << endl;
                breaker = true;
            }

            turn = !turn;
            printBoard();

        } while (!breaker);
    }

    void printBoard()
    {
        system("CLS");
        //loop for printing vertically line by line
        for (int ver = 0; ver < size; ver++)
        {
            //vv set of loops that print each box of the board horizontally vv
            for (int hor = 0; hor < size; hor++)
            {
                cout << "     ";
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;
            for (int hor = 0; hor < size; hor++)
            {
                cout << "  " << static_cast<char>(board[ver][hor]) << "  ";
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;
            for (int hor = 0; hor < size; hor++)
            {
                cout << "   " << ver << hor;
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;

            if (ver != size - 1)
            {
                for (int hor = 0; hor < size; hor++)
                {
                    cout << "=====";
                    if (hor != size - 1)
                        cout << "||";
                }
                cout << endl;
            }
        }
    }

    bool isTie()
    {
        return remMoves == 0; //Basically if (Empty Tiles == 0) {return == true}
    }

    bool occupied(int x, int y, Player player)
    {
        if (board[x][y] == player)
            return true;
        else
            return false;
    }

    bool checkWin(Player player)
    {
        //for column and rows checking
        for (int i = 0; i < size; ++i)
        {
            bool rowwin = true;
            bool colwin = true;
            for (int j = 0; j < size; ++j)
            {
                rowwin &= board[i][j] == player;
                colwin &= board[j][i] == player;
            }
            if (colwin || rowwin)
                return true;
        }

        // check for diagonal wins
        bool diagonalwin = true;
        for (int i = 0; i < size; ++i)
            diagonalwin &= board[i][i] == player;

        if (diagonalwin)
            return true;

        diagonalwin = true;

        for (int i = 0; i < size; ++i)
            diagonalwin &= board[size - i - 1][i] == player;

        return diagonalwin;
    }

    Move minimax()
    {
        int score = numeric_limits<int>::max();
        Move move;
        int level = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == Player::blank)
                {
                    board[i][j] = Player::P2;
                    remMoves--;

                    int temp = maxSearch(level, numeric_limits<int>::min(), numeric_limits<int>::max()); //Type Casting done to avoid problems with limits on int.

                    if (temp < score)
                    {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }

                    board[i][j] = Player::blank;
                    remMoves++;
                }
            }
        }

        return move;
    }

    int maxSearch(int level, int alpha, int beta) //Alpha Beta Pruning to help with the Tree implementation.
    {
        int rem = remMoves;
        if (checkWin(Player::P1)) { return 10; }

        else if (checkWin(Player::P2)) { return -10; }

        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::min();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == Player::blank)
                {
                    board[i][j] = Player::P1;
                    rem--; //Checks through the remaining blocks

                    score = max(score, minSearch(level + 1, alpha, beta) - level);
                    alpha = max(alpha, score);

                    board[i][j] = Player::blank;
                    rem++;

                    if (beta <= alpha) { return alpha; }
                }
            }
        }

        return score;
    }

    int minSearch(int level, int alpha, int beta)
    {
        int rem = remMoves;
        if (checkWin(Player::P1)) { return 10; }

        else if (checkWin(Player::P2)) { return -10; }

        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::max();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == Player::blank)
                {
                    board[i][j] = Player::P2;
                    rem--;

                    score = min(score, maxSearch(level + 1, alpha, beta) + level);
                    beta = min(beta, score);

                    board[i][j] = Player::blank;
                    rem++;

                    if (beta <= alpha) return beta;
                }
            }
        }
        return score;
    }

    void getHumanMove()
    {
        bool fail = true;
        unsigned x = -1, y = -1;

        do
        {
            cout << "Your Move: ";

            char c;
            cin >> c;
            x = c - '0';
            cin >> c;
            y = c - '0';

            fail = board[x][y] != Player::blank;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (fail);

        board[x][y] = Player::P1;
        //remMoves--;
    }
};
  
int main()
{
    TicTac tictactoe;
    tictactoe.play();
    system("pause");
}
