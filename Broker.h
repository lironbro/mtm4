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
	std::map<Topic, SortedSet<const Client&, CompareClients>> avaliableTopics;

	/*
	 * IMPORTANT:<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
	 * i removed turned the objects to be non const and not references,
	 * which made the strange errors i had earlier disappear.
	 * this is most likely incorrect, since it is reasonable to add const clients
	 * to the broker, but it just seems to fail even though the functions
	 * called within these ones do accept const.
	 */

	void subscribeToTopic(const Subscriber& sub, const Topic& t) override;

	void unsubscribeToTopic(const Subscriber& sub, const Topic& t) override;

	void publishTopic(const Publisher& pub, const Topic& t) override;
	
	void unpublishTopic(const Publisher& pub, const Topic& t) override;

	void publishMessage(const Topic& t, const std::string& message, const Client& sender)const override;



public:

	Broker()=default;
	

	virtual void sendMaintenanceMessageAny(std::list<Topic> topics,
			std::string message);


	virtual void sendMaintenanceMessageAll(std::list<Topic> topics,
			std::string message);
};


#endif //MTM4_BROKER_H
