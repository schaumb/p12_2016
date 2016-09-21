#ifndef NETWORKMAGIC_H
#define NETWORKMAGIC_H

#include <winsock2.h>
#include <stdio.h>
#include <string>

class UdpSocket
{
private:
    WSADATA wsaData;
    SOCKET MySocket;
    SOCKADDR_IN Address;

public:
    UdpSocket(u_short port);
    ~UdpSocket();

    void sendTo(unsigned long ip, u_short port, std::string message);
    std::string receiveFrom(unsigned long &ip, u_short &port);
    std::string receiveFromTimeout(unsigned long &ip, u_short &port, int sec);
};

#endif /* NETWORKMAGIC_H */