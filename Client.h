#ifndef MTM4_CLIENT_H
#define MTM4_CLIENT_H


#include <exception>
#include <string>
#include "BrokerIfc.h"
#include <iostream>

class Client {

private:
	static int allocId;


public:
	class ClientException : public std::exception {};
	class IllegalPriority : public ClientException {};
	class NonSubscribedTopic : public ClientException {};
	class NonPublishedTopic : public ClientException {};

	Client(int priority, BrokerIfc& broker,
			std::ostream& messagesSink);	// ??

	virtual ~Client();

	int getPriority() const;

	int getId() const;

	void receiveMaintenanceMessage(const std::string& s) const;



protected:
	class CompareTopics{
		public:
			bool operator()(Topic topic1, Topic topic2){
			return topic1.compare(topic2);
		}
	};


	BrokerIfc& broker;

	SortedSet<Topic, CompareTopics> topics;
	int id;
	int priority;
	const std::ostream& messagesSink;

};


#endif //MTM4_CLIENT_H
