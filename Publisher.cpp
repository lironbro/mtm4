/*
 * Publisher.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Publisher.h"


/*
 * this seems to have forgotten everything about Client.h, even though this file
 * includes Publisher.h, which includes Client.h
 */


Publisher::Publisher(int priority, BrokerIfc& broker,
		std::ostream& messagesSink):
		Client(priority, broker, messagesSink){
}


void Publisher::publishTopic(const Topic& topic){
	topics.insert(topic);
	this->broker.publishTopic(*this, topic);
}


void Publisher::unpublishTopic(const Topic& topic){
	if(topics.find(topic) == topics.end()){
		throw NonPublishedTopic();
	}
	this->topics.remove(topic);
	broker.unpublishTopic(*this, topic);
}


void Publisher::unpublishAll(){
	auto ite = this->topics.begin();
	while(ite != topics.end()){		// empties the set
		unpublishTopic(*(ite));
		//topics.remove(*(topics.begin()));
	}
}


void Publisher::sendMessage(const std::string& message, const Topic& topic)const{
	if(topics.find(topic) == topics.end())
		throw NonPublishedTopic();
	this->broker.publishMessage(topic, message, *this);
}

void Publisher::receiveMessage(const std::string& message, const Topic& topic,
			const Client& client)const{

}

