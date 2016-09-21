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

    unsigned long ServerAddress, SenderAddress = 0;
    u_short ServerPort, SenderPort = 0, ClientPort = 46150;
    std::string str, name = "Sanyi", tacticName = "";

    std::ifstream config("config.txt");
    config >> ClientPort;

    config >> str;
    ServerAddress = inet_addr(str.c_str());
    config >> ServerPort;

    config.close();

    bool NO_LOG = false;
    int i = 1;
    while(i < argc)
    {
        if(strcmp(argv[i], "-no-log") == 0)
        {
            NO_LOG = true;
            i++;
        }
        else if(strcmp(argv[i], "-name") == 0)
        {
            name = argv[i + 1];
            i += 2;
        }
        else if(strcmp(argv[i], "-default-port") == 0)
        {
            ClientPort = 46150;
            i++;
        }
        else if(strcmp(argv[i], "-tactic") == 0)
        {
            tacticName = argv[i + 1];
            i += 2;
        }
        else
            i++;
    }


    UdpSocket ClientSocket(ClientPort);

    ClientSocket.sendTo(ServerAddress, ServerPort, name); //TODO végső kódba ez nem kell

    str = ClientSocket.receiveFrom(SenderAddress, SenderPort);
    if(SenderAddress == ServerAddress && SenderPort == ServerPort && str == "0")
    {
        str = "";
        AI Sanyi(tacticName);

        while(str.size() < 2)
        {
            Sanyi.calculateNextChoice();

            ClientSocket.sendTo(ServerAddress, ServerPort, patch::to_string(Sanyi.getChoice()));
            std::cout << "Sajat valasztas: " << Sanyi.getChoice();

            str = ClientSocket.receiveFromTimeout(SenderAddress, SenderPort, 300);
            std::cout << " Ellenfel vlasztasa: " << str << std::endl;

            Sanyi.setEnemyChoice(str[0] - '0');
        }

        if(!NO_LOG)
        {
            std::ofstream log("log.txt", std::ofstream::app);
            log << Sanyi;
            log.close();
        }

    }
    else
        std::cerr << "Valami baj van a szerverrel" << std::endl;

    ClientSocket.~UdpSocket();
    return 0;
}