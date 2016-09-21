#include <winsock2.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "../RPSLS.hpp"
#include "../NetworkMagic.hpp"
#include <list>


int main(int argc, char **argv)
{
    long int rounds = 100;
    u_short ServerPort = 16748;

    std::ifstream config("config.txt");
    config >> rounds;
    config >> ServerPort;
    config.close();

    std::ofstream log("log.txt", std::ofstream::app);
    UdpSocket ServerSocket(ServerPort);
    bool keepRunning = true;

    while(keepRunning)
    {
        unsigned long Player1Address, Player2Address, SenderAddress;
        u_short Player1Port, Player2Port, SenderPort;
        std::list<short int> Player1Choices, Player2Choices;
        std::string Player1Name = "Player1", Player2Name = "Player2";
        std::string lastMessage= "";

        Player1Name = ServerSocket.receiveFrom(Player1Address, Player1Port);
        std::cout << Player1Name << " becsatlakozott!" << std::endl;
        Player2Name = ServerSocket.receiveFromTimeout(Player2Address, Player2Port, 300);
        std::cout << Player2Name << " becsatlakozott!" << std::endl;

        if(Player1Name == "csukojd_be" || Player2Name == "csukodj_be")
        {
            ServerSocket.sendTo(Player1Address, Player1Port, "Server is shutting down.");
            ServerSocket.sendTo(Player2Address, Player2Port, "Server is shutting down.");
            keepRunning = false;
            exit;
        }

        if(Player1Name == "timeout" || Player2Name == "timeout" || Player1Name == "error" || Player2Name == "error")
        {
            ServerSocket.sendTo(Player1Address, Player1Port, "There was an error.");
            ServerSocket.sendTo(Player2Address, Player2Port, "There was an error.");
            std::cout << "Uj jatek." << std::endl;

            continue;
        }


        ServerSocket.sendTo(Player1Address, Player1Port, "0");
        ServerSocket.sendTo(Player2Address, Player2Port, "0");

        std::string Player1Choice = "", Player2Choice = "";
        long int i = 0, Player1Wins = 0, Player1Draws = 0, Player1Losses = 0, Player2Wins = 0, Player2Draws = 0, Player2Losses = 0;
        while (i < rounds && lastMessage != "timeout" && lastMessage != "error")
        {
            Player1Choice = "";
            Player2Choice = "";
            while ((Player1Choice == "" || Player2Choice == "") && lastMessage != "timeout" && lastMessage != "error")
            {
                lastMessage = ServerSocket.receiveFromTimeout(SenderAddress, SenderPort, 120);

                if (SenderAddress == Player1Address && SenderPort == Player1Port)
                {
                    Player1Choice = lastMessage;
                    std::cout << "Player1: " << Player1Choice << std::endl;
                }
                else if (SenderAddress == Player2Address && SenderPort == Player2Port)
                {
                    Player2Choice = lastMessage;
                    std::cout << "Player2: " << Player2Choice << std::endl;
                }
                else
                    std::cerr << "Valami köcsög zaklat" << std::endl;
            }

            if(lastMessage == "timeout" || lastMessage == "error" || Player1Choice == "" || Player2Choice == ""
               || !RPSLS::isValidChoice(Player1Choice[0] - '0') || !RPSLS::isValidChoice(Player2Choice[0] - '0'))
            {
                ServerSocket.sendTo(Player1Address, Player1Port, "There was an error.");
                ServerSocket.sendTo(Player2Address, Player2Port, "There was an error.");
                lastMessage = "error";
                std::cout << "Valaki bamba." << std::endl;
                continue;
            }

            int winner = RPSLS::getWinner(Player1Choice[0] - '0', Player2Choice[0] - '0');
            std::cout << i << ". kor lement. ";

            switch(winner)
            {
                case 0: std::cout << "Dontetlen!" << std::endl; Player1Draws++; Player2Draws++; break;
                case 1: std::cout << Player1Name << ". a nyertes!" << std::endl; Player1Wins++; Player2Losses++; break;
                case 2: std::cout << Player2Name << ". a nyertes!" << std::endl; Player2Wins++; Player1Losses++; break;
                default: std::cerr << "Baj van." << std::endl;
            }

            Player1Choices.push_back(Player1Choice[0] - '0');
            Player2Choices.push_back(Player2Choice[0] - '0');

            if (i == rounds - 1) {
                Player1Choice += "0";
                Player2Choice += "0";
            }
            ServerSocket.sendTo(Player1Address, Player1Port, Player2Choice);
            ServerSocket.sendTo(Player2Address, Player2Port, Player1Choice);


            i++;
        }

        if(i == rounds)
        {
            log << Player1Name << std::endl;
            log << Player1Address << std::endl;
            log << Player1Port << std::endl;
            log << Player1Wins << std::endl;
            log << Player1Draws << std::endl;
            log << Player1Losses << std::endl;
            log << Player1Choices.size() << std::endl;
            auto it = Player1Choices.begin();
            while(it != Player1Choices.end())
            {
                log << *it << " ";

                it++;
            }
            log << std::endl;

            log << Player2Name << std::endl;
            log << Player2Address << std::endl;
            log << Player2Port << std::endl;
            log << Player2Wins << std::endl;
            log << Player2Draws << std::endl;
            log << Player2Losses << std::endl;
            log << Player2Choices.size() << std::endl;
            auto it2 = Player2Choices.begin();
            while(it2 != Player2Choices.end())
            {
                log << *it2 << " ";

                it2++;
            }
            log << std::endl;

            log << std::endl;
            log.flush();

            if(Player1Wins > Player2Wins)
                std::cout << Player1Name << " nyert!" << std::endl;
            else if(Player1Wins < Player2Wins)
                std::cout << Player2Name << " nyert!" << std::endl;
            else
                std::cout << "Dontetlen lett a jatek!" << std::endl;

            std::cout << "Uj jatek!" << std::endl;
        }

    }
    log.close();
}