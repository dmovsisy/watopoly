#include <iostream>

#include "gym.h"
#include "dice.h"

Gym::Gym(std::string name) : Building{name, SquareType::Gym, 150} {}

int Gym::computeTuition() {
    if (mortgaged) return 0;

    int gyms = owner->getGyms();

    Dice d = Dice();
    d.roll();

    std::cout << "You rolled a total value of " << d.getValue() << "." << std::endl; 

    if (gyms == 1) {
        return 2*d.getValue();
    } else if (gyms == 2) {
        return 4*d.getValue();
    }

    //should not reach this line of execution
    return 0;
}

void Gym::mortgage() {
    mortgaged = true;
    return;
}

void Gym::unmortgage() {
    mortgaged = false;
    return;
}

std::string Gym::print() {
    std::string out = getName();
    out += " ";
    if (owner) {
        out += owner->getName();
    } else {
        out += "BANK";
    }
    out += " ";
    if (mortgaged) {
        out += std::to_string(-1);
    } else {
        out += std::to_string(0);
    }
    return out;
}

void Gym::setImprovements(int improve) {
    if (improve == -1) mortgaged = true;
    return;
}