#ifndef _RESIDENCE_H
#define _RESIDENCE_H_

#include "building.h"

class Player;
class Residence : public Building {
public:
    Residence(std::string name);
    int computeTuition() override ;
    void mortgage() override;
    void unmortgage() override;
    std::string print() override;
    void setImprovements(int improve) override;
};

#endif
