/*
 * Client.cpp
 *
 *      Author: Liron
 */

#include "Client.h"
int Client::allocId = 0;


Client::Client(int priority, BrokerIfc& broker,
		std::ostream& messagesSink):	id(allocId),
		priority(priority), broker(broker), messagesSink(messagesSink),
		topics(SortedSet<Topic, CompareTopics>()){
	if(priority < 0)
		throw IllegalPriority();
	allocId++;
}


int Client::getPriority() const{
	return this->priority;
}


int Client::getId() const{
	return this->id;
}


void Client::receiveMaintenanceMessage(const std::string& s) const{
	messagesSink << "Client #"<< this->id <<
			" received maintenance message: "<< s << std::endl;
}



