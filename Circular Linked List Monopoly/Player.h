#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Board;

class Player {
private:
    string playerName;
    int location;
    int money;
    bool bankrupt;
    Board* currentSpot;

public:
    // Constructors
    Player();
    Player(string n, int m);
    Player(string n, int m, int l);

    // Player information
    void printPlayer() const;

    // Movement
    void move();

    // Getters
    string getName() const;
    int getMoney() const;
    int getLocation() const;
    Board* getCurrentSpot() const;

    // Setters
    void setName(string n);
    void setMoney(int x);
    void setLocation(int x);
    void setCurrentSpot(Board* spot);

    // Money management
    void addMoney(int x);
    void pay(int amount);
    void receive(int amount);

    // Bankruptcy
    bool isBankrupt() const;
    void setBankrupt(bool value);
};

#endif