#include "game.h"
#include "building.h"
#include "player.h"
#include "board.h"
#include "state.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;  

// Constructor
Game::Game(bool t = false, bool l = false): testing{t}, loaded{l}, board{}, currentPlayer{} {
    board = Board{};
    board.init();
}

void Game::loadProperty(string s) {

    string word;
    int improvements;
    istringstream ss{s};
    

    // Get property object
    ss >> word; 
    Building *property = board.getBuilding(word);
    
    // Set ownership
    ss >> word;
    Player *p = board.getPlayer(word);
    if (p) {
        property->setOwner(p);
        
        // Add to player's buildingsOwned
        p->addBuilding(property);

        // Get improvements as int
        if (ss >> word) {
            improvements = stoi(word); 

            // Set improvements
            property->setImprovements(improvements);
        }
    }
}
    


void Game::loadPlayer(string playerDetails, bool first) { 
    
    string word;
    int position;
    int cups; 
    istringstream ss{playerDetails};

    // Get player object, add to board
    string name;
    ss >> name; 

    // Set players piece char
    ss >> word; 
    char piece = word[0];

    Player *p = new Player {&board, name, piece};

    // Set players roll-up-the-rim cups
    ss >> word; 
    stringstream ss2; 
    ss2 << word;
    ss2 >> cups; 
    p->setTimsCups(cups);


    // Set player balance
    ss >> word; 
    stringstream ss3; 
    int money;
    ss3 << word;
    ss3 >> money; 
    State newState; 
    newState.balance = money; 


    // Set player position
    ss >> word;
    stringstream ss4;
    int position; 
    ss4 << word;
    ss4 >> position;
    newState.position = position;
    board.getSquare(position)->attach(p);
    if (position == 10) { 
        ss >> word; 
        stringstream ss5;
        int tims;
        ss5 << word;
        ss5 >> tims; 
        if (tims == 0) p->setInTims(false, 0);
        else {
            ss >> word; 
            stringstream ss6;
            int rounds;
            ss6 << word;
            ss6 >> rounds; 
            p->setInTims(true, rounds);

        }
    }
    p->setState(newState);
    if (first) currentPlayer = p; 
    board.addPlayer(p);
}
    

// Loads in previously existing game
void Game::load(ifstream &ss) {

    string s; 
    ss >> s; 
    int numPlayers = stoi(s); 
    for (int i = 0; i < numPlayers; i++) {
        ss >> s;
        if (i == 0) loadPlayer(s, true);
        else loadPlayer(s, false);
    }
    while (ss >> s) {
        loadProperty(s);
    }

}

// Saves current game
void Game::save() {
    string file;
    cin >> file;
    ofstream savedGame (file); 
    while (true) {
        if (savedGame.is_open()) {
            board.save(savedGame);
            break;
        } else {
            cout << "File could not be opened, please enter valid file name: ";
        }
    }
    return;
}

