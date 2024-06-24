#include <iostream>
#include <limits>

using namespace std;

const int SIZE = 3;

void printBoard(const char board[SIZE][SIZE])
{
    cout << "Current board:\n";
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            cout << board[i][j];
            if (j < SIZE - 1)
                cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1)
            cout << "---------\n";
    }
}

bool checkWin(const char board[SIZE][SIZE], char player)
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool checkDraw(const char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

void switchPlayer(char &currentPlayer)
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

pair<int, int> getMove(const char board[SIZE][SIZE], char player)
{
    int move;
    while (true)
    {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;
        if (cin.fail() || move < 1 || move > 9)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid move. Please enter a number between 1 and 9.\n";
            continue;
        }
        int row = (move - 1) / SIZE;
        int col = (move - 1) % SIZE;
        if (board[row][col] != ' ')
        {
            cout << "This position is already taken. Try another move.\n";
        }
        else
        {
            return {row, col};
        }
    }
}

void playGame()
{
    while (true)
    {
        char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
        char currentPlayer = 'X';
        while (true)
        {
            printBoard(board);
            auto move = getMove(board, currentPlayer);
            board[move.first][move.second] = currentPlayer;
            if (checkWin(board, currentPlayer))
            {
                printBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (checkDraw(board))
            {
                printBoard(board);
                cout << "The game is a draw!\n";
                break;
            }
            switchPlayer(currentPlayer);
        }

        char playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain != 'y' && playAgain != 'Y')
        {
            break;
        }
    }
}

int main()
{
    playGame();
    return 0;
}
