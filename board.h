#ifndef __BOARD_H__
#define __BOARD_H__

#include "player.h"
#include "square.h"
#include "block.h"
#include <string>
#include <fstream>

class Board {
    std::vector<Square*> boardSquares;
    std::vector<Player*> players;
    int boardSize;
    Player *currentPlayer;
    int curPindex = 0;
    
    int availableTimsCups;

    Block Arts1{"Arts1"};
    Block Arts2{"Arts2"};
    Block Eng{"Eng"};
    Block Health{"Health"};
    Block Env{"Env"};
    Block Sci1{"Sci1"};
    Block Sci2{"Sci2"};
    Block Math{"Math"};

    public:
    Board();
    ~Board();
    void init();
    int availableCups();
    void givingAwayTimsCup();
    void timsCupsUsed(int c = 1);
    Square* getSquare(int pos);
    Building* getBuilding(std::string name);
    void addPlayer(Player *p);
    Player *getPlayer(std::string name);
    void roll();
    void roll(int v1, int v2);
    Player* next();
    void purchase(Building *b);
    void trade(std::string give, std::string name, std::string receive);
    void improve();
    void mortgage(Building *b);
    void unmortgage(Building *b);
    void bankrupt(int charge, Player *owed);
    void auction(Building *b, Player *noBid);
    void assets();
    void all();
    void save(std::ofstream &out);
    void printplayers(int i);
    void printImprovements(int i);
    void display();
    vector<Player*> getPlayers();
};

#endif

