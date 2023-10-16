#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "building.h"
#include "square.h"
#include "state.h"
#include "board.h"

using std::vector;
using std::string;

class Player {
    State state;
    vector<Building*> buildingsOwned; // Vector of squares Player owns 
    bool inTims; // True if Player is in DC Tims line
    bool endOfGame = false;
    int roundsInTims; // If Player in DC Tims line, stores how many rounds Player has been there
    char piece; // Char representing player: 'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'
    string name; // Player name ie. John
    int timsCups; // How many roll up the rim cups Player owns
    int gymsOwned;
    int resOwned; 
    Board *board; // Board the player is playing on 
    
    static int numTimsCups; 

    public:
        Player(Board *b, string playerName, char pieceChosen, int timsCups = 0, int money = 1500, int position = 0, int dcTurns = 0);  // Constructor
        bool canRoll(); // Returns true if player is able to roll (not currently in DC Tims line)
        bool isInTims();
        bool done();
        void bankrupt(); // Clears player's assets
        void setPosition(int pos); // Changes the position of Player and performs appropriate actions
        string print(); // Prints "player1 char TimsCups money position"
        string assets(); // Format: ("Player 1: Property 1, Property 2, Property 3")
        void changeFunds(int change); // Changes funds from Player's assets
        State getState(); // Gets the state (balance, position, bool canRoll) of Player
        void setState(State newState); // Sets the state (balance, position, bool canRoll) of Player
        void roll(); // Rolls dice for Player
        void next(); // Sets current player to be able to roll on next turn
        void trade(Building *b1, Player *p, Building *b2);
        void trade(int price, Player *p, Building *b);
        void trade(Building *b, Player *p, int price);
        char getPiece();

        void addBuilding(Building *b); // Adds building to player's vector
        void removeBuilding(Building *b);
        int getGyms(); // Returns number of gyms Player owns
        int getRes(); // Returns number of residences Player owns
        vector<Building*> getProperties(); // Returns the vector of buidlingsOwned of Player
        int getTimsCups(); // Returns number of tims roll-up-the-rim Player owns
        void setName(std::string s); // Sets name of Player
        string getName(); //return player name
        void setTimsCups(int cups); // Sets number of roll-up-the-rim Player has
        void setBoard(Board *b); // Sets board field of player
        void setInTims(bool t, int rounds); // Sets if player is in tims and how long they have been there
        int getTimsRounds();
        int getWorth(); // Gets players worth (cash + asset worth)
        int getCash(); // Gets players cash (cash + 1/2 asset worth)

        ~Player(); // Destructor

};

#endif
