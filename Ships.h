#pragma once
#include <string>

int  shipColor();
void placementofships(char board[10][10], char shiplabel[10][10]);
void manualplacement(char board[10][10], char shiplabel[10][10],
    int size, std::string sname, char shiplabelChar);
void setRandomShips(char board[10][10]);
bool shipsunk(char shiplabel[10][10], char label);
int  remainingships(char shiplabel[10][10]);