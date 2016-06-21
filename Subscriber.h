#ifndef MTM4_SUBSCRIBER_H
#define MTM4_SUBSCRIBER_H


#include "Client.h"

class Subscriber : public Client {

public:

	Subscriber(int priority, BrokerIfc& broker,
			std::ostream& messagesSink = std::cout);


	void subscribeToTopic(Topic topic);


	void unsubscribeToTopic(Topic topic);


	void unsubscribeAll();


	virtual void receiveMessage(const std::string& message, const Topic& topic,
			const Client& client)const;

};


#endif //MTM4_SUBSCRIBER_H
