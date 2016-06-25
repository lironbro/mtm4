/*
 * Subscriber.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Subscriber.h"


Subscriber::Subscriber(int priority, BrokerIfc& broker,
		std::ostream& messagesSink):
		Client(priority, broker, messagesSink){

}


void Subscriber::subscribeToTopic(Topic topic){
	this->topics.insert(topic);
	broker.subscribeToTopic(*this, topic);
}


void Subscriber::unsubscribeToTopic(Topic topic){
	if(topics.find(topic) == topics.end()){
		throw Client::NonSubscribedTopic();
	}
	this->topics.remove(topic);
	broker.unsubscribeToTopic(*this, topic);
}


void Subscriber::unsubscribeAll(){
	while(topics.begin() != topics.end()){		// empties the set
		unsubscribeToTopic(*(topics.begin()));
	}
}


void Subscriber::receiveMessage(const std::string& message, const Topic& topic,
		const Client& client)const{
	if(this->topics.contains(topic) == false)
		throw Client::NonSubscribedTopic();
	int client_id =client.getId();
	int i_id = this->id;
	messagesSink << "Topic: " << topic << ". Sender: #" <<client_id <<
			". Receiver: #"	<< i_id << ". Message: " << message << std::endl;
}
