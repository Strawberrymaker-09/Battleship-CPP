#include "ships.h"
#include "board.h"
#include "globals.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int shipColor() {
    int choice;
    do {
        cout << "\nChoose your ship color:" << endl;
        cout << "1. Blue\n2. Green\n3. Cyan\n4. Red\n5. Magenta\n6. Yellow\n7. White" << endl;
        cout << "Enter choice (1-7): ";
        cin >> choice;
        switch (choice) {
        case 1: return BLUE;
        case 2: return GREEN;
        case 3: return CYAN;
        case 4: return RED;
        case 5: return MAGENTA;
        case 6: return YELLOW;
        case 7: return WHITE;
        default: cout << "Invalid. Enter 1-7." << endl;
        }
    } while (true);
}

bool shipsunk(char shiplabel[10][10], char label) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (shiplabel[i][j] == label)
                return false;
    return true;
}

int remainingships(char shiplabel[10][10]) {
    char labels[5] = { 'A', 'B', 'D', 'E', 'F' };
    int count = 0;
    for (int i = 0; i < 5; i++) {
        bool found = false;
        for (int r = 0; r < 10 && !found; r++)
            for (int c = 0; c < 10 && !found; c++)
                if (shiplabel[r][c] == labels[i])
                    found = true;
        if (found) count++;
    }
    return count;
}

void manualplacement(char board[10][10], char shiplabel[10][10],
    int size, string sname, char shiplabelChar) {
    int row, col, dir;

    while (true) {
        cout << "\nPlace your " << sname << " (size " << size << ")" << endl;
        cout << "Enter starting row (0-9): ";    cin >> row;
        cout << "Enter starting column (0-9): "; cin >> col;

        if (row < 0 || row > 9 || col < 0 || col > 9) {
            cout << "Row and column must be 0-9. Try again." << endl;
            continue;
        }

        cout << "Direction — 1. Horizontal   2. Vertical: ";
        cin >> dir;

        if (dir != 1 && dir != 2) {
            cout << "Enter 1 or 2 only." << endl;
            continue;
        }

        if (dir == 1) {
            if (col + size > 10) {
                cout << "Does not fit horizontally from column " << col
                    << " (would need up to column " << col + size - 1
                    << "). Try again." << endl;
                continue;
            }
            bool overlap = false;
            for (int i = 0; i < size; i++)
                if (board[row][col + i] != '~') { overlap = true; break; }
            if (overlap) { cout << "A ship is already there. Try again." << endl; continue; }

            for (int i = 0; i < size; i++) {
                board[row][col + i] = 'S';
                shiplabel[row][col + i] = shiplabelChar;
            }
        }
        else {
            if (row + size > 10) {
                cout << "Does not fit vertically from row " << row
                    << " (would need down to row " << row + size - 1
                    << "). Try again." << endl;
                continue;
            }
            bool overlap = false;
            for (int i = 0; i < size; i++)
                if (board[row + i][col] != '~') { overlap = true; break; }
            if (overlap) { cout << "A ship is already there. Try again." << endl; continue; }

            for (int i = 0; i < size; i++) {
                board[row + i][col] = 'S';
                shiplabel[row + i][col] = shiplabelChar;
            }
        }

        cout << "Ship placed!" << endl;
        printBoard(board, false);
        break;
    }
}

void placementofships(char board[10][10], char shiplabel[10][10]) {
    string snames[5] = { "Aircraft Carrier", "Battleship", "Destroyer", "Submarine", "Patrol Boat" };
    int    sizes[5] = { 5, 4, 3, 3, 2 };
    char   labels[5] = { 'A', 'B', 'D', 'E', 'F' };
    int choice;

    do {
        cout << "1. Manual placement\n2. Random placement\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            for (int i = 0; i < 5; i++)
                manualplacement(board, shiplabel, sizes[i], snames[i], labels[i]);
        }
        else if (choice == 2) {
            setRandomShips(board);
            printBoard(board, false);
        }
        else {
            cout << "Enter 1 or 2 only." << endl;
        }
    } while (choice != 1 && choice != 2);
}

void setRandomShips(char randomboard[10][10]) {
    int  shipsize[5] = { 5, 4, 3, 3, 2 };
    char labels[5] = { 'A', 'B', 'D', 'E', 'F' };

    srand((unsigned)time(0));

    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            int row = rand() % 10;
            int col = rand() % 10;
            int dir = rand() % 2;   // 0=horizontal, 1=vertical
            bool overlap = false;

            if (dir == 0) {
                if (col + shipsize[i] > 10) continue;
                for (int j = 0; j < shipsize[i]; j++)
                    if (randomboard[row][col + j] == 'S') { overlap = true; break; }
                if (!overlap) {
                    for (int j = 0; j < shipsize[i]; j++) {
                        randomboard[row][col + j] = 'S';
                        if (playerturn == 1) shiplabel1[row][col + j] = labels[i];
                        else                 shiplabel2[row][col + j] = labels[i];
                    }
                    placed = true;
                }
            }
            else {
                if (row + shipsize[i] > 10) continue;
                for (int j = 0; j < shipsize[i]; j++)
                    if (randomboard[row + j][col] == 'S') { overlap = true; break; }
                if (!overlap) {
                    for (int j = 0; j < shipsize[i]; j++) {
                        randomboard[row + j][col] = 'S';
                        if (playerturn == 1) shiplabel1[row + j][col] = labels[i];
                        else                 shiplabel2[row + j][col] = labels[i];
                    }
                    placed = true;
                }
            }
        }
    }
}