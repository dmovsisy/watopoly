#include "block.h"

Block::Block(string name) : block_name{name} {}

string Block::getName() {return block_name;}

void Block::addToBlock(Academic *s) {
    block_members.push_back(s);
    return;
}

bool Block::checkMonopoly(Player *p) {
    for (auto &a : block_members) {
        if (a->getOwner() != p || a->isMortgaged()) return false;
    }

    return true;
}

bool Block::hasImprovements() {
    for (auto &a : block_members) {
        if (a->getImprovementValue() > 0) return true;
    }
    return false;
}