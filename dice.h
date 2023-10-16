#ifndef __DICE_H_
#define __DICE_H_

#include <random>
#include <chrono>

class Dice {
    int val1;
    int val2;
    int value;
    bool doubles;
    public:
    Dice();
    ~Dice();
    void roll();
    void roll(int v1, int v2);
    int getValue();
    int getVal1();
    int getVal2();
    bool isDouble();
};

#endif