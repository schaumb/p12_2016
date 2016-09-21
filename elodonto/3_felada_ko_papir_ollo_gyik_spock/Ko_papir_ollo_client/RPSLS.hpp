#ifndef RPSLS_H
#define RPSLS_H

#include <string>
#include <list>
#include <iostream>

struct PlayerStat
{
    unsigned long int victories = 0, draws = 0, losses = 0;
};

class RPSLS
{
private:
    std::string Player1Name = "", Player2Name = "";
    std::list<short int> Player1Choices, Player2Choices;
    PlayerStat Player1Stat, Player2Stat;
    short int lastWinner = 0;

public:
    static const unsigned short int ROCK = 1;
    static const unsigned short int PAPER = 2;
    static const unsigned short int SCISSOR = 3;
    static const unsigned short int LIZARD = 4;
    static const unsigned short int SPOCK = 5;

    static unsigned short int getWinner(short int a, short int b);
    static bool isValidChoice(short int a);

    RPSLS();
    RPSLS(std::string a, std::string b);

    void addChoices(short int a, short int b);
    short int getLastChoice(short int x);
    short int getLastWinner();

    short int getMatchWinner();

    PlayerStat getPlayerStat(short int x);

    friend std::ostream& operator<<(std::ostream &o, const RPSLS &game);
};

#endif /* RPSLS_H */