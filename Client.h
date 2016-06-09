#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H


#include <exception>
#include <string>
#include "BrokerIfc.h"

class Client {
    static int nextId;

    const int id;
    const int priority;

protected:
    BrokerIfc& broker;

public:
    class ClientException : public std::exception {};
    class IllegalPriority : public ClientException {};
    class NonSubscribedTopic : public ClientException {};
    class NonPublishedTopic : public ClientException {};

    Client(int priority, BrokerIfc& broker);

    Client(const Client& c) = default;

    Client& operator=(const Client&) = default;

    virtual ~Client();

    int getPriority() const;

    int getId() const;

    std::string receiveMaintenanceMessage(const std::string& s) const;
};


#endif //MTM4_CLIENT_H
