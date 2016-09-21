#include "RPSLS.hpp"


unsigned int RPSLS::getWinner(short int a, short int b)
{
    if(isValidChoice(a) && isValidChoice(b))
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