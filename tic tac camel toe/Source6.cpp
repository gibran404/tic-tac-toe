
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

    const int size = 3; //Constexpr used to Make the expression constant on start. Don't know why the fuck normal ways don't work. Also, due to nest loops and recursion the code is slow af on 6 r&c.
    Player board[3][3];
    int remMoves;
    int P1score;
    int P2score;
    int drawscore;
    bool DualPlayer;

public:
    TicTac()
    {
        remMoves = size * size;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = Player::blank;
            }
        }
        P1score = 0;
        P2score = 0;
        drawscore = 0;
    }
    void reset()
    {
        remMoves = size * size;
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
        cout << "\n\t  ****************************\n";
        cout << "\t\tTIC TAC TOE GAME\n";
        cout << "\t  ****************************\n";

        cout << "\n\n\t     Made by Hanan and Momin\n\n";
        cout << "\n\n\n   Enter 1 for SinglePlayer and 2 for DualPlayer\n";
        int type;
        do
        {
            cin >> type;
            if (type == 1)
                DualPlayer = false;
            else if (type == 2)
                DualPlayer = true;
            else
                cout << "Wrong input, enter again\n";
        } while (type != 1 && type != 2);

        char choice = 'y';
        do
        {
            play();
            cout << "\n Playe again?(y/n) ";
            cin >> choice;
        } while (choice == 'y');
    }
    void play()
    {
        bool turn = false;
        bool breaker = false;
        reset();
        printBoard();
        do
        {
            if (turn == false)
            {
                DualPlayer == true ? cout << "P1 Move: " : cout << "Your Move: ";
                getHumanMove(Player::P1);
                printBoard();
                remMoves--;
                if (checkWin(Player::P1))
                {
                    P1score++;
                    cout << "P1 wins! \n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tP2 Wins: " << P2score << endl;
                    breaker = true;
                }
            }
            else if (DualPlayer == true)//runs for DualPlayer
            {
                cout << "P2 Move: ";
                getHumanMove(Player::P2);
                printBoard();
                remMoves--;
                if (checkWin(Player::P2))
                {
                    P2score++;
                    cout << "P2 wins! \n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tP2 Wins: " << P2score << endl;
                    breaker = true;
                }
            }
            else if (DualPlayer == false)//runs for SinglePlayer
            {
                cout << "\nComputer Move: ";

                Move aimove = minimax();

                cout << aimove.x << aimove.y << "\n";

                board[aimove.x][aimove.y] = Player::P2;
                printBoard();
                remMoves--;
                if (checkWin(Player::P2))
                {
                    P2score++;
                    cout << "Computer Wins\n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tComputer Wins: " << P2score << endl;
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
                    cout << "\tComputer Wins: ";

                cout << P2score << endl;
                breaker = true;
            }

            turn = !turn;

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
    void getHumanMove(Player player)
    {
        bool fail = true;
        unsigned x = -1, y = -1;

        do
        {
            char c;
            cin >> c;
            x = c - '0';
            cin >> c;
            y = c - '0';

            fail = board[x][y] != Player::blank;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (fail);

        board[x][y] = player;
        //remMoves--;
    }
};

int main()
{
    TicTac tictactoe;
    tictactoe.Menu();
    system("pause");
}
