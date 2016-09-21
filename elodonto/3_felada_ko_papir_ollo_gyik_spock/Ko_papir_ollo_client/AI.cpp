//
// Created by Komonyi on 2016.09.21..
//

#include "AI.hpp"
#include "Tactics/OnlyOne.hpp"

AI::AI() {};

AI::AI(std::string t)
{
    if(t == "")
    {
        //this->AI();
    }
    else if(t == "OnlyRock")
    {
        this->tactics.push_back(new OnlyOne(1));
    }
    else if(t == "OnlyPaper")
    {
        this->tactics.push_back(new OnlyOne(2));
    }
    else if(t == "OnlyScissor")
    {
        this->tactics.push_back(new OnlyOne(3));
    }
    else if(t == "OnlyLizard")
    {
        this->tactics.push_back(new OnlyOne(4));
    }
    else if(t == "OnlySpock")
    {
        this->tactics.push_back(new OnlyOne(5));
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

        auto it = this->tactics.begin();
        while(it != this->tactics.end())
        {
            (*it)->addChoices(this->myChoice, this->enemyChoice);

            it++;
        }
    }
}

void AI::calculateNextChoice()
{
    Tactic *bestTactic = nullptr;

    auto it = this->tactics.begin();
    while(it != this->tactics.end())
    {
        (*it)->calculateNextChoice();
        if(bestTactic == nullptr || bestTactic->getChanceToWin() < (*it)->getChanceToWin())
        {
            bestTactic = *it;
        }

        it++;
    }

    if(bestTactic != nullptr)
    {
        this->myChoice = bestTactic->getChoice();
        bestTactic->markAsUsed();
    }
    else
        this->myChoice = 1;
}

std::ostream& operator<<(std::ostream &o, const AI &bela)
{
    o << bela.currentGame;
    return o;
}