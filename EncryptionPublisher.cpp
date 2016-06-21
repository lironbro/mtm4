/*
 * EncryptionPublisher.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "EncryptionPublisher.h"


EncryptionPublisher::EncryptionPublisher(int priority, BrokerIfc& broker, char key,
		std::ostream& messagesSink = std::cout) :
		Publisher(priority, broker, messagesSink), key(key){
}


void EncryptionPublisher::sendMessage(std::string message, Topic topic)const{
	std::string encrypted = message^key;
	super::sendMessage(encrypted, topic);
}

