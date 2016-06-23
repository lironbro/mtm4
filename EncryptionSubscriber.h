//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONSUBSCRIBER_H
#define MTM4_ENCRYPTIONSUBSCRIBER_H


#include "Subscriber.h"

class EncryptionSubscriber : public Subscriber {

	typedef Subscriber super;

public:

	EncryptionSubscriber(int priority, BrokerIfc& broker, char key,
			std::ostream& messagesSink = std::cout);

	void receiveMessage(const std::string& message, const Topic& topic,
			const Client& client)const override;


private:
	char key;


};


#endif //MTM4_ENCRYPTIONSUBSCRIBER_H
