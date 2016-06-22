/*
 * EncryptionPublisher.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "EncryptionPublisher.h"


EncryptionPublisher::EncryptionPublisher(int priority, BrokerIfc& broker, char key,
		std::ostream& messagesSink) :
		Publisher(priority, broker, messagesSink), key(key){
}


void EncryptionPublisher::sendMessage(std::string message, const Topic& topic)const{
	std::string encrypted = message;
	for(unsigned int i = 0; i < encrypted.size(); i++){
		encrypted[i]^=key;
	}
	super::sendMessage(encrypted, topic);
}

