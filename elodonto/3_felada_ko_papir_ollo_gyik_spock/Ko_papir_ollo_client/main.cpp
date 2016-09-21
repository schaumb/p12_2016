#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../NetworkMagic.hpp"
#include <random>
#include <chrono>

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
    std::string seged, name;

    std::ifstream config("config.txt");
    config >> name;
    config >> ClientPort;

    config >> seged;
    ServerAddress = inet_addr(seged.c_str());
    config >> ServerPort;

    config.close();

    UdpSocket ClientSocket(ClientPort);

    ClientSocket.sendTo(ServerAddress, ServerPort, name);

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();

    seged = ClientSocket.receiveFrom(SenderAddress, SenderPort);
    if(SenderAddress == ServerAddress && SenderPort == ServerPort && seged == "0")
    {
        seged = "";

        std::default_random_engine generator(seed1);
        std::uniform_int_distribution<int> distribution(1,5);
        int choice;

        while(seged.size() < 2)
        {
            choice = distribution(generator);
            ClientSocket.sendTo(ServerAddress, ServerPort, patch::to_string(choice));
            std::cout << "Sajat valasztas: " << choice;

            seged = ClientSocket.receiveFromTimeout(SenderAddress, SenderPort, 300);
            std::cout << " Ellenfel vlasztasa: " << seged << std::endl;
        }

    }
    else
        std::cerr << "Valami baj van a szerverrel" << std::endl;

    ClientSocket.~UdpSocket();
    return 0;
}