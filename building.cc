#include "building.h"

Building::Building(std::string name, SquareType t, int p)
    : Square{name, t}
    , purchaseCost{p}
    , mortgaged{false}
{}

bool Building::isOwned() {return (owner == nullptr);}

bool Building::isMortgaged() {return mortgaged;}

Player* Building::getOwner() {return owner;}

void Building::setOwner(Player *p) {
    owner = p;
    return;
}

int Building::getCost() {return purchaseCost;}

void Building::purchase(Player *p) {
    setOwner(p);
    p->addBuilding(this);
    return;
}

void Building::landedOn(Player *p) {
    if (isOwned()) {
        Player *owner = getOwner();
        if (p == owner) {
            std::cout << "You own " << getName() << "." << std::endl;
        } else {
            int charge = computeTuition(); 
            std::cout << "You owe $" << charge << " to " << (owner ? owner->getName() : "the Bank") << "." << std::endl;
            if (charge > p->getState().balance) {
                board->bankrupt(charge, owner);
            } else {
                p->changeFunds(-charge);
                if (owner) owner->changeFunds(charge);
                std::cout << "Your current balance is $" << p->getState().balance << "." << std::endl;
            }
        }
    } else {
        board->purchase(this);
    }
    return;
}