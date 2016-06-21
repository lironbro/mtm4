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
		Client::Client(priority, broker, messagesSink){
}


void Publisher::publishTopic(Topic topic){
	Client::topics.insert(topic);
	this->broker.publishTopic(*this, topic);
}


void Publisher::unpublishTopic(Topic topic){
	this->topics.remove(topic);
	broker.unpublishTopic(*this, topic);
}


void Publisher::unpublishAll(){
	while(this->topics.begin() != topics.end()){		// empties the set
		unpublishTopic(*(topics.begin()));
		topics.remove(*(topics.begin()));
	}
}


void Publisher::sendMessage(std::string message, Topic topic)const{
	if(topics.find(topic) == topics.end())
		throw NonPublishedTopic();
	this->broker.publishMessage(topic, message, *this);
}

