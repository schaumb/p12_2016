#include "NetworkMagic.hpp"
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <iostream>

UdpSocket::UdpSocket(u_short port)
{
    // Initialize Winsock version 2.2
    if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        printf("Server: WSAStartup failed with error %i\n", WSAGetLastError());
    }

    // Create a new socket to receive datagrams on.
    MySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (MySocket == INVALID_SOCKET)
    {
        printf("Server: Error at socket(): %i\n", WSAGetLastError());
        // Clean up
        WSACleanup();
    }

    Address.sin_family = AF_INET;
    Address.sin_port = htons(port);
    Address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Associate the address information with the socket using bind.
    if (bind(MySocket, (SOCKADDR *)&Address, sizeof(Address)) == SOCKET_ERROR)
    {
        printf("Server: bind() failed! Error: %i.\n", WSAGetLastError());
        // Close the socket
        closesocket(MySocket);
        // Do the clean up
        WSACleanup();
    }
}

UdpSocket::~UdpSocket()
{
    closesocket(MySocket);
    WSACleanup();
}

void UdpSocket::sendTo(unsigned long ip, u_short port, std::string message)
{
    SOCKADDR_IN ReceiverAddress;
    ReceiverAddress.sin_family = AF_INET;
    ReceiverAddress.sin_addr.s_addr = ip;
    ReceiverAddress.sin_port = htons(port);

    char buff[256];
    strcpy(buff, message.c_str());
    int buffSize = message.size();

    sendto(MySocket, buff, buffSize, 0, (SOCKADDR *)&ReceiverAddress, sizeof(ReceiverAddress));
}

std::string UdpSocket::receiveFrom(unsigned long &ip, u_short &port)
{
    char buff[256];
    SOCKADDR_IN SenderAddress;
    int buffSize = 256, SenderAddressSize = sizeof(SenderAddress);

    int bytesReceived = recvfrom(MySocket, buff, buffSize, 0, (SOCKADDR *)&SenderAddress, &SenderAddressSize);

    ip = SenderAddress.sin_addr.s_addr;
    port = ntohs(SenderAddress.sin_port);

    if(bytesReceived > 0)
        return std::string(buff, bytesReceived);
    else if(bytesReceived == 0)
        return std::string("error");
    else
    {
        printf("Error: %i.\n", WSAGetLastError());
        return std::string("error");
    }
}

std::string UdpSocket::receiveFromTimeout(unsigned long &ip, u_short &port, int sec)
{
    // Setup timeval variable
    timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = 0;

    // Setup fd_set structure
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(MySocket, &fds);

    // Return value:
    // -1: error occurred
    // 0: timed out
    // > 0: data ready to be read
    int x = select(MySocket + 1, &fds, 0, 0, &timeout);
    if(x > 0)
        return this->receiveFrom(ip, port);
    else if(x == 0)
        return std::string("timeout");
    else
        return std::string("error");
}