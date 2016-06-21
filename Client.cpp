/*
 * Client.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Client.h"


Client::Client(int priority, BrokerIfc& broker,
		std::ostream& messagesSink = std::cout):
		broker(broker), messagesSink(messagesSink){
	if(priority < 0)
		throw IllegalPriority();
	this->priority = priority;
}


int Client::getPriority() const{
	return this->priority;
}


int Client::getId() const{
	return this->id;
}


std::string Client::receiveMaintenanceMessage(const std::string& s) const{
	std::string result = "Client #"+this->id+" received maintenance message: "
			+s;
	messagesSink << result << std::endl;	// ??
	return result;
}



