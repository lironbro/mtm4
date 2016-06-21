#ifndef MTM4_BROKER_H
#define MTM4_BROKER_H

#include <map>
#include <list>
#include "SortedSet.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "BrokerIfc.h"

class Broker : public BrokerIfc {
	class CompareClients {
	public:
		bool operator()(const Client& c1, const Client& c2) const{
			if(c1.getPriority() < c2.getPriority())
				return true;
			if(c1.getPriority() > c2.getPriority())
				return false;
			return c1.getId() < c2.getId();
		}


	};


private:
	// topics is the map of topics held by the broker
	// the keys are topics, the elements are the sets of users subscribed to
	// each topic
	std::map<Topic, SortedSet<Client&, CompareClients>> avaliableTopics;


	virtual void subscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void unsubscribeToTopic(const Subscriber& sub, const Topic& t);

	virtual void publishTopic(const Publisher& pub, const Topic& t);

	virtual void unpublishTopic(const Publisher& pub, const Topic& t);

	virtual void publishMessage(const Topic& t, const std::string& message, const Client& sender) const;



public:


	virtual void sendMaintenanceMessageAny(std::list<Topic> topics,
			std::string message);


	virtual void sendMaintenanceMessageAll(std::list<Topic> topics,
			std::string message);
};


#endif //MTM4_BROKER_H
