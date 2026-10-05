
#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Board.h"

using namespace std;

// Default constructor
Player::Player() {
    playerName = "John Doe";
    location = 0;
    money = 1500;
    bankrupt = false;
    currentSpot = nullptr;
}

// Constructor with name and money
Player::Player(string n, int m) {
    playerName = n;
    money = m;
    location = 0;
    bankrupt = false;
    currentSpot = nullptr;
}

// Constructor with name, money, and location
Player::Player(string n, int m, int l) {
    playerName = n;
    money = m;
    location = l;
    bankrupt = false;
    currentSpot = nullptr;
}

// Print player information
void Player::printPlayer() const {
    cout << playerName << ":\n"
         << "Location: " << location << "\n"
         << "Money: $" << money << endl;
}

// Move player
void Player::move() {
    // Roll two six-sided dice
    int steps =
        (1 + rand() % 6) +
        (1 + rand() % 6);

    cout << playerName
         << " rolled "
         << steps << "." << endl;

    // Move around the 26-space circular board.
    // Passing or landing on Go does not give money.
    int newLocation =
        (location + steps) % 26;

    location = newLocation;
}

// Getters

string Player::getName() const {
    return playerName;
}

int Player::getMoney() const {
    return money;
}

int Player::getLocation() const {
    return location;
}

Board* Player::getCurrentSpot() const {
    return currentSpot;
}

// Setters

void Player::setName(string n) {
    playerName = n;
}

void Player::setMoney(int x) {
    money = x;
}

void Player::setLocation(int x) {
    location = x;
}

void Player::setCurrentSpot(Board* spot) {
    currentSpot = spot;
}

// Add money
void Player::addMoney(int x) {
    money += x;
}

// Pay money
void Player::pay(int amount) {
    money -= amount;

    if (money < 0) {
        setBankrupt(true);

        cout << getName()
             << " cannot pay and goes bankrupt!"
             << endl;
    }
}

// Receive money
void Player::receive(int amount) {
    money += amount;
}

// Bankruptcy

bool Player::isBankrupt() const {
    return bankrupt;
}

void Player::setBankrupt(bool value) {
    bankrupt = value;
}

