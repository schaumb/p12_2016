#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "NetworkMagic.hpp"
#include "AI.hpp"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


int main(int argc, char **argv)
{
    u_short            ClientPort = 46150;

    unsigned long ServerAddress, SenderAddress = 0;
    u_short ServerPort, SenderPort = 0;
    std::string str, name;

    std::ifstream config("config.txt");
    config >> name; //TODO végső kódba ez nem kell
    config >> ClientPort;

    config >> str;
    ServerAddress = inet_addr(str.c_str());
    config >> ServerPort;

    config.close();

    UdpSocket ClientSocket(ClientPort);

    ClientSocket.sendTo(ServerAddress, ServerPort, name); //TODO végső kódba ez nem kell

    str = ClientSocket.receiveFrom(SenderAddress, SenderPort);
    if(SenderAddress == ServerAddress && SenderPort == ServerPort && str == "0")
    {
        str = "";
        AI Sanyi;
        std::ofstream log("log.txt", std::ofstream::app);

        while(str.size() < 2)
        {
            Sanyi.calculateNextChoice();

            ClientSocket.sendTo(ServerAddress, ServerPort, patch::to_string(Sanyi.getChoice()));
            std::cout << "Sajat valasztas: " << Sanyi.getChoice();

            str = ClientSocket.receiveFromTimeout(SenderAddress, SenderPort, 300);
            std::cout << " Ellenfel vlasztasa: " << str << std::endl;

            Sanyi.setEnemyChoice(str[0] - '0');
        }

        log << Sanyi;
        log.close();

    }
    else
        std::cerr << "Valami baj van a szerverrel" << std::endl;

    ClientSocket.~UdpSocket();
    return 0;
}