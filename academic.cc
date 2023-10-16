#include "academic.h"

Academic::Academic(std::string name, int p, int ic,  std::vector<int> improvs, Block *b)
    : Building{name, SquareType::Academic, p}
    , improvementCost(ic)
    , improvementValue{0}
    , improvements{improvs}
    , block{b}
{}

int Academic::getImprovementCost() {return improvementCost;}

int Academic::getImprovementValue() {return improvementValue;}

bool Academic::upgrade() {
    if (block->checkMonopoly(owner)) {
        if (improvementValue < 5) {
            improvementValue++;
            return true;
        } else {
            std::cout << "Sorry, you cannot improve " << name << " any further." << std::endl;
            return false;
        }
    } else {
        std::cout << "Sorry, you do not own the monopoly for " << block->getName() << "." << std::endl;
        return false;
    }
}

bool Academic::sellUpgrade() {
    if (improvementValue < 1) {
        std::cout << "Sorry, you have no improvements to sell for " << name << "." << std::endl;
    }
}

int Academic::computeTuition() {
    if (mortgaged) {
        return 0;
    } if (block->checkMonopoly(owner)) {
        if (improvementValue == 0) return 2*improvements[0];
        else return improvements[improvementValue];
    } else {
        return improvements[0];
    }
}

void Academic::mortgage() {
    mortgaged = true;
    improvementValue = -1;
    return;
} 

void Academic::unmortgage() {
    improvementValue = 0;
    mortgaged = false;
    return;
}

std::string Academic::print() {
   std::string out = getName();
    out += " ";
    if (owner) {
        out += owner->getName();
    } else {
        out += "BANK";
    }
    out += " ";
    out += std::to_string(improvementValue);
    return out;
}

void Academic::setImprovements(int improve) {
    if (improve == -1) {
        mortgaged = true;
    }
    improvementValue = improve;
    return;
}

bool Academic::monopolyHasImprovements() {
    return block->hasImprovements();
}
