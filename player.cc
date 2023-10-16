
#include "player.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std; 

Player::Player(Board *b, string playerName, char pieceChosen, int timsCups = 0, int money = 1500, int position = 0, int dcTurns = 0)
    : state{}
    , buildingsOwned{}
    , inTims{false}
    , roundsInTims{dcTurns}
    , piece{pieceChosen}
    , name{playerName}
    , timsCups{timsCups}
    , gymsOwned{0}
    , resOwned{0}
    , board{b} 
{

    // Initializing State
    State newState; 
    newState.balance = money; 
    newState.assets = 0;   
    newState.position = position;
    state = newState; 

} 

bool Player::canRoll() {
    if (!inTims && state.canRoll) return true; 
    else return false; 
}

void Player::bankrupt() {

    // Remove all properties
    buildingsOwned.clear(); 

    // Clear tims cups
    numTimsCups -= timsCups; 
    timsCups = 0;

    //set end of game (bankrupt bool)
    endOfGame= true;
    return;
}

bool Player::done() {return endOfGame;}

void Player::setPosition(int pos) { 
    if ((state.position == 30 && pos == 10) || !state.canRoll) {
        inTims = true;
        roundsInTims = 0;
    } else if (pos > 40) changeFunds(200);

    Square *old = board->getSquare(state.position);
    old->detach(this);
    state.position = pos%40;
	Square *next = board->getSquare(state.position);
	next->attach(this);
    
    return;
}

string Player::print() {
    int position = state.position; 
    string print = name;
    print += " ";
    print += piece; 
    print += " ";
    print += to_string(timsCups);
    print += " ";
    print += to_string(state.balance);
    print += " ";

    // If player is at Tims
    if (position == 10) {

        // If player is at Tims and in Tims line
        if (inTims) {
            print += "10 1 ";
            print += to_string(roundsInTims); 
        
        // If player is at Tims but not in Tims line
        } else print += "10 0";

    } else print += to_string(position); 
    print += "\n";
    return print; 
}



// Format: ("Player 1: Property 1, Property 2, Property 3")
string Player::assets() {
    string print = name; 
    print += ":\n"; 
    print += "Balance: $" + std::to_string(getState().balance) + "\n";
    
    /*
    int numAssets = buildingsOwned.size();
    for (int i = 0; i < numAssets; i++) {
        print += buildingsOwned[i]->getName() + ", Value: $" + std::to_string(buildingsOwned[i]->getCost()); 
        if (i != numAssets-1) print += "\n"; 
    }  
    print += "\n";
    */

    for (auto b : buildingsOwned) {
        print += b->getName() + ", Value: $" + std::to_string(b->getCost()) + "\n";
    }
    return print; 
}

// Changes funds from Player's assets
void Player::changeFunds(int change) {
    state.balance += change;
    return;
}

// Gets the state (balance, position, bool canRoll) of Player
State Player::getState(){ return state; } 

// Sets the state (balance, position, bool canRoll) of Player
void Player::setState(State newState) { state = newState; }

void Player::roll() {
    state.canRoll = false;
    return;  
}

// Sets current player to be able to roll on next turn
void Player::next() {
    state.canRoll = true; 
    return;
}

void Player::trade(Building *b1, Player *p, Building *b2) {
    //remove old buildings
    removeBuilding(b1);
    p->removeBuilding(b2);

    //add buildings
    addBuilding(b2);
    p->addBuilding(b1);

    //set ownership
    b1->setOwner(p);
    b2->setOwner(this);

    return;
}

void Player::trade(int price, Player *p, Building *b) {
    //remove building
    p->removeBuilding(b);

    //set ownership and add building
    addBuilding(b);
    b->setOwner(this);

    //change funds
    changeFunds(-price);
    p->changeFunds(price);
    
    return;
}

void Player::trade(Building *b, Player *p, int price) {
    //remove building
    removeBuilding(b);

    //addBuilding
    p->addBuilding(b);
    b->setOwner(p);

    //change funds
    p->changeFunds(-price);
    changeFunds(price);

    return;
}


char Player::getPiece() {return piece;}

// Adds building to player's vector
void Player::addBuilding(Building *b) {
    buildingsOwned.push_back(b);
    SquareType type = b->getType();
    if (type == SquareType::Gym) {
        gymsOwned++;
    } else if (type == SquareType::Residence) {
        resOwned++;
    }
    return;
}

void Player::removeBuilding(Building *b) {
    buildingsOwned.erase(remove(buildingsOwned.begin(), buildingsOwned.end(), b), buildingsOwned.end());
    SquareType type = b->getType();
    if (type == SquareType::Gym) {
        gymsOwned--;
    } else if (type == SquareType::Residence) {
        resOwned--;
    }
    return;
}


// Returns number of gyms Player owns
int Player::getGyms() { return gymsOwned; }

// Returns number of residences Player owns
int Player::getRes() { return resOwned; }

// Returns the vector of buildingsOwned of Player
vector<Building*> Player::getProperties() { return buildingsOwned; }

// Returns number of tims roll-up-the-rim Player owns
int Player::getTimsCups() { return timsCups; }

// Sets name of Player
void Player::setName(std::string s) { name = s;}

std::string Player::getName() {return name;}

void Player::setTimsCups(int cups) { // Sets number of roll-up-the-rim Player has
    timsCups = cups;
    return;
}


// Sets if player is in tims and how long they have been there
void Player::setInTims(bool t, int rounds) {
    inTims = t; 
    roundsInTims = rounds;
    return;
}

int Player::getTimsRounds() {return roundsInTims;}

// Sets board field of player
void Player::setBoard(Board *b) { board = b; } 

// Gets players worth (cash + asset worth)
int Player::getWorth() {
    State playerState = this->getState();
    int worth = playerState.balance;
    for (auto b: buildingsOwned) {
        worth += b->getCost();
        if (b->getType() == SquareType::Academic && !b->isMortgaged()) {
            Academic *a = static_cast<Academic*>(b);
            worth += a->getImprovementValue() * a->getImprovementCost(); 
        }
    }
    return worth;
} 

// Gets players cash (cash + 1/2 asset worth)
int Player::getCash() {
    State playerState = this->getState();
    int cash = playerState.balance;
    
    for (auto b: buildingsOwned) {
        // if not mortgaged
        cash += b->getCost() / 2; 
        if (b->getType() == SquareType::Academic && !b->isMortgaged()) {
            Academic *a = static_cast<Academic*>(b);
            // if not acamdeic 
            cash += (a->getImprovementValue() * a->getImprovementCost()) / 2;
        }
    }
    return cash;
} 

// Destructor
Player::~Player() {
    buildingsOwned.clear();
    buildingsOwned.shrink_to_fit();
} 
