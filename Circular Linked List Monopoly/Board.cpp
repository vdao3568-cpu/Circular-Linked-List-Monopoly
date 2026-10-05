
#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Player.h"

using namespace std;

// Static member definitions
Board* Board::first = nullptr;
Board* Board::last = nullptr;

// Default constructor
Board::Board() {
    placeName = "Does not Exist";
    price = 0;
    rent = {0};
    owner = nullptr;
    level = 0;
    nextspot = nullptr;
    previous = nullptr;
}

// Parameterized constructor
Board::Board(string n, int cost, vector<int> payments) {
    placeName = n;
    price = cost;
    rent = payments;
    owner = nullptr;
    level = 0;
    nextspot = nullptr;
    previous = nullptr;
}

// Navigate to a specific index
Board* Board::navigate(int spot) {
    if (first == nullptr) {
        return nullptr;
    }

    Board* current = first;

    for (int i = 0; i < spot; i++) {
        current = current->getNextSpot();

        if (current == first) {
            break;
        }
    }

    return current;
}

// Create the first space
void Board::createFirst(
    string n,
    int cost,
    vector<int> payments
) {
    first = new Board(n, cost, payments);

    last = first;

    // Make the list circular
    first->setNextSpot(first);
    first->setPre(first);
}

// Add a new space to the end
void Board::addElement(
    string n,
    int cost,
    vector<int> payments
) {
    if (first == nullptr) {
        createFirst(n, cost, payments);
        return;
    }

    Board* addition = new Board(n, cost, payments);

    addition->setNextSpot(first);
    addition->setPre(last);

    last->setNextSpot(addition);
    first->setPre(addition);

    last = addition;
}

// Insert after a given index
void Board::insertElement(
    string n,
    int cost,
    vector<int> payments,
    int spot
) {
    Board* position = navigate(spot);

    if (position == nullptr) {
        return;
    }

    Board* addition = new Board(n, cost, payments);

    addition->setNextSpot(position->getNextSpot());
    addition->setPre(position);

    position->getNextSpot()->setPre(addition);
    position->setNextSpot(addition);

    // If inserted after the last space,
    // make the new space the last space.
    if (position == last) {
        last = addition;
    }
}

// Find a space by name
Board* Board::findSpot(string s) {
    if (first == nullptr) {
        return nullptr;
    }

    Board* current = first;

    do {
        if (current->getPlaceName() == s) {
            return current;
        }

        current = current->getNextSpot();

    } while (current != first);

    return nullptr;
}

// Remove a space by name
void Board::removeSpot(string s) {
    Board* removal = findSpot(s);

    // Don't remove Go
    if (removal == nullptr || removal == first) {
        return;
    }

    removal->getPre()->setNextSpot(
        removal->getNextSpot()
    );

    removal->getNextSpot()->setPre(
        removal->getPre()
    );

    if (removal == last) {
        last = removal->getPre();
    }

    delete removal;
}

// ========== Getters ==========

string Board::getPlaceName() const {
    return placeName;
}

Board* Board::getNextSpot() const {
    return nextspot;
}

Board* Board::getPre() const {
    return previous;
}

int Board::getPrice() const {
    return price;
}

Player* Board::getOwner() const {
    return owner;
}

int Board::getLevel() const {
    return level;
}

int Board::getRent() const {
    if (level < 0 ||
        level >= static_cast<int>(rent.size())) {
        return 0;
    }

    return rent[level];
}

// ========== Setters ==========

void Board::setNextSpot(Board* x) {
    nextspot = x;
}

void Board::setPre(Board* x) {
    previous = x;
}

void Board::setPrice(int x) {
    price = x;
}

void Board::setOwner(Player* x) {
    owner = x;
}

void Board::setLevel(int x) {
    level = x;
}

// ========== Landing ==========

void Board::landOn(Player& player) {

    cout << player.getName()
         << " landed on "
         << placeName << endl;

    // Go has no special effect.
    // Players do not receive money for passing
    // or landing on Go.
    if (placeName == "Go") {
        cout << "Nothing happens here." << endl;
        return;
    }

    // Free spaces
    if (price <= 0) {
        cout << "Nothing happens here." << endl;
        return;
    }

    // ========================================
    // PROPERTY IS UNOWNED
    // ========================================

    if (owner == nullptr) {

        if (player.getMoney() >= price) {

            cout << placeName
                 << " is unowned. Cost: $"
                 << price << endl;

            cout << "Would you like to buy it? (y/n): ";

            string choice;
            cin >> choice;

            if (choice == "y" ||
                choice == "Y" ||
                choice == "yes" ||
                choice == "Yes" ||
                choice == "YES") {

                player.pay(price);

                if (!player.isBankrupt()) {

                    owner = &player;

                    cout << player.getName()
                         << " now owns "
                         << placeName
                         << "!" << endl;
                }
            }
            else {

                cout << player.getName()
                     << " decided not to buy "
                     << placeName
                     << "." << endl;
            }
        }
        else {

            cout << player.getName()
                 << " doesn't have enough money to buy "
                 << placeName
                 << "." << endl;
        }
    }

    // ========================================
    // PROPERTY IS OWNED BY SOMEONE ELSE
    // ========================================

    else if (owner != &player) {

        int rentAmount = getRent();

        cout << placeName
             << " is owned by "
             << owner->getName()
             << "." << endl;

        cout << player.getName()
             << " must pay $"
             << rentAmount
             << " rent." << endl;

        player.pay(rentAmount);

        // Only transfer the rent if the player
        // was able to pay it.
        if (!player.isBankrupt()) {
            owner->receive(rentAmount);
        }
    }

    // ========================================
    // PLAYER ALREADY OWNS PROPERTY
    // ========================================

    else {

        cout << "You already own "
             << placeName
             << "." << endl;
    }
}

