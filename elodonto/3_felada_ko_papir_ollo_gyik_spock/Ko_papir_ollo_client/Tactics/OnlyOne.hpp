//
// Created by Komonyi on 2016.09.22..
//

#ifndef KO_PAPIR_OLLO_CLIENT_ONLYONE_HPP
#define KO_PAPIR_OLLO_CLIENT_ONLYONE_HPP

#include "../Tactic.hpp"

class OnlyOne : public Tactic {
public:
    OnlyOne(short int x);

    int getChanceToWin();

    void calculateNextChoice() {};
};


#endif //KO_PAPIR_OLLO_CLIENT_ONLYONE_HPP
