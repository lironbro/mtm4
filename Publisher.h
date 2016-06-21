#ifndef MTM4_PUBLISHER_H
#define MTM4_PUBLISHER_H


#include "Client.h"

class Publisher : public Client {

public:

	Publisher(int priority, BrokerIfc& broker,
			std::ostream& messagesSink = std::cout);


	void publishTopic(Topic topic);


	void unpublishTopic(Topic topic);


	void unpublishAll();


	void sendMessage(std::string message, Topic topic)const;


};


#endif //MTM4_PUBLISHER_H
