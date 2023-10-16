#ifndef _ADMINSQUARE_H_
#define _ADMINSQUARE_H_

#include "square.h"

class adminSquare : public Square {
public:
    adminSquare(std::string name);
    virtual void landedOn(Player *p) = 0;
};

class collectOSAP : public adminSquare {
    public:
    collectOSAP();
    void landedOn(Player *p) override;
};

class goToTims : public adminSquare {
    public:
    goToTims();
    void landedOn(Player *p) override;
};

class DCTimsLine : public adminSquare {
    public:
    DCTimsLine();
    void landedOn(Player *p) override;
};

class gooseNesting : public adminSquare {
    public:
    gooseNesting();
    void landedOn(Player *p) override;
};

class Tuition : public adminSquare {
    public:
    Tuition();
    void landedOn(Player *p) override;
};

class coopFee : public adminSquare {
    public:
    coopFee();
    void landedOn(Player *p) override;
};

class SLC : public adminSquare {
    public:
    SLC();
    void landedOn(Player *p) override;
};

class needlesHall : public adminSquare {
    public:
    needlesHall();
    void landedOn(Player *p) override;
};

#endif
