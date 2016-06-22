/*
 * Subscriber.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Subscriber.h"


Subscriber::Subscriber(int priority, BrokerIfc& broker,
		std::ostream& messagesSink):
		Client::Client(priority, broker, messagesSink){

}


void Subscriber::subscribeToTopic(Topic topic){
	this->topics.insert(topic);
	broker.subscribeToTopic(*this, topic);
}


void Subscriber::unsubscribeToTopic(Topic topic){
	this->topics.remove(topic);
	broker.unsubscribeToTopic(*this, topic);
}


void Subscriber::unsubscribeAll(){
	while(topics.begin() != topics.end()){		// empties the set
		unsubscribeToTopic(*(topics.begin()));
		topics.remove(*(topics.begin()));
	}
}


void Subscriber::receiveMessage(const std::string& message, const Topic& topic,
		const Client& client)const{
	if(this->topics.find(topic) == this->topics.end())
		throw Client::NonSubscribedTopic();
	messagesSink<< "Topic " << topic <<". Sender: #"<< client.getId()
					<<". Receiver: #" << (this->id) <<". Message: "<< message;
	messagesSink<< std::endl;
}
