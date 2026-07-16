#pragma once

void initializeBoard(char board[10][10]);
void clearBoard(char board[10][10]);
void clearScreen();
void setColor(int textColor, int bgColor);

// Used during ship placement — hideShips=false shows 'S' cells
void printBoard(char board[10][10], bool hideShips);

// Gameplay view: enemy board left, your board right, ships always hidden
void fullBoard(char enemyBoard[10][10], char myBoard[10][10]);

int hitcounter(char board[10][10]);