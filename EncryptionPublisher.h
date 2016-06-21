//
// Created by izikgo on 5/23/2016.
//

#ifndef MTM4_ENCRYPTIONPUBLISHER_H
#define MTM4_ENCRYPTIONPUBLISHER_H


#include "Publisher.h"

class EncryptionPublisher : public Publisher {

	typedef Publisher super;

public:
	EncryptionPublisher(int priority, BrokerIfc& broker, char key,
			std::ostream& messagesSink = std::cout);


	void sendMessage(std::string message, Topic topic)const override;

private:
	char key;
};


#endif //MTM4_ENCRYPTIONPUBLISHER_H
