#ifndef _ACADEMIC_H_
#define _ACADEMIC_H_

#include <string>
#include <iostream>

#include "building.h"
#include "block.h"

using std::string;

class Academic : public Building {
    Block *block;
    int improvementCost;
    int improvementValue;
    std::vector<int> improvements;
public:
    Academic(std::string name, int p, int ic, std::vector<int> improvs, Block *b);
    int getImprovementCost();
    int getImprovementValue();
    bool upgrade();
    bool sellUpgrade();
    int computeTuition() override;
    void mortgage() override;
    void unmortgage() override;
    std::string print() override;
    void setImprovements(int improve) override;
    bool monopolyHasImprovements();
};

#endif