// Executes game
void Game::play() {
    string cmd; 
    if (!loaded) readPlayers(); 
    
    
    cout << currentPlayer->getName() << ", enter a command, or enter 'c' for list of commands: "; 
    while (cin >> cmd) {
        
        if (currentPlayer->isInTims()) {
            board.getSquare(10)->landedOn(currentPlayer);
        }
        if (cmd == "c") {
            cout << "Available commands:" << endl; 
            cout << "'roll' - roll 2 dice, if in testing mode input 2 values for dice" << endl;
            cout << "'next' - give control to next player" << endl;
            cout << "'trade' <name of player trading with> <give> <receive> - attempt a trade" << endl;
            cout << "'improve' <property> <buy/sell> - improve or sell improvements of property" << endl;
            cout << "'mortgage' <property> - attempt to mortage property" << endl;
            cout << "'unmortgage' <property> - attempt to unmortage property " << endl;
            cout << "'assets' - print your assets" << endl;
            cout << "'all' - print all players' assets" << endl;
            cout << "'save' - save and quit current game" << endl;
            cout << "'quit' - quit current game" << endl;
        } else if (cmd == "roll") { // Player rolls two dice OR if -testing, takes input for dice
            if (currentPlayer->canRoll()) {
                if (testing) { 
                    string word;
                    cin >> word;
                    int dice1 = stoi(word); 
                    cin >> word; 
                    int dice2 = stoi(word);
                    board.roll(dice1, dice2);
                } else {
                    board.roll();
                }
            } else cout << "Sorry you cannot roll" << endl;

        } else if (cmd == "next") { // Gives control to next payer
            currentPlayer = board.next(); 
        } else if (cmd == "trade") { // Executes sa trade between current player and input player
            string name; cin >> name;
            string give; cin >> give;
            string receive; cin >> receive;
            board.trade(name, give, receive);
        } else if (cmd == "improve") { // Attemps to improve property
            string property; 
            cin >> property;
            string buyOrSell;
            cin >> buyOrSell;
            Building *b = board.getBuilding(property);
            if (!b) { 
                cout << "Sorry, that building does not exist." << endl; 
            } else {
                if (b->getType() != SquareType::Academic) cout << "Sorry,  you can only improve academic buildings" << endl;
                else {
                    Academic *a = static_cast<Academic*>(b);
                    if (a->getOwner() != currentPlayer) cout << "Sorry, you do not own " << a->getName() << endl;
                    else {
                        if (buyOrSell == "buy") a->upgrade();
                        else if (buyOrSell == "sell") a->sellUpgrade();
                        else cout << "Invalid command, please enter \"improve <property> buy/sell\"" << endl;
                    }
                }
            }
        } else if (cmd == "mortgage") { // Attemps to mortgage property
            string property; 
            cin >> property;   
            Building *b = board.getBuilding(property);
            if (!b) { 
                cout << "Sorry that building does not exist." << endl; 
            } else {
                if (b->getType() != SquareType::Academic) cout << "Sorry you can only mortgage academic buildings" << endl;
                else {
                    Academic *a = static_cast<Academic*> (b);
                    a->mortgage();
                }
            } 

        } else if (cmd == "unmortgage") { // Attempts to unmortgage property
            string property; 
            cin >> property;   
            Building *b = board.getBuilding(property);
            if (!b) { 
                cout << "Sorry that building does not exist." << endl; 
            } else {
                if (b->getType() != SquareType::Academic) cout << "Sorry you can only mortgage academic buildings" << endl;
                else {
                    Academic *a = static_cast<Academic*> (b);
                    a->unmortgage();
                }
            } 
        } else if (cmd == "assets") { 
            currentPlayer->assets();
        } else if (cmd == "all") { // Display assets of every player
            board.all();
        } else if (cmd == "save") {
            save();
            cout << "Game saved." << endl;
            break;
        } else if (cmd == "quit") {
            cout << "Would you like to save your game?" << endl;
            cout << "Enter 'yes' to save, any key to quit without saving: ";
            string ans; 
            cin >> ans; 
            if (ans == "yes") {
                save();
                cout << "Game saved." << endl;
            } 
            cout << "Game quit." << endl;
            cout << "Thanks for Playing!" << endl;
            break;
        } else  {
            cout << "Invalid entry, please try again." << endl;
        }
        board.display();
        if (board.getPlayers().size() == 1) {
            cout << "Congratulations " << board.getPlayers()[0] << "!. You are the last player left, you won!" << endl;
            cout << "Would you like to save your game?" << endl;
            cout << "Enter 'yes' to save, any key to quit without saving: ";
            string ans; 
            cin >> ans; 
            if (ans == "yes") {
                save();
                cout << "Game saved." << endl;
            } 
            cout << "Game quit." << endl;
            cout << "Thanks for Playing!" << endl;
            break;
        }
        cout << currentPlayer->getName() << ", enter a command, or enter 'c' for list of commands: "; 
    }


}

// reads in player names and chosen pieces for new game
void Game::readPlayers() {
    string name; 
    int numPlayers; 
    string stringP;
    char p;
    string word; 
    cout << "Please enter number of players: "; 
    
    // Get numPlayers
    while (true) {
        cin >> word;
        stringstream ss; 
        ss << word;
        ss >> numPlayers;

        if (numPlayers < 2 || numPlayers > 7) {
            cout << "Invalid number of players, please enter value [2-7]: ";
        } else {
            break;
        }
    }
    vector<string> names; // vector for keeping track of taken names
    vector<char> pieces; // vector for keeping track of taken pieces

    // Add each player to game
    for (int i = 0; i < numPlayers; i++) {
        
        // Reading in player's name
        cout << "Player " << i+1 << " , please enter name: ";
        while (true) {
            bool taken = false;
            cin >> name;
            // Check name is valid
            if (name != "BANK") {
                for (string n : names) { if (n == name) taken = true; }
                if (taken) cout << "That name is already taken, please try again: ";
                else { names.push_back(name); break;}
            } else cout << "Player name cannot be BANK, please try again: "; 
        }
        
        // Reading in player's piece choice
        cout << name << ", Please enter a char from pieces 'G', 'B', 'D', 'P', 'S', '$', 'L', 'T': ";
        while (true) {
            bool taken = false;
            cin >> stringP; 
            if (stringP.length() > 1) cout << "Please enter only 1 character from 'G', 'B', 'D', 'P', 'S', '$', 'L', 'T': ";
            else {
                p = stringP[0]; // convert string to char

                // Check p is valid
                if (p == 'G' || p == 'B'|| p == 'D' || p== 'P' || p =='S' || p == '$'|| p == 'L' || p == 'T') {
                    for (char pc : pieces) { if (pc == p) taken = true; }
                    if (taken) cout << "That piece is already taken, please try again: ";
                    else { pieces.push_back(p); break;}
                } else cout << "Invalid entry. Please enter only a character from 'G', 'B', 'D', 'P', 'S', '$', 'L', 'T': ";
            }
        }

        Player *newPlayer = new Player{&board, name, p}; 
        board.addPlayer(newPlayer);
        board.getSquare(0)->attach(newPlayer);
        
        // If first player, set currentPlayer to newPlayer
        if (i = 0) currentPlayer = newPlayer; 
    }
    
}

