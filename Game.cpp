#include "game.h"
#include "board.h"
#include "ships.h"
#include "score.h"
#include "globals.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Forward declaration — defined in ui.cpp (avoids circular include)
void displayResult(int player1Score, int player2Score);

// ---------------------------------------------
// Player attacks opponent board
// ---------------------------------------------
void playerAttack(char oppboard[10][10], int& playerscore) {
    int row, col;
    cout << "\n ...Attack Your Enemy..." << endl;

    while (true) {
        cout << "Enter row to attack (0-9): ";    cin >> row;
        cout << "Enter column to attack (0-9): "; cin >> col;

        if (row < 0 || row > 9 || col < 0 || col > 9) {
            cout << "Invalid. Row and column must be 0-9." << endl;
            continue;
        }

        char target = oppboard[row][col];

        if (target == 'O' || target == 'X' || target == 'P') {
            cout << "Already attacked this cell. Choose another." << endl;
            continue;
        }

        if (target == 'S') {
            cout << "Direct hit!" << endl;
            oppboard[row][col] = 'X';
            playerscore += 10;

            // Pick the correct label grid for the board being attacked
            char (*lbl)[10] = (playerturn == 1) ? shiplabel2 : shiplabel1;
            char sinklabel = lbl[row][col];
            lbl[row][col] = 'X';

            if (shipsunk(lbl, sinklabel)) {
                cout << "You sunk the opponent's ship!" << endl;
                for (int r = 0; r < 10; r++)
                    for (int c = 0; c < 10; c++)
                        if (lbl[r][c] == 'X' || lbl[r][c] == sinklabel) {
                            lbl[r][c] = 'P';
                            oppboard[r][c] = 'P';
                        }
            }
        }
        else {
            cout << "Miss!" << endl;
            oppboard[row][col] = 'O';
            playerscore -= 1;
        }
        break;
    }
}

// ---------------------------------------------
// Computer attacks a random valid cell
// ---------------------------------------------
void computerAttack(char playerBoard[10][10], int& computerScore) {
    while (true) {
        int row = rand() % 10;
        int col = rand() % 10;
        char cell = playerBoard[row][col];

        if (cell == 'X' || cell == 'O' || cell == 'P') continue;

        if (cell == 'S') {
            cout << "Computer hit your ship at (" << row << "," << col << ")!" << endl;
            playerBoard[row][col] = 'X';
            updateScore(computerScore);

            char sinklabel = shiplabel1[row][col];
            shiplabel1[row][col] = 'X';

            if (shipsunk(shiplabel1, sinklabel)) {
                cout << "The computer sunk one of your ships!" << endl;
                for (int r = 0; r < 10; r++)
                    for (int c = 0; c < 10; c++)
                        if (shiplabel1[r][c] == 'X' || shiplabel1[r][c] == sinklabel) {
                            shiplabel1[r][c] = 'P';
                            playerBoard[r][c] = 'P';
                        }
            }
        }
        else {
            cout << "Computer missed at (" << row << "," << col << ")." << endl;
            playerBoard[row][col] = 'O';
            computerScore -= 1;
        }
        break;
    }
}

// ---------------------------------------------
// Player vs Computer
// ---------------------------------------------
void vsComputer(char playerBoard[10][10], char computerBoard[10][10]) {
    clearScreen();
    cout << "-------------- VS COMPUTER MODE --------------" << endl;

    int playerScore = 0, computerScore = 0;
    const int totalHits = 17;

    // name2 shown in result screen — set it here
    name2 = "Computer";

    playerturn = 1;
    player1shipcolor = shipColor();

    initializeBoard(playerBoard);
    initializeBoard(computerBoard);
    initializeBoard(shiplabel1);
    initializeBoard(shiplabel2);

    cout << "Computer is placing ships..." << endl;
    playerturn = 2;
    setRandomShips(computerBoard);
    playerturn = 1;

    cout << name << ", place your ships:" << endl;
    printBoard(playerBoard, false);
    placementofships(playerBoard, shiplabel1);
    cout << "\nAll ships placed! Press any key to start..." << endl;
    _getch();

    bool gameOver = false;
    while (!gameOver) {
        clearScreen();
        int p_attacks = remainingships(shiplabel1) + 1;

        cout << "\n========================================" << endl;
        cout << name << "'s TURN  |  Ships remaining: " << remainingships(shiplabel1) << endl;
        cout << "Shots this turn: " << p_attacks << endl;
        cout << "========================================" << endl;

        for (int i = 1; i <= p_attacks && !gameOver; i++) {
            fullBoard(computerBoard, playerBoard);
            cout << "Shot " << i << " of " << p_attacks << endl;
            playerAttack(computerBoard, playerScore);
            if (hitcounter(computerBoard) >= totalHits) {
                fullBoard(computerBoard, playerBoard);
                cout << "\nCONGRATULATIONS! " << name << " wins!" << endl;
                gameOver = true;
            }
            if (!gameOver) { _getch(); clearScreen(); }
        }
        if (gameOver) break;

        cout << "Press any key for Computer's move..." << endl;
        _getch();
        clearScreen();

        playerturn = 2;
        int c_attacks = remainingships(shiplabel2) + 1;

        cout << "\n========================================" << endl;
        cout << "COMPUTER'S TURN  |  Shots: " << c_attacks << endl;
        cout << "========================================" << endl;
        _getch();

        for (int j = 1; j <= c_attacks && !gameOver; j++) {
            cout << "Computer shot " << j << " of " << c_attacks << endl;
            computerAttack(playerBoard, computerScore);
            if (hitcounter(playerBoard) >= totalHits) {
                cout << "\nGame Over! Computer wins!" << endl;
                gameOver = true;
            }
        }

        fullBoard(computerBoard, playerBoard);

        if (!gameOver) {
            playerturn = 1;
            cout << "\nPress any key to continue your turn..." << endl;
            _getch();
        }
        clearScreen();
    }

    displayResult(playerScore, computerScore);
}

