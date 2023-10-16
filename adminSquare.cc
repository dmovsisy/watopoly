#include "adminSquare.h"
#include "player.h"
#include "state.h"
#include "dice.h"

#include <random>
#include <chrono>

adminSquare::adminSquare(std::string name) : Square{name, SquareType::Admin} {}

collectOSAP::collectOSAP() : adminSquare{"Collect OSAP"} {}

void collectOSAP::landedOn(Player *p) {
    p->changeFunds(200);
    return;
}

goToTims::goToTims() : adminSquare{"Go To Tims"} {}

void goToTims::landedOn(Player *p) {
    p->setPosition(10);
    return;
}

DCTimsLine::DCTimsLine() : adminSquare{"DC Tims Line"} {}

void DCTimsLine::landedOn(Player *p) {
    //DCTims line procedure
    if (p->isInTims()) {
        int rounds = p->getTimsRounds();
        rounds++;
        Dice d = Dice();
        std::cout << "Welcome to Tims! You may leave by rolling doubles [1], paying $50 [2], or using a roll up the rim cup [3]: ";
        std::string res;
        std::cin >> res;
        while (true) {
            if (res == "3" && p->getTimsCups() > 0) break;
            else if (res == "3" && !p->getTimsCups()) {
                std::cout << "You do not have a Tims Cup! Please try a valid option: ";
                continue;
            } else if (res == "1" || res == "2") break;
            
            std::cout << "Pleaes enter 1, 2, or 3 for the corresponding options: ";
        }

        if (res == "1") {
            d.roll();
            if (d.isDouble()) {
                std::cout << "You rolled doubles! You have moved forward " << d.getValue() << " spaces.";
                p->setPosition(p->getState().position + d.getValue());
                p->setInTims(false, 0);
                board->getSquare(p->getState().position)->landedOn(p);
                return;
            } 
        } else if (res == "2") {
            if (50 > p->getState().balance) {
                board->bankrupt(50, nullptr);
            } else {
                p->changeFunds(-50);
                p->setInTims(false, 0);
                return;
            }
        } else if (res == "3") {
            int cups = p->getTimsCups();
            --cups;
            p->setTimsCups(cups);
            board->timsCupsUsed();
            p->setInTims(false, 0);
            return;
        }
        if (rounds == 3) {
            std::cout << "You have spent 3 turns in line! You must leave by paying $50 [1] or using a roll up the rim cup [2]: ";
            while (true) {
                if (res == "2" && p->getTimsCups() > 0) break;
                else if (res == "2" && !p->getTimsCups()) {
                    std::cout << "You do not have a Tims Cup! Please try a valid option: ";
                    continue; 
                } else if (res == "1") break;
                
                std::cout << "Pleaes enter 1 or 2 for the corresponding options: ";
            }
            if (res == "1") {
                if (50 > p->getState().balance) {
                    board->bankrupt(50, nullptr);
                } else {
                    p->changeFunds(-50);
                    p->setInTims(false, 0);
                    return;
                }
            } else if (res == "2") {
                int cups = p->getTimsCups();
                --cups;
                p->setTimsCups(cups);
                board->timsCupsUsed();
                p->setInTims(false, 0);
                return;
            }
            p->setPosition(p->getState().position + d.getValue());
            p->setInTims(false, 0);
            board->getSquare(p->getState().position)->landedOn(p);
        }
    }
    return;
}

gooseNesting::gooseNesting() : adminSquare{"Goose Nesting"} {}

void gooseNesting::landedOn(Player *p) {
    return;
}

Tuition::Tuition() : adminSquare{"Tuition"} {}

void Tuition::landedOn(Player *p) {
    //Tuition line procedure
    std::cout << "You must pay either $300 [1] or 10% of your net worth [2]: ";
    std::string res;
    std::cin >> res;
    while (true) {
        if (res == "1" || res == "2") break;
        else {
            std::cout << "Please enter 1 or 2: ";
            std::cin >> res;
        }
    }

    int fee = 0;
    if (res == "1") {
        fee = 300;
    } else {
        fee = 0.1*(p->getWorth());
    }

    if (fee > p->getState().balance) {
        board->bankrupt(fee, nullptr);
    } else {
        p->changeFunds(-fee);
        std::cout << "You paid $" << fee << std::endl;
        std::cout << "Your current balance is $" << p->getState().balance << "." << std::endl;
    }
    return;
}

coopFee::coopFee() : adminSquare{"Co-op Fee"} {}

void coopFee::landedOn(Player *p) {
    std::cout << "You owe $" << 150 << " to the Bank." << std::endl;
    if (150 > p->getState().balance) {
        board->bankrupt(150, nullptr);
    } else {
        p->changeFunds(-150);
        std::cout << "Your current balance is $" << p->getState().balance << "." << std::endl;
    }
    return;
}

SLC::SLC() : adminSquare{"SLC"} {}

void SLC::landedOn(Player *p) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (board->availableCups()) {
        std::default_random_engine rng{seed};
        std::uniform_int_distribution<int> dist(1,100);

        if (dist(rng) == 1) {
            board->givingAwayTimsCup();
            p->setTimsCups(p->getTimsCups() + 1);
            return;
        }
    } 

    std::default_random_engine rng{seed};
    std::uniform_int_distribution<int> dist(0,23);

    int randInt = dist(rng);
    int curPos = p->getState().position;
    if (randInt < 3) { //0, 1, 2 (3/24 = 1/8)
        p->setPosition((curPos-3)%40);
    } else if (randInt < 7) { //3, 4, 5, 6 (4/24 = 1/6)
        p->setPosition((curPos-2)%40);
    } else if (randInt < 12) { //7, 8, 9, 10
        p->setPosition((curPos-1)%40);
    } else if (randInt < 14) { //11, 12, 13
        p->setPosition((curPos+1)%40);
    } else if (randInt < 18) { //14, 15, 16, 17
        p->setPosition((curPos+2)%40);
    } else if (randInt < 22) { //18, 19, 20, 21
        p->setPosition((curPos+3)%40);
    } else if (randInt < 23) {//22
        p->setPosition(30);
    } else {
        p->setPosition(0);
    }

}

needlesHall::needlesHall() : adminSquare{"Needles Hall"} {}

void needlesHall::landedOn(Player *p) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (board->availableCups()) {
        std::default_random_engine rng{seed};
        std::uniform_int_distribution<int> dist(1,100);

        if (dist(rng) == 1) {
            board->givingAwayTimsCup();
            p->setTimsCups(p->getTimsCups() + 1);
            return;
        }
    } 

    std::default_random_engine rng{seed};
    std::uniform_int_distribution<int> dist(0,17);

    int randInt = dist(rng);
    int curBal = p->getState().balance;
    if (randInt < 1) {
        if (curBal < 200) board->bankrupt(200, nullptr);
        else p->changeFunds(-200);
    } else if (randInt < 3) { 
        if (curBal < 100) board->bankrupt(200, nullptr);
        else p->changeFunds(-100);
    } else if (randInt < 6) { 
        if (curBal < 50) board->bankrupt(200, nullptr);
        else p->changeFunds(-50);
    } else if (randInt < 12) { 
        p->changeFunds(25);
    } else if (randInt < 15) { 
        p->changeFunds(50);
    } else if (randInt < 17) { 
        p->changeFunds(100);
    } else {
        p->changeFunds(200);
    }
}
