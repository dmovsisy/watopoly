#ifndef _GYM_H
#define _GYM_H

#include "building.h"

class Gym : public Building {
public:
    Gym(std::string name);
    int computeTuition() override;
    void mortgage() override;
    void unmortgage() override;
    std::string print() override;
    void setImprovements(int improve) override;
};

#endif
