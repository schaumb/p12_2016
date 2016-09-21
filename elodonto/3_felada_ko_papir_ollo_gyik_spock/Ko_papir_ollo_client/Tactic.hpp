//
// Created by Komonyi on 2016.09.21..
//

#ifndef KO_PAPIR_OLLO_CLIENT_TACTIC_HPP
#define KO_PAPIR_OLLO_CLIENT_TACTIC_HPP


class Tactic {
protected:
    short int myChoice;
public:
    virtual int getChanceToWin()=0;
    virtual short int getChoice();

    virtual void addChoices(short int a, short int b);
    virtual void markAsUsed();

    virtual void calculateNextChoice()=0;

};


#endif //KO_PAPIR_OLLO_CLIENT_TACTIC_HPP
