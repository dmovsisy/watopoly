#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <string>
#include <vector>

class Player;
class Board;

enum class SquareType {Admin, Academic, Residence, Gym};
class Square {
protected:
    static Board *board;
    std::string name;
    std::vector<Player*> playersOnBoard;
    SquareType type;
public:
    Square(std::string name, SquareType t);
    static void setBoard(Board *b);
    std::vector<Player*> getPlayersOnSquare();
    virtual void landedOn(Player *p) = 0;
    void attach(Player *p);
    void detach(Player *p);
    bool isOn(Player *p);
    SquareType getType();
    std::string getName();
    virtual ~Square();
};

#endif
