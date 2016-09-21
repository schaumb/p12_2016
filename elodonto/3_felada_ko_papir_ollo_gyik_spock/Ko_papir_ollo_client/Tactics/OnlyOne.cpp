//
// Created by Komonyi on 2016.09.22..
//

#include "OnlyOne.hpp"
#include "../RPSLS.hpp"

OnlyOne::OnlyOne(short int x)
{
    if(RPSLS::isValidChoice(x))
    {
        this->myChoice = x;
    }
    else
        this->myChoice = 1;
}

int OnlyOne::getChanceToWin()
{
    return -1000;
}

void OnlyOne::calculateNextChoice() {}