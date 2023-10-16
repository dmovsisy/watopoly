#include "square.h"
#include <algorithm>

Square::Square(std::string name, SquareType t) : name{name}, type{t} {}

void Square::setBoard(Board *b) {
    board = b;
    return;
}

std::vector<Player*> Square::getPlayersOnSquare() {
    return playersOnBoard;
}

void Square::attach(Player *p) {
    playersOnBoard.push_back(p);
    return;
}

void Square::detach(Player *p) {
    playersOnBoard.erase(std::remove(playersOnBoard.begin(), playersOnBoard.end(), p), playersOnBoard.end());
    return;
}

bool Square::isOn(Player *p) {
    for (auto &pob : playersOnBoard) {
        if (pob == p) return true;
    }

    return false;
}

SquareType Square::getType() {return type;}

std::string Square::getName() {return name;}

Square::~Square() {}