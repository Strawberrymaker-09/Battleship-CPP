#pragma once
#include <string>

extern char board[10][10];
extern char board2[10][10];
extern char shiplabel1[10][10];
extern char shiplabel2[10][10];

extern std::string name;
extern std::string name2;

extern int player1shipcolor;
extern int player2shipcolor;
extern int playerturn;

// Color constants — defined once in globals.cpp
extern const int BLACK;
extern const int BLUE;
extern const int GREEN;
extern const int CYAN;
extern const int RED;
extern const int MAGENTA;
extern const int YELLOW;
extern const int WHITE;