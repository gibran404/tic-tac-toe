/*
* 
#include <iostream>
#include <stdlib.h>
#include <conio.h>


using namespace std;

class TICTACTOE
{
    char board[3][3];
public:
    TICTACTOE()
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                board[x][y] = ' ';
            }
        }
    }
    void empty()
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                board[x][y] = ' ';
            }
        }
    }
    void printboard()
    {
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
                cout << "  " << board[x][y];
                if (y == 2)
                {
                    cout << endl;
                }
                else
                    cout << "  |";
            }
                    board[0][2] = 'X';
                else if (loc == 4)
                    board[1][0] = 'X';
                else if (loc == 5)
                    board[1][1] = 'X';
                else if (loc == 6)
                    board[1][2] = 'X';
                else if (loc == 7)
            cout << "      " << ++loc << "|    ";
            cout << ++loc << "|   ";
            cout << ++loc << endl;
            if (x != 2)
                cout << "  =====|=====|=====" << endl;
        }
    }
    void input(char turn, int loc)
    {
            if (turn == 'X')
            {
                if (loc == 1)
                    board[0][0] = 'X';
                else if (loc == 2)
                    board[0][1] = 'X';
                else if (loc == 3)
                    board[2][0] = 'X';
                else if (loc == 8)
                    board[2][1] = 'X';
                else if (loc == 9)
                    board[2][2] = 'X';
                else
                {
                    cout << "wrong input";
                    cin >> loc;
                }
            }
            if (turn == 'O')
            {
                if (loc == 1)
                    board[0][0] = 'O';
                else if (loc == 2)
                    board[0][1] = 'O';
                else if (loc == 3)
                    board[0][2] = 'O';
                else if (loc == 4)
                    board[1][0] = 'O';
                else if (loc == 5)
                    board[1][1] = 'O';
                else if (loc == 6)
                    board[1][2] = 'O';
                else if (loc == 7)
                    board[2][0] = 'O';
                else if (loc == 8)
                    board[2][1] = 'O';
                else if (loc == 9)
                    board[2][2] = 'O';
                else
                {
                    cout << "wrong input";
                    cin >> loc;
                }
            }
    }
    bool checkwin()
    {
        //CHECKING FOR X:
        //123, 456, 789
        
        //if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
        //    exit(0);

        if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X' || board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X' || board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
        {
            cout << "\n*** X won the Game!!! ***\n";
            return true;
        }
        //147, 258, 369
        else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X' || board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X' || board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
        {
            cout << "\n*** X won the Game!!! ***\n";
            return true;
        }
        //159, 357
        else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X' || board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
        {
            cout << "\n*** X won the Game!!! ***\n";
            return true;
        }
        //CHECKING FOR O:
        //123, 456, 789
        else if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O' || board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O' || board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
        {
            cout << "\n*** O won the Game!!! ***\n";
            return true;
        }
        //147, 258, 369
        else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O' || board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O' || board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
        {
            cout << "\n*** O won the Game!!! ***\n";
            return true;
        }
        //159, 357
        else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O' || board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
        {
            cout << "\n*** O won the Game!!! ***\n";
            return true;
        }
        else
            return false;
    }
    void startgame()
    {
        cout << endl;
        int loc;
        printboard();

        //for (int x = 0; x < 9; x++)//9 turns
        int x = 0;
        do
        {
                if (x % 2 == 0)
                {
                    cout << "\nTurn : X\t";
                    cin >> loc;
                    input('X', loc);
                    printboard();
                }
                else
                {
                    cout << "\nTurn : O\t";
                    cin >> loc;
                    input('O', loc);
                    printboard();
                }
                x++;
        } while (checkwin() == false);
    }
};




int main()
{
    TICTACTOE game;

    char c = 'y';
    while (c == 'y')
    {
        game.empty();
        game.startgame();
        cout << "another game?(y/n) ";
        cin >> c;
    }

    //startgame returns character who won//keep track of counts.
    //fix so doesnt replace already filled space
    //REVERSE NUMBERS SO MATCHES NUMPAD
    //
    

    return 0;
}

*/