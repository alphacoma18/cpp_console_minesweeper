#include <iostream>
#include <math.h>
#include <ctime>
#include <string.h>
#include <iomanip>
#include <chrono>

using namespace std;
/*
    -Course Final Project-

    Program by: Alpha Romer Coma
    Section: BSCSSE - TN05
    Date: 2022/11/09

    Program name: Console Minesweeper Lite
    Description: A simple console minesweeper game with four difficulty levels.
    Submitted to: Sir Reginald Cheng
    Course: CCS0003L - Computer Programming 1

    Initialization Algorithm Time Complexity: O(n^2) - Quadratic
    Search Algorithm Time Complexity: 0(1) - Constant

    Program Flow:
    1. Display the game title.
    2. Ask the user to input the board size and difficulty level.
    3. Generate the game board.
    4. Ask the user to input coordinates.
    5. Check if the coordinate is a mine.
    6. If the coordinate is a mine, display the game board with the mines and end the game.
    7. If the coordinate is not a mine, display the game board with the coordinate revealed.
    8. Repeat steps 4 to 7 until the user wins or loses.
    9. Display the game board with the mines, and the user wins.
    10. Ask the user if they want to play again.
    11. If the user wants to play again, go to step 2.
    12. If the user does not want to play again, end the program.
*/

struct Game
{
    int rows = 0;
    int cols = 0;

    int mines = 0;
    int clearFields = 0;
    int cleared = 0;

    chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
    chrono::duration<double> gameTime = endTime - startTime;

    int modulo = 0;
    int turn = 1;
    char **gameBoard = NULL;
    int **process1 = NULL;
    char **process2 = NULL;
};

// Game Function prototypes
int initGame();
int inputMeta(Game &board);
void initBoards(Game &board);
void genMineBoard(Game &board);
int replGameBoard(Game &board, int i, int j);
int playGame(Game &board);

// Utility function prototypes
void genHorizLine(int width);
void printResult(string res, Game &board);
void printSolution(Game &board);

int main()
{
    int play = 1;
    do
    {
        play = initGame();
    } while (play == 1);
    genHorizLine(30);
    cout << "Thank you for playing!\n";
    cout << "Program by: Alpha Romer Coma\n";
    cout << "Section: BSCSSE - TN05\n";
    genHorizLine(30);
    return 0;
}
// Utility functions
void genHorizLine(int width)
{
    cout << string(width, '_') << "\n";
}

void printSolution(Game &board)
{
    cout << "Solution:\n";
    genHorizLine(board.cols * 2);
    for (int i = 0; i < board.rows; i++)
    {
        for (int j = 0; j < board.cols; j++)
        {
            cout << board.process2[i][j] << " ";
        }
        cout << "\n";
    }
    genHorizLine(board.cols * 2);
}
void printResult(string res, Game &board)
{
    board.endTime = chrono::steady_clock::now();
    board.gameTime = board.endTime - board.startTime;
    cout << "Game Over! - YOU " << res << "\n";
    cout << "Time: " << fixed << setprecision(2) << board.gameTime.count() << "s\n";
    cout << "Turns: " << board.turn << "\n";
    printSolution(board);
}
// Game Functions
int playGame(Game &board)
{
    genHorizLine(board.cols * 2);
    while (true)
    {
        for (int i = 0; i < board.rows; ++i)
        {
            for (int j = 0; j < board.cols; ++j)
            {
                cout << board.gameBoard[i][j] << " ";
            }
            cout << "\n";
        }
        genHorizLine(board.cols * 2);
        if (board.cleared == board.clearFields)
        {
            printResult("WIN!", board);
            return 1;
        }
        cout << "Turn: " << board.turn++ << " - " << board.cleared << "/" << board.clearFields << "\n";
        int col, row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter row: ";
        cin >> row;
        int res = replGameBoard(board, row, col);
        genHorizLine(board.cols * 2);
        if (res == 1)
        {
            printResult("LOSE!", board);
            return 0;
        }
    }
}

int replGameBoard(Game &board, int i, int j)
{
    if (board.process2[i][j] == '*')
        return 1;
    board.gameBoard[i][j] = board.process2[i][j];
    board.cleared++;
    return 0;
}

void genMineBoard(Game &board)
{
    for (int i = 0; i < board.rows; ++i)
    {
        for (int j = 0; j < board.cols; ++j)
        {
            if (board.process1[i][j] == 1)
            {
                board.process2[i][j] = '*';
                --board.clearFields;
                ++board.mines;
                continue;
            }
            int count = 0;
            if (i - 1 >= 0 && j - 1 >= 0 && board.process1[i - 1][j - 1] == 1)
            {
                ++count;
            }
            if (i - 1 >= 0 && board.process1[i - 1][j] == 1)
            {
                ++count;
            }
            if (i - 1 >= 0 && j + 1 < board.cols && board.process1[i - 1][j + 1] == 1)
            {
                ++count;
            }
            if (j - 1 >= 0 && board.process1[i][j - 1] == 1)
            {
                ++count;
            }
            if (j + 1 < board.cols && board.process1[i][j + 1] == 1)
            {
                ++count;
            }
            if (i + 1 < board.rows && j - 1 >= 0 && board.process1[i + 1][j - 1] == 1)
            {
                ++count;
            }
            if (i + 1 < board.rows && board.process1[i + 1][j] == 1)
            {
                ++count;
            }
            if (i + 1 < board.rows && j + 1 < board.cols && board.process1[i + 1][j + 1] == 1)
            {
                ++count;
            }
            board.process2[i][j] = count + '0';
        }
    }
    board.clearFields = (board.rows * board.cols) - board.mines;
}

void initBoards(Game &board)
{
    board.gameBoard = new char *[board.rows];
    board.process1 = new int *[board.rows];
    board.process2 = new char *[board.rows];
    for (int i = 0; i < board.rows; ++i)
    {
        board.gameBoard[i] = new char[board.cols];
        board.process1[i] = new int[board.cols];
        board.process2[i] = new char[board.cols];
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < board.rows; ++i)
    {
        for (int j = 0; j < board.cols; ++j)
        {
            board.gameBoard[i][j] = '-';
            board.process1[i][j] = rand() % board.modulo;
        }
    }
}

int inputMeta(Game &board)
{
    cout << "TN05 - Project Minesweeper\n";
    cout << string(28, '_') << "\n";

    char difficulty;
    cout << "Enter the number of rows: ";
    cin >> board.rows;
    cout << "Enter the number of columns: ";
    cin >> board.cols;
    cout << "Enter the difficulty (E/M/H/X): ";
    cin >> difficulty;
    switch (difficulty)
    {
    case 'E':
        board.modulo = 8;
        break;
    case 'M':
        board.modulo = 6;
        break;
    case 'H':
        board.modulo = 4;
        break;
    case 'X':
        board.modulo = 2;
        break;
    default:
        cout << "Invalid difficulty\n";
        return -1;
    }
    return 0;
}
int initGame()
{
    int init, again;
    Game board;
    init = inputMeta(board);
    if (init == -1)
        return 0;
    board.startTime = chrono::steady_clock::now();
    initBoards(board);
    genMineBoard(board);
    playGame(board);
    cout << "Play again? (1 = Yes, 0 = No): ";
    cin >> again;
    return again;
}