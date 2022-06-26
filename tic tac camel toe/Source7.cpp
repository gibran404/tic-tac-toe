
//working 3x3, stuck on 4x4
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class TicTac
{
    enum class Player//stores the possible states of a grid in the board
    {
        blank = ' ',
        P1 = 'O',
        P2 = 'X'
    };

    struct Move //stores x,y cordinates which are used by the minimax algorithm for determining the computer's turn location
    {
        int x = 0;
        int y = 0;
    };

    const int size = 3; //constant size used because variable size for some reason doesnt work with the algorithm
    Player board[3][3]; //2d array for the board itself
    int remMoves;   //counts total moves left until no more moves can be done
    int P1score;
    int P2score;
    int drawscore;
    bool DualPlayer; //used for deciding between player vs player or player vs ai

public:
    TicTac()
    {
        remMoves = size * size; //total number of moves is square of size of one side
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
    void reset()//resets the board so the game can be played again
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
        do//asks user for input for deciding SinglePlayer or DualPlayer
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
        do //runs if user wants to play more than once
        {
            play();
            cout << "\n Play again?(y/n) ";
            cin >> choice;
        } while (choice == 'y');
    }
    void play()//The main part of the game which calls all the functions in order to play the game
    {
        bool turn = false; //switches between turns of the players
        bool breaker = false; //switch is flipped when a win/lose/draw condition is come across
        reset();//resets the board for each run of the game
        printBoard();

        do //
        {
            if (turn == false)
            {
                DualPlayer == true ? cout << "P1 Move: " : cout << "Your Move: ";
                getHumanMove(Player::P1); //runs for taking the input cordiantes from the user
                printBoard();
                remMoves--; //at each turn of the game, the remaining moves are decreased
                if (checkWin(Player::P1))//if P1 wins, their score is increased and the breaker is flipped
                {
                    P1score++;  
                    cout << "P1 wins! \n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tP2 Wins: " << P2score << endl;
                    breaker = true;
                }
            }
            else if (DualPlayer == true)//runs for DualPlayer, where the ai is replaced by an input by the user
            {
                cout << "P2 Move: ";
                getHumanMove(Player::P2); //runs for taking the input cordiantes from the user
                printBoard();
                remMoves--;
                if (checkWin(Player::P2))//if P2 wins, their score is increased and the breaker is flipped
                {
                    P2score++;
                    cout << "P2 wins! \n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tP2 Wins: " << P2score << endl;
                    breaker = true;
                }
            }
            else if (DualPlayer == false)//runs for SinglePlayer where P2 is the computer
            {
                cout << "\nComputer Move: ";

                Move aimove = minimax();    //minimax algorithm is called which return a Move datatype which stores the x,y cordinates where the ai should do it's turn

                cout << aimove.x << aimove.y << "\n";

                board[aimove.x][aimove.y] = Player::P2; //the board is updated
                printBoard();
                remMoves--;
                if (checkWin(Player::P2)) //if Computer wins, it's score is increased and the breaker is flipped
                {
                    P2score++;
                    cout << "Computer Wins\n";
                    cout << "Draws: " << drawscore << "\tP1 Wins: " << P1score << "\tComputer Wins: " << P2score << endl;
                    breaker = true;
                }
            }

            if (isTie())//if a tie is rached, the drawscore is increased and the breaker is flipped
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

            turn = !turn; //after wach turn, the turn is switched for the other player

        } while (!breaker);//runs till the breaker is flipped which would mean an ending condition is reached
    }

    void printBoard()//prints the whole board at it's current condition
    {
        system("CLS");
        //loop for printing vertically line by line
        for (int ver = 0; ver < size; ver++)
        {
            //vv set of loops that print each box of the board horizontally vv
            for (int hor = 0; hor < size; hor++)//prints the first line of each box
            {
                cout << "     ";
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;
            for (int hor = 0; hor < size; hor++) // prints the spaces and the columns in the secong line depending on the size of the board
            {
                cout << "  " << static_cast<char>(board[ver][hor]) << "  ";
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;
            for (int hor = 0; hor < size; hor++)//prints the 3rd line with the cordinate of each box.
            {
                cout << "   " << ver << hor;
                if (hor != size - 1)
                    cout << "||";
            }
            cout << endl;

            if (ver != size - 1)
            {
                for (int hor = 0; hor < size; hor++)//prints the 4th line which is the dashes
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

    bool checkWin(Player player)//checks if there are any of the winning conditions in the current state of the board
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
    void getHumanMove(Player player)//takes input cordinates from the user to put the input of the player in that spot on the board
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
