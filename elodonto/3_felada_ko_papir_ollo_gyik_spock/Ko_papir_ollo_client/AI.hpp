//
// Created by Komonyi on 2016.09.21..
//

#ifndef KO_PAPIR_OLLO_CLIENT_AI_HPP
#define KO_PAPIR_OLLO_CLIENT_AI_HPP

#include "RPSLS.hpp"
#include "Tactic.hpp"
#include <list>

class AI {
private:
    RPSLS currentGame;
    short int myChoice = 0, enemyChoice = 0;
    std::list<Tactic*> tactics;

public:

    AI();
    AI(std::string t);

    short int getChoice() const;
    void setEnemyChoice(short int a);

    void calculateNextChoice();


    friend std::ostream& operator<<(std::ostream &o, const AI &bela);

};


#endif //KO_PAPIR_OLLO_CLIENT_AI_HPP
