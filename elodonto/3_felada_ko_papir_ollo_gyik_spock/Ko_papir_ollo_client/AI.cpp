//
// Created by Komonyi on 2016.09.21..
//

#include "AI.hpp"

AI::AI() {};

AI::AI(std::string t)
{
    if(t == "")
    {
        this->AI();
    }
}

short int AI::getChoice() const
{
    return this->myChoice;
}

void AI::setEnemyChoice(short int a)
{
    if(RPSLS::isValidChoice(a))
    {
        this->enemyChoice = a;
        this->currentGame.addChoices(this->myChoice, this->enemyChoice);
    }
}

void AI::calculateNextChoice()
{
    this->myChoice = 1;
}

std::ostream& operator<<(std::ostream &o, const AI &bela)
{
    o << bela.currentGame;
    return o;
}