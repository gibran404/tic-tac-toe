#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class Game
{
    enum class Player
    {
        blank = ' ',
        person = '0',
        algorithm = 'X'
    };

    struct Move
    {
        int x = 0;
        int y = 0;
    };
    int size;
    //static constexpr int size = 3; //Constexpr used to Make the expression constant on start. Don't know why the fuck normal ways don't work. Also, due to nest loops and recursion the code is slow af on 6 r&c.
    //Player** board = new Player*[size];
    Player** board;
    int remMoves;
     
public:
    Game(int size = 3)
    {
        this->size = size;
        remMoves = size * size;
        
        board = new Player*[size];
        for (int i = 0; i < size; i++)
        {
            board[i] = new Player[size];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = Player::blank;
            }
        }
    }

    void play()
    {
        bool turn = true;
        bool breaker = false;

        printBoard();

        do
        {
            //Human Turn
            if (turn == true)
            {
                getHumanMove();
                remMoves--;
                //Useless because Humans will never win.
                if (checkWin(Player::person))
                {
                    cout << "You win! \n"; //If they do win, sue me.
                    breaker = true;
                }
            }
            else
            {
                cout << "\nComputer Move: ";

                Move aimove = minimax();

                cout << aimove.x << aimove.y << "\n";

                board[aimove.x][aimove.y] = Player::algorithm;
                remMoves--;
                if (checkWin(Player::algorithm))
                {
                    cout << "Computer Wins\n";
                    breaker = true;
                }
            }

            if (isTie())
            {
                cout << "\n" << "* Tie *\n";
                breaker = true;
            }

            turn = false;
            printBoard();

        } while (!breaker);
    }

private:
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
        /*
        for (int i = 0; i < coordinate; i++)
        {
            cout << "\n|";
            for (unsigned j = 0; j < coordinate; j++)
            {
                cout << setw(3) << static_cast<char>(board[i][j]) << setw(3) << " |";
            }
        }
        cout << "\n\n";
        */
    }

    bool isTie()
    {
        return remMoves == 0; //Basically if (Empty Tiles == 0) {return == true}
    }

    bool checkWin(Player player)
    {
        // check for row or column wins
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
                    board[i][j] = Player::algorithm;
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
        if (checkWin(Player::person)) { return 10; }

        else if (checkWin(Player::algorithm)) { return -10; }

        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::min();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == Player::blank)
                {
                    board[i][j] = Player::person;
                    remMoves--; //Checks through the remaining blocks

                    score = max(score, minSearch(level + 1, alpha, beta) - level);
                    alpha = max(alpha, score);

                    board[i][j] = Player::blank;
                    remMoves++;

                    if (beta <= alpha) { return alpha; }
                }
            }
        }

        return score;
    }

    int minSearch(int level, int alpha, int beta)
    {
        if (checkWin(Player::person)) { return 10; }

        else if (checkWin(Player::algorithm)) { return -10; }

        else if (isTie()) { return 0; }

        int score = numeric_limits<int>::max();

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == Player::blank)
                {
                    board[i][j] = Player::algorithm;
                    remMoves--;

                    score = min(score, maxSearch(level + 1, alpha, beta) + level);
                    beta = min(beta, score);

                    board[i][j] = Player::blank;
                    remMoves++;

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

        board[x][y] = Player::person;
        remMoves--;
    }
};

int main()
{
    Game tictactoe(3);
    tictactoe.play();
    system("pause");
}