#ifndef _STATE_H_
#define _STATE_H_

class Square;

struct State {
    int balance;
    int assets;
    int position;
    bool canRoll;
};

#endif
