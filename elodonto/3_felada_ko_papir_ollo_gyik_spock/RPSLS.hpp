#ifndef RPSLS_H
#define RPSLS_H

class RPSLS
{
public:
    static const unsigned short int ROCK = 1;
    static const unsigned short int PAPER = 2;
    static const unsigned short int SCISSOR = 3;
    static const unsigned short int LIZARD = 4;
    static const unsigned short int SPOCK = 5;

    static unsigned int getWinner(short int a, short int b);
    static bool isValidChoice(short int a);
};

#endif /* RPSLS_H */