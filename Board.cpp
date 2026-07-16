#include "board.h"
#include "globals.h"
#include <iostream>
#include <windows.h>
using namespace std;

void initializeBoard(char board[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}

void clearBoard(char board[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board[i][j] = '~';
}

int hitcounter(char board[10][10]) {
    int hits = 0;
    for (int r = 0; r < 10; r++)
        for (int c = 0; c < 10; c++)
            if (board[r][c] == 'X' || board[r][c] == 'P')
                hits++;
    return hits;
}

void clearScreen() {
    system("CLS");
}

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

// Internal helper: print one cell, ships always shown as water
static void printCell(char cell) {
    if (cell == 'X') {
        setColor(15, 12); cout << " X ";   // white on red   = hit
    }
    else if (cell == 'P') {
        setColor(15, 13); cout << " X ";   // white on pink  = sunk
    }
    else if (cell == 'O') {
        setColor(0, 8);  cout << " O ";   // black on gray  = miss
    }
    else {
        setColor(15, 1);  cout << " ~ ";   // white on blue  = water (S hidden)
    }
    setColor(7, 0);
}

// Internal helper: print the +---+ separator for exactly 10 columns
static void printSep() {
    cout << "  +---+---+---+---+---+---+---+---+---+---+";
}

void printBoard(char board[10][10], bool hideShips) {
    cout << "    0   1   2   3   4   5   6   7   8   9" << endl;
    printSep(); cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " |";
        for (int j = 0; j < 10; j++) {
            char cell = board[i][j];
            if (cell == 'X') {
                setColor(15, 12); cout << " X "; setColor(7, 0);
            }
            else if (cell == 'P') {
                setColor(15, 13); cout << " X "; setColor(7, 0);
            }
            else if (cell == 'O') {
                setColor(0, 8);  cout << " O "; setColor(7, 0);
            }
            else if (cell == 'S' && !hideShips) {
                if (playerturn == 1) setColor(15, player1shipcolor);
                else                 setColor(15, player2shipcolor);
                cout << " S "; setColor(7, 0);
            }
            else {
                setColor(15, 1);  cout << " ~ "; setColor(7, 0);
            }
            cout << "|";
        }
        cout << endl;
        printSep(); cout << endl;
    }
    cout << endl;
}

void fullBoard(char enemyBoard[10][10], char myBoard[10][10]) {
    const char* gap = "      ";  // space between the two boards

    cout << endl;
    cout << "        ENEMY BOARD" << gap << "              YOUR BOARD" << endl << endl;
    cout << "    0   1   2   3   4   5   6   7   8   9";
    cout << gap;
    cout << "    0   1   2   3   4   5   6   7   8   9" << endl;

    printSep(); cout << gap; printSep(); cout << endl;

    for (int i = 0; i < 10; i++) {
        // Left: enemy board
        cout << i << " |";
        for (int j = 0; j < 10; j++) { printCell(enemyBoard[i][j]); cout << "|"; }

        cout << gap;

        // Right: your board (ships also hidden)
        cout << i << " |";
        for (int j = 0; j < 10; j++) { printCell(myBoard[i][j]); cout << "|"; }

        cout << endl;
        printSep(); cout << gap; printSep(); cout << endl;
    }
    cout << endl;
}