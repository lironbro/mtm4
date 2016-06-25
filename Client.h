#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H


#include <exception>
#include <string>
#include "BrokerIfc.h"
#include <iostream>

class Client{

private:
	static int allocId;


public:
	class ClientException : public std::exception {};
	class IllegalPriority : public ClientException {};
	class NonSubscribedTopic : public ClientException {};
	class NonPublishedTopic : public ClientException {};

	Client(int priority, BrokerIfc& broker,
			std::ostream& messagesSink);

	int getPriority() const;

	int getId() const;

	void receiveMaintenanceMessage(const std::string& s) const;
	
	virtual void receiveMessage(const std::string& message, const Topic& topic,
			const Client& client)const = 0;



protected:
	class CompareTopics{
		public:
			bool operator()(Topic topic1, Topic topic2){
			return topic1.compare(topic2);
		}
	};


	int id;
	int priority;
	BrokerIfc& broker;
	std::ostream& messagesSink;
	SortedSet<Topic, CompareTopics> topics;

};


#endif //MTM4_CLIENT_H
