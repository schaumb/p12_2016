#include "RPSLS.hpp"
#include <iostream>

RPSLS::RPSLS() {}

RPSLS::RPSLS(std::string a, std::string b)
{
    this->Player1Name = a;
    this->Player2Name = b;
}

void RPSLS::addChoices(short int a, short int b)
{
    if(RPSLS::isValidChoice(a) && RPSLS::isValidChoice(b))
    {
        this->Player1Choices.push_back(a);
        this->Player2Choices.push_back(b);

        this->lastWinner = RPSLS::getWinner(a, b);

        switch(this->lastWinner)
        {
            case 0: this->Player1Stat.draws++; this->Player2Stat.draws++; break;
            case 1: this->Player1Stat.victories++; this->Player2Stat.losses++; break;
            case 2: this->Player1Stat.losses++; this->Player2Stat.victories++; break;
        }
    }
}

short int RPSLS::getLastChoice(short int x)
{
    if(Player1Choices.size() > 0 && Player2Choices.size() > 0)
    {
        switch (x)
        {
            case 1: return Player1Choices.back(); break;
            case 2: return Player2Choices.back(); break;
            default: return -1;
        }
    }
    else
        return 0;
}

short int RPSLS::getLastWinner()
{
    return this->lastWinner;
}

short int RPSLS::getMatchWinner()
{
    if(this->Player1Stat.victories > this->Player2Stat.victories)
        return 1;
    else if(this->Player1Stat.victories < this->Player2Stat.victories)
        return 2;
    else
        return 0;
}

PlayerStat RPSLS::getPlayerStat(short int x)
{
    switch(x)
    {
        case 1: return this->Player1Stat; break;
        case 2: return this->Player2Stat; break;
        default: return PlayerStat();
    }
}

std::ostream& operator<<(std::ostream &o, const RPSLS &game)
{
    o << game.Player1Choices.size() << std::endl;

    auto it = game.Player1Choices.begin();
    while(it != game.Player1Choices.end())
    {
        o << *it << " ";

        it++;
    }
    o << std::endl;

    auto it2 = game.Player2Choices.begin();
    while(it2 != game.Player2Choices.end())
    {
        o << *it2 << " ";

        it2++;
    }
    o << std::endl;

    return o;
}

unsigned short int RPSLS::getWinner(short int a, short int b)
{
    if(RPSLS::isValidChoice(a) && RPSLS::isValidChoice(b))
    {
        if (a == b || a < 1 || a > 5 || b < 1 || b > 5) return 0;
        if (a == ROCK && (b == SCISSOR || b == LIZARD)) return 1;
        if (a == PAPER && (b == ROCK || b == SPOCK)) return 1;
        if (a == SCISSOR && (b == PAPER || b == LIZARD)) return 1;
        if (a == LIZARD && (b == PAPER || b == SPOCK)) return 1;
        if (a == SPOCK && (b == ROCK || b == SCISSOR)) return 1;
        return 2;
    }
    else
        return 0;

}

bool RPSLS::isValidChoice(short int a)
{
    return a >= 1 && a <= 5;
}