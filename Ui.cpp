#include "ui.h"
#include "game.h"
#include "score.h"
#include "board.h"
#include "globals.h"
#include <iostream>
#include <conio.h>
using namespace std;

void ShowGameMenu() {
    clearScreen();
    int choice;
    do {
        cout << "\n========================================================================================" << endl;
        setColor(5, 0);
        cout << "                        WELCOME TO BATTLESHIP GAME" << endl;
        setColor(7, 0);
        cout << "========================================================================================" << endl;
        setColor(9, 0);
        cout << "                               MAIN MENU" << endl;
        setColor(7, 0);
        cout << "========================================================================================" << endl << endl;
        setColor(12, 0); cout << "1"; setColor(7, 0); cout << ". Start New Game" << endl;
        setColor(12, 0); cout << "2"; setColor(7, 0); cout << ". Instructions" << endl;
        setColor(12, 0); cout << "3"; setColor(7, 0); cout << ". View Leaderboard" << endl;
        setColor(12, 0); cout << "4"; setColor(7, 0); cout << ". Exit" << endl;
        cout << "\nEnter your choice (1-4): ";
        cin >> choice;

        if (choice == 1) StartNewGame();
        else if (choice == 2) Instructions();
        else if (choice == 3) ViewLeaderboard();
        else if (choice == 4) { cout << "Exiting... Goodbye!" << endl; break; }
        else                  cout << "Please enter a valid choice (1-4)." << endl;

    } while (choice != 4);
}

void StartNewGame() {
    clearScreen();
    int choice;
    cout << "======================================" << endl;
    cout << "          Start New Game              " << endl;
    cout << "======================================" << endl;
    cout << "Enter your name: ";
    cin.ignore(1000, '\n');
    cin >> name;

    do {
        cout << "\nSelect Game Mode:" << endl;
        cout << "1. Player vs Computer" << endl;
        cout << "2. Player vs Player" << endl;
        cout << "Enter choice (1-2): ";
        cin >> choice;

        if (choice == 1) vsComputer(board, board2);
        else if (choice == 2) vsPlayer(board, board2);
        else                  cout << "Enter 1 or 2 only." << endl;

    } while (choice != 1 && choice != 2);
}

void Instructions() {
    clearScreen();
    cout << "=====================================================" << endl;
    cout << "                   Instructions                      " << endl;
    cout << "=====================================================" << endl;
    cout << "1. Place your ships on the 10x10 grid." << endl;
    cout << "2. You and your opponent take turns firing shots." << endl;
    cout << "3. 'O' = MISS,  'X' = HIT,  pink X = SUNK." << endl;
    cout << "4. Shots per turn = your remaining ships + 1." << endl;
    cout << "5. Sink ALL enemy ships to win!" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "(Press any key to return to Main Menu)";
    _getch();
    clearScreen();
    ShowGameMenu();
}

void displayResult(int player1Score, int player2Score) {
    clearScreen();
    cout << "==============================================================" << endl;
    cout << "              BATTLESHIP - GAME RESULT                        " << endl;
    cout << "==============================================================" << endl;
    cout << "\nFinal Scores:" << endl;
    cout << "  ----------------------------------" << endl;
    cout << "  " << name << " : " << player1Score << endl;
    cout << "  " << name2 << " : " << player2Score << endl;
    cout << "  ----------------------------------" << endl << endl;

    if (player1Score > player2Score) {
        cout << "WINNER: " << name << "! Congratulations!" << endl;
        saveScore(name, player1Score);
    }
    else if (player2Score > player1Score) {
        cout << "WINNER: " << name2 << "! Congratulations!" << endl;
        saveScore(name2, player2Score);
    }
    else {
        cout << "It's a DRAW!" << endl;
    }

    cout << "\nPress any key to return to the main menu..." << endl;
    _getch();
    clearScreen();
    ShowGameMenu();
}