// ---------------------------------------------
// Player vs Player
// ---------------------------------------------
void vsPlayer(char board1[10][10], char board2[10][10]) {
    clearScreen();
    int p1score = 0, p2score = 0;
    const int totalHits = 17;

    cout << "Player 1: " << name << endl;
    player1shipcolor = shipColor();

    initializeBoard(shiplabel1);
    initializeBoard(shiplabel2);
    initializeBoard(board1);

    playerturn = 1;
    printBoard(board1, false);
    placementofships(board1, shiplabel1);

    cout << "\nAll ships of " << name << " placed!" << endl;
    cout << "Pass to Player 2 — press any key..." << endl;
    _getch();
    clearScreen();

    cout << "\nEnter Player 2 name: ";
    cin >> name2;
    player2shipcolor = shipColor();

    initializeBoard(board2);
    playerturn = 2;
    printBoard(board2, false);
    placementofships(board2, shiplabel2);

    cout << "\nAll ships of " << name2 << " placed!" << endl;
    cout << "Press any key to start the battle..." << endl;
    _getch();
    clearScreen();

    bool gameOver = false;

    while (!gameOver) {
        // ── Player 1's turn ──
        playerturn = 1;
        int p1_attacks = remainingships(shiplabel1) + 1;

        cout << "\n========================================" << endl;
        cout << name << "'s TURN  |  Ships remaining: " << remainingships(shiplabel1) << endl;
        cout << "Shots this turn: " << p1_attacks << endl;
        cout << "========================================" << endl;

        for (int i = 1; i <= p1_attacks && !gameOver; i++) {
            fullBoard(board2, board1);   // left=enemy(p2), right=own(p1)
            cout << "Shot " << i << " of " << p1_attacks << endl;
            playerAttack(board2, p1score);
            if (hitcounter(board2) >= totalHits) {
                fullBoard(board2, board1);
                cout << "\n" << name << " WINS!" << endl;
                gameOver = true;
            }
            if (!gameOver) { _getch(); clearScreen(); }
        }
        if (gameOver) break;

        cout << "Pass to " << name2 << "\n...press any key..." << endl;
        _getch();
        clearScreen();

        // ── Player 2's turn ──
        playerturn = 2;
        int p2_attacks = remainingships(shiplabel2) + 1;

        cout << "\n========================================" << endl;
        cout << name2 << "'s TURN  |  Ships remaining: " << remainingships(shiplabel2) << endl;
        cout << "Shots this turn: " << p2_attacks << endl;
        cout << "========================================" << endl;

        for (int j = 1; j <= p2_attacks && !gameOver; j++) {
            fullBoard(board1, board2);   // left=enemy(p1), right=own(p2)
            cout << "Shot " << j << " of " << p2_attacks << endl;
            playerAttack(board1, p2score);
            if (hitcounter(board1) >= totalHits) {
                fullBoard(board1, board2);
                cout << "\n" << name2 << " WINS!" << endl;
                gameOver = true;
            }
            if (!gameOver) { _getch(); clearScreen(); }
        }
        if (gameOver) break;

        cout << "Pass to " << name << " — press any key..." << endl;
        _getch();
        clearScreen();
    }

    displayResult(p1score, p2score);
}