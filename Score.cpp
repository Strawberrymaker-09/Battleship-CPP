#include "score.h"
#include "board.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;

// Forward declaration avoids circular include (ui.h <-> score.h)
void ShowGameMenu();

void updateScore(int& score) {
    score += 10;
}

void saveScore(string playerName, int score) {
    ofstream outFile("leaderboard.txt", ios::app);
    if (outFile.is_open()) {
        outFile << playerName << " " << score << endl;
        outFile.close();
    }
}

void ViewLeaderboard() {
    clearScreen();
    ifstream inFile("leaderboard.txt");

    cout << "=====================================================" << endl;
    cout << "           BATTLESHIP LEADERBOARD                   " << endl;
    cout << "=====================================================" << endl;
    cout << " " << left << setw(20) << "PLAYER NAME" << "SCORE" << endl;
    cout << "-----------------------------------------------------" << endl;

    if (!inFile) {
        cout << " No records found. Play a game first!" << endl;
    }
    else {
        string playerName;
        int score;
        while (inFile >> playerName >> score)
            cout << " " << left << setw(20) << playerName << score << endl;
        inFile.close();
    }

    cout << "=====================================================" << endl;
    cout << "\n(Press any key to return to Main Menu)";
    _getch();
    clearScreen();
    ShowGameMenu();
}