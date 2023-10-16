#ifndef __BLOCK_H_
#define __BLOCK_H_

#include <string>
#include <vector>

#include "square.h"
#include "player.h"
#include "academic.h"

using std::string;

class Block {
    string block_name;
    std::vector<Academic*> block_members;
    public: 
    Block(string name);
    string getName();
    void addToBlock(Academic *s);
    bool checkMonopoly(Player *p);
    bool hasImprovements();
    ~Block() = default;
};

#endif