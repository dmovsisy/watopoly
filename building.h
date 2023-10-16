#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <vector>
#include "square.h"
#include "player.h"

class Building : public Square {
protected:
    Player *owner;
    int purchaseCost;
    bool mortgaged;
public:
    Building(std::string name, SquareType t, int p);
    bool isOwned();
    bool isMortgaged();
    Player* getOwner();
    void setOwner(Player *p);
    int getCost();
    void purchase(Player *p);
    void landedOn(Player *p) override;
    virtual int computeTuition() = 0;
    virtual void mortgage() = 0;
    virtual void unmortgage() = 0;
    virtual std::string print() = 0;
    virtual void setImprovements(int improve) = 0;
};

#endif
