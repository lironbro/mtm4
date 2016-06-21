#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H


#include <exception>
#include <string>
#include "BrokerIfc.h"

class Client {
    static int nextId;

    const int id;
    const int priority;
    const std::ostream& messagesSink;

protected:
    BrokerIfc& broker;

public:
    class ClientException : public std::exception {};
    class IllegalPriority : public ClientException {};
    class NonSubscribedTopic : public ClientException {};
    class NonPublishedTopic : public ClientException {};

    Client(int priority, BrokerIfc& broker,
    		std::ostream& messagesSink = std::cout);	// ??

    virtual ~Client();

    int getPriority() const;

    int getId() const;

    std::string receiveMaintenanceMessage(const std::string& s) const;
};


#endif //MTM4_CLIENT_H
