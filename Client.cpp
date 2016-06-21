/*
 * Client.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Client.h"


Client::Client(int priority, BrokerIfc& broker,
		std::ostream& messagesSink = std::cout): id(allocId),
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
	messagesSink << "Client #"<< this->id <<" received maintenance message: "
			<< s << std::endl;	// ??
}



