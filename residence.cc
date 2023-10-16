#include <iostream>

#include "residence.h"

Residence::Residence(std::string name) : Building{name, SquareType::Residence, 200} {}

int Residence::computeTuition() {
    if (mortgaged) return 0;

    int res = owner->getRes();

    int ret = 0;
    switch (res) {
        case 1:
            ret = 25;
            break;
        case 2:
            ret = 50;
            break;
        case 3:
            ret = 100;
            break;
        case 4:
            ret = 200;
            break;
        default:
            break;
    }

    return ret;
}

void Residence::mortgage() {
    mortgaged = true;
    return;
}

void Residence::unmortgage() {
    mortgaged = false;
    return;
}

std::string Residence::print() {
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

void Residence::setImprovements(int improve) {
    if (improve == -1) mortgaged = true;
    return;
}