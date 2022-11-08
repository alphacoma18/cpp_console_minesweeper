#include <iostream>
#include <math.h>
#include <ctime>
#include <string.h>
#include <iomanip>

using namespace std;
/*
    -Course Final Project-

    Program by: Alpha Romer Coma
    Section: BSCSSE - TN05
    Date: 2022/11/09

    Program name: Console Minesweeper Lite
    Description: A simple console minesweeper game with three difficulty levels.
    Submitted to: Sir Reginald Cheng
    Course: CCS0003L - Computer Programming 1
*/
struct gameBoard
{
    int rows = 0;
    int cols = 0;
    int mines = 0;
    int modulo = 0;
    int turn = 1;
    char **gameBoard = NULL;
    int **process1 = NULL;
    char **process2 = NULL;
};

int inputMeta(int &rows, int &cols);
void initBoards(gameBoard &board);
void generateMineBoard(gameBoard &board);
void replaceGameBoard(gameBoard &board, int i, int j);

int main()
{
    int rows, cols, modulo;
    gameBoard board;
    board.modulo = inputMeta(rows, cols);
    if (board.modulo == -1)
        return 0;
    board.rows = rows;
    board.cols = cols;
    initBoards(board);
    // not using the loop of initBoards because we have + 1 and the next value is not generated yet
    generateMineBoard(board);
    while (true)
    {
        for (int i = 0; i < board.rows; i++)
        {
            cout.width(25);
            for (int j = 0; j < board.cols; j++)
            {
                cout << board.gameBoard[i][j] << " ";
            }
            cout << "\n";
        }
        cout << string(board.rows*2, '_') << "\n" << "Turn: " << board.turn++ << "\n";
        int col, row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter row: ";
        cin >> row;
        replaceGameBoard(board, row, col);
    }
    return 0;
}
void replaceGameBoard(gameBoard &board, int i, int j) {
    if (board.process2[i][j] == '*') {
        cout << "You lost!\n";
        exit(0);
    }
    if (board.process2[i][j] == '0') {
        board.gameBoard[i][j] = '0';
        if (i - 1 >= 0 && j - 1 >= 0 && board.gameBoard[i - 1][j - 1] == 'X')
            replaceGameBoard(board, i - 1, j - 1);
        if (i - 1 >= 0 && board.gameBoard[i - 1][j] == 'X')
            replaceGameBoard(board, i - 1, j);
        if (i - 1 >= 0 && j + 1 < board.cols && board.gameBoard[i - 1][j + 1] == 'X')
            replaceGameBoard(board, i - 1, j + 1);
        if (j - 1 >= 0 && board.gameBoard[i][j - 1] == 'X')
            replaceGameBoard(board, i, j - 1);
        if (j + 1 < board.cols && board.gameBoard[i][j + 1] == 'X')
            replaceGameBoard(board, i, j + 1);
        if (i + 1 < board.rows && j - 1 >= 0 && board.gameBoard[i + 1][j - 1] == 'X')
            replaceGameBoard(board, i + 1, j - 1);
        if (i + 1 < board.rows && board.gameBoard[i + 1][j] == 'X')
            replaceGameBoard(board, i + 1, j);
        if (i + 1 < board.rows && j + 1 < board.cols && board.gameBoard[i + 1][j + 1] == 'X')
            replaceGameBoard(board, i + 1, j + 1);
    }
    else {
        board.gameBoard[i][j] = board.process2[i][j];
    }
}

void generateMineBoard(gameBoard &board)
{
    for (int i = 0; i < board.rows; i++)
    {
        for (int j = 0; j < board.cols; j++)
        {

            if (board.process1[i][j] == 1)
            {
                board.process2[i][j] = '*';
                board.mines++;
                continue;
            }
            else
            {
                // check for mines in all 8 directions
                int count = 0;
                if (i - 1 >= 0 && j - 1 >= 0 && board.process1[i - 1][j - 1] == 1)
                {
                    count++;
                }
                if (i - 1 >= 0 && board.process1[i - 1][j] == 1)
                {
                    count++;
                }
                if (i - 1 >= 0 && j + 1 < board.cols && board.process1[i - 1][j + 1] == 1)
                {
                    count++;
                }
                if (j - 1 >= 0 && board.process1[i][j - 1] == 1)
                {
                    count++;
                }
                if (j + 1 < board.cols && board.process1[i][j + 1] == 1)
                {
                    count++;
                }
                if (i + 1 < board.rows && j - 1 >= 0 && board.process1[i + 1][j - 1] == 1)
                {
                    count++;
                }
                if (i + 1 < board.rows && board.process1[i + 1][j] == 1)
                {
                    count++;
                }
                if (i + 1 < board.rows && j + 1 < board.cols && board.process1[i + 1][j + 1] == 1)
                {
                    count++;
                }
                board.process2[i][j] = count + '0';
            }
        }
    }
}

void initBoards(gameBoard &board)
{
    board.gameBoard = new char *[board.rows];
    board.process1 = new int *[board.rows];
    board.process2 = new char *[board.rows];
    for (int i = 0; i < board.rows; i++)
    {
        board.gameBoard[i] = new char[board.cols];
        board.process1[i] = new int[board.cols];
        board.process2[i] = new char[board.cols];
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < board.rows; i++)
    {
        for (int j = 0; j < board.cols; j++)
        {
            board.gameBoard[i][j] = '-';
            board.process1[i][j] = rand() % board.modulo;
        }
    }
}

int inputMeta(int &rows, int &cols)
{
    char difficulty;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    cout << "Enter the difficulty (E/M/H): ";
    cin >> difficulty;
    switch (difficulty)
    {
    case 'E':
        return 10;
    case 'M':
        return 5;
    case 'H':
        return 2;
    default:
        cout << "Invalid difficulty\n";
        return -1;
    }
}