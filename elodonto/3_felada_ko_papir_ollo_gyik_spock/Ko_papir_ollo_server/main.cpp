#include <winsock2.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "../Ko_papir_ollo_client/RPSLS.hpp"
#include "../Ko_papir_ollo_client/NetworkMagic.hpp"
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

        RPSLS currentGame(Player1Name, Player2Name);

        ServerSocket.sendTo(Player1Address, Player1Port, "0");
        ServerSocket.sendTo(Player2Address, Player2Port, "0");

        std::string Player1Choice = "", Player2Choice = "";
        long int i = 0;
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

            currentGame.addChoices(Player1Choice[0] - '0', Player2Choice[0] - '0');
            std::cout << i << ". kor lement. ";

            switch(currentGame.getLastWinner())
            {
                case 0: std::cout << "Dontetlen!" << std::endl; break;
                case 1: std::cout << Player1Name << ". a nyertes!" << std::endl; break;
                case 2: std::cout << Player2Name << ". a nyertes!" << std::endl; break;
                default: std::cerr << "Baj van." << std::endl;
            }

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
            log << currentGame;
            log.flush();

            switch(currentGame.getMatchWinner())
            {
                case 0: std::cout << "Dontetlen lett a jatek!" << std::endl; break;
                case 1: std::cout << Player1Name << " nyert!" << std::endl; break;
                case 2: std::cout << Player2Name << " nyert!" << std::endl; break;
            }

            std::cout << "Uj jatek!" << std::endl;
        }

    }
    log.close();
}