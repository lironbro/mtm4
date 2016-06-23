#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H


#include "Client.h"

class Publisher : public Client {

public:

	Publisher(int priority, BrokerIfc& broker,
			std::ostream& messagesSink = std::cout);


	void publishTopic(const Topic& topic);


	void unpublishTopic(const Topic& topic);


	void unpublishAll();


	virtual void sendMessage(const std::string& message, const Topic& topic)const;


};


#endif //MTM4_PUBLISHER_H
