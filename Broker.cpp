/*
 * Broker.cpp
 *
 *  Created on: 21 αιεπι 2016
 *      Author: Liron
 */

#include "Broker.h"



void Broker::subscribeToTopic(const Subscriber& sub, const Topic& t){
	avaliableTopics[t].insert(sub);
}


void Broker::unsubscribeToTopic(const Subscriber& sub, const Topic& t){
	avaliableTopics[t].remove(sub);
}


void Broker::publishTopic(const Publisher& pub, const Topic& t){
	avaliableTopics[t].insert(pub);
}


void Broker::unpublishTopic(const Publisher& pub, const Topic& t){
	avaliableTopics[t].remove(pub);
}


void Broker::publishMessage(const Topic& t, const std::string& message,
			const Client& sender) const{
	SortedSet<const Client&, CompareClients> set = this->avaliableTopics[t];
	// set should be a sorted set of clients subscribed to t
	for(auto current = set.begin(); current != set.end(); current++){
		if(const Subscriber* ptr = dynamic_cast<const Subscriber*>(&(*current))){
			ptr->receiveMessage(message, t, sender);
		}
	}
}


void Broker::sendMaintenanceMessageAny(std::list<Topic> topics,
		std::string message){
	SortedSet<const Client&, CompareClients> any =
			SortedSet<const Client&, CompareClients>();
	for(auto current = topics.begin(); current != topics.end(); current++){
		any = any | avaliableTopics[*current];
	}
	for(auto current = any.begin(); current != any.end();
			current++){
		(*current).receiveMaintenanceMessage(message);
	}
}


void Broker::sendMaintenanceMessageAll(std::list<Topic> topics,
		std::string message){
	SortedSet<const Client&, CompareClients> all =
			SortedSet<const Client&, CompareClients>();
	for(auto current = topics.begin(); current != topics.end(); current++){
		all = all & avaliableTopics[*current];
	}
	for(auto current = all.begin(); current != all.end();
			current++){
		(*current).receiveMaintenanceMessage(message);
	}
}


