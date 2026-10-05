/*
Name: Vincent Dao
Honor Pledge: I have not plagiarized this from anyone, and any AI usage will be cited
AI Usage: For my bankruptcy logic and to clean up my code
Date: 10/4/2026
*/

#include <iostream>
#include "Player.h"
#include "Board.h"
#include <vector>
#include <string>

using namespace std;

static vector<Player> playerList;

void createBoard();
void createPlayers();
bool startGame();

int main() {
    cout << "Headers found!" << endl;

    createBoard();
    createPlayers();
    startGame();

    return 0;
}

void createBoard() {
    Board::createFirst("Go", 0, {0, 0, 0});

    Board::addElement("Mediterranean Avenue", 60, {10, 30, 90});
    Board::addElement("Baltic Avenue", 60, {20, 60, 180});
    Board::addElement("Oriental Avenue", 100, {30, 90, 270});
    Board::addElement("Vermont Avenue", 100, {30, 90, 270});
    Board::addElement("Connecticut Avenue", 120, {40, 100, 300});

    Board::addElement("Free Parking", 0, {0, 0, 0});

    Board::addElement("St. Charles Place", 140, {50, 150, 450});
    Board::addElement("States Avenue", 140, {50, 150, 450});
    Board::addElement("Virginia Avenue", 160, {60, 180, 500});
    Board::addElement("St. James Place", 180, {70, 200, 550});
    Board::addElement("Tennessee Avenue", 180, {70, 200, 550});
    Board::addElement("New York Avenue", 200, {80, 220, 600});

    Board::addElement("Free Parking", 0, {0, 0, 0});

    Board::addElement("Kentucky Avenue", 220, {90, 250, 700});
    Board::addElement("Indiana Avenue", 220, {90, 250, 700});
    Board::addElement("Illinois Avenue", 240, {100, 300, 750});
    Board::addElement("Atlantic Avenue", 260, {110, 330, 800});
    Board::addElement("Ventnor Avenue", 260, {110, 330, 800});
    Board::addElement("Marvin Gardens", 280, {120, 360, 850});

    Board::addElement("Free Parking", 0, {0, 0, 0});

    Board::addElement("Pacific Avenue", 300, {130, 390, 900});
    Board::addElement("North Carolina Avenue", 300, {130, 390, 900});
    Board::addElement("Pennsylvania Avenue", 320, {150, 450, 1000});
    Board::addElement("Park Place", 350, {175, 500, 1100});
    Board::addElement("Boardwalk", 400, {200, 600, 1400});
}

void createPlayers() {
    int numOfPlayer;

    cout << "Please enter the number of players: ";
    cin >> numOfPlayer;

    if (numOfPlayer < 2) {
        cout << "You need at least 2 players to play." << endl;
        return;
    }

    for (int i = 0; i < numOfPlayer; i++) {
        cout << "Player " << i + 1
             << " please enter your name: ";

        string tempName;
        cin >> tempName;

        playerList.push_back(Player(tempName, 1500));
    }
}

bool startGame() {
    int turn = 0;

    cout << "\nGame Start!" << endl;

    if (playerList.size() < 2) {
        cout << "At least 2 players are required to start the game."
             << endl;
        return false;
    }

    while (true) {
        int playersLeft = 0;
        Player* winner = nullptr;

        // Count players who are not bankrupt
        for (auto& p : playerList) {
            if (!p.isBankrupt()) {
                playersLeft++;
                winner = &p;
            }
        }

        // One player remains
        if (playersLeft == 1) {
            cout << "\n*** "

