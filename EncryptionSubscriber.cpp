/*
 * EncryptionSubscriber.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "EncryptionSubscriber.h"


EncryptionSubscriber::EncryptionSubscriber(int priority, BrokerIfc& broker,
		char key, std::ostream& messagesSink) :
		Subscriber(priority, broker, messagesSink), key(key){

}


void EncryptionSubscriber::receiveMessage(const std::string& message,
		const Topic& topic, const Client& client)const{
	std::string encrypted = message;
	for(unsigned int i = 0; i < encrypted.size(); i++){
		encrypted[i]^=key;
	}
	super::receiveMessage(encrypted, topic, client);
}


