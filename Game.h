#pragma once

void vsComputer(char playerBoard[10][10], char computerBoard[10][10]);
void vsPlayer(char board1[10][10], char board2[10][10]);
void playerAttack(char opponentBoard[10][10], int& playerScore);
void computerAttack(char playerBoard[10][10], int& computerScore);