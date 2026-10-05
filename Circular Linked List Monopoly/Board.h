#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

using namespace std;

class Player;

class Board {
private:
    string placeName;
    int price;
    vector<int> rent;

    Player* owner;

    int level;

    Board* nextspot;
    Board* previous;

    static Board* first;
    static Board* last;

public:
    // Constructors
    Board();
    Board(string n, int cost, vector<int> payments);

    // Board creation
    static void createFirst(
        string n,
        int cost,
        vector<int> payments
    );

    static void addElement(
        string n,
        int cost,
        vector<int> payments
    );

    static void insertElement(
        string n,
        int cost,
        vector<int> payments,
        int spot
    );

    // Board navigation/search
    static Board* navigate(int spot);

    static Board* findSpot(string s);

    static void removeSpot(string s);

    // Getters
    string getPlaceName() const;
    Board* getNextSpot() const;
    Board* getPre() const;

    int getPrice() const;

    Player* getOwner() const;

    int getLevel() const;

    int getRent() const;

    // Setters
    void setNextSpot(Board* x);
    void setPre(Board* x);

    void setPrice(int x);
    void setOwner(Player* x);
    void setLevel(int x);

    // Landing
    void landOn(Player& player);
};

#endif