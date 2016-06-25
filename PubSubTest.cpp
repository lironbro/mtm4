/*
 * LironsTest.cpp
 *
 *  Created on: 24 αιεπι 2016
 *      Author: Liron
 */


#include <cstdlib>
#include "Broker.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"
#include "MtmTst.h"


bool brokerSendMaintenanceMessageAny(Broker& broker){
	std::list<Topic> list;
	list.insert(list.end(), "Game of thrones");
	list.insert(list.end(), "Gaming");
	list.insert(list.end(), "Boring topic");
	broker.sendMaintenanceMessageAny(list,
			"Welcome everyone! You're all nerds!");

	return true;
}


bool brokerSendMaintenanceMessageAll(Broker& broker){
	std::list<Topic> list;
	list.insert(list.end(), "Boring topic");
	list.insert(list.end(), "Very boring topic");
	broker.sendMaintenanceMessageAll(list,
			"Wow, you're into some really boring things!");

	return true;
}



bool clientGetId(Subscriber& sub1, Publisher& pub1){
	ASSERT_EQUALS(0, sub1.getId());
	ASSERT_EQUALS(3, pub1.getId());

	return true;
}


bool clientGetPriority(Subscriber& sub1, Publisher& pub1){
	ASSERT_EQUALS(1, sub1.getPriority());
	ASSERT_EQUALS(5, pub1.getPriority());

	return true;
}


bool clientReceiveMaintenanceMessage(Subscriber& sub1, Publisher& pub1){
	sub1.receiveMaintenanceMessage("Sub1 got this message");
	pub1.receiveMaintenanceMessage("Pub1 got this message");

	return true;
}



bool subSubscribeToTopic(Subscriber& sub1, Subscriber& sub2, Subscriber& sub3){
	sub1.subscribeToTopic("Game of thrones");
	sub1.subscribeToTopic("Rick and Morty");
	sub1.subscribeToTopic("Pizza");
	sub1.subscribeToTopic("Boring topic");
	sub1.subscribeToTopic("Very boring topic");
	sub2.subscribeToTopic("Gaming");
	sub2.subscribeToTopic("Boring topic");
	sub2.subscribeToTopic("Boring topic");
	sub2.subscribeToTopic("Boring topic");
	sub3.subscribeToTopic("Climbing");
	sub3.subscribeToTopic("To be removed");
	return true;
}


bool subUnsubscribeToTopic(){
	Broker broker;
	Subscriber sub1(1, broker), sub2(2, broker), sub3(2, broker);
	subSubscribeToTopic(sub1, sub2, sub3);

	ASSERT_THROW(Client::NonSubscribedTopic,
			sub1.unsubscribeToTopic("No topic"));
	sub1.unsubscribeToTopic("Boring topic");
	ASSERT_THROW(Client::NonSubscribedTopic,
			sub1.unsubscribeToTopic("Boring Topic"));
	sub2.unsubscribeToTopic("Boring topic");
	ASSERT_THROW(Client::NonSubscribedTopic,
			sub3.unsubscribeToTopic("No topic"));
	sub3.unsubscribeToTopic("To be removed");
	ASSERT_THROW(Client::NonSubscribedTopic,
			sub3.unsubscribeToTopic("To be removed"));

	return true;
}


bool subUnsubscribeAll(){
	Broker broker;
	Subscriber sub1(1, broker);
	sub1.subscribeToTopic("Game of thrones");
	sub1.subscribeToTopic("Rick and Morty");
	sub1.subscribeToTopic("Pizza");
	sub1.subscribeToTopic("Boring topic");
	sub1.subscribeToTopic("Very boring topic");

	sub1.unsubscribeAll();
	ASSERT_THROW(Subscriber::NonSubscribedTopic,
			sub1.unsubscribeToTopic("Game of thrones"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,
			sub1.unsubscribeToTopic("Rick and Morty"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,
			sub1.unsubscribeToTopic("Pizza"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,
			sub1.unsubscribeToTopic("Pizza"));

	return true;
}


bool subReceiveMessage(){
	Broker broker;
	Subscriber sub1(1, broker), sub2(2, broker), sub3(2, broker);
	subSubscribeToTopic(sub1, sub2, sub3);

	//ASSERT_THROW(Subscriber::NonSubscribedTopic,
	//		sub1.receiveMessage("This shouldn't work!", "No topic", sub3));
	//ASSERT_THROW(Subscriber::NonSubscribedTopic,
	//		sub2.receiveMessage("This shouldn't work!", "No topic", sub3));
	sub2.receiveMessage("Gaming is for nerds!", "Gaming", sub3);
	sub3.receiveMessage("Reminder to go climbing!", "Climbing", sub3);


	return true;
}


bool pubPublishTopic(Publisher& pub1, Publisher& pub2, Publisher& pub3){
	pub1.publishTopic("Game of thrones");
	pub1.publishTopic("Rick and Morty");
	pub1.publishTopic("Pizza");
	pub1.publishTopic("Boring topic");
	pub1.publishTopic("Very boring topic");
	pub2.publishTopic("Gaming");
	pub2.publishTopic("Boring topic");
	pub2.publishTopic("Boring topic");
	pub2.publishTopic("Boring topic");
	pub3.publishTopic("Climbing");
	pub3.publishTopic("To be removed");

	return true;
}


bool pubUnpublishTopic(){
	Broker broker;
	Publisher pub1(5, broker), pub2(4, broker), pub3(5, broker);

	pubPublishTopic(pub1, pub2, pub3);
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("No topic"));
	pub1.unpublishTopic("Boring topic");
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("Boring Topic"));
	pub2.unpublishTopic("Boring topic");
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub3.unpublishTopic("No topic"));
	pub3.unpublishTopic("To be removed");
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub3.unpublishTopic("To be removed"));

	return true;
}


bool pubUnpublishAll(){
	Broker broker;
	Publisher pub1(1, broker);
	pub1.publishTopic("Game of thrones");
	pub1.publishTopic("Rick and Morty");
	pub1.publishTopic("Pizza");
	pub1.publishTopic("Boring topic");
	pub1.publishTopic("Very boring topic");

	pub1.unpublishAll();
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("Game of thrones"));
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("Rick and Morty"));
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("Pizza"));
	ASSERT_THROW(Publisher::NonPublishedTopic ,
			pub1.unpublishTopic("Pizza"));

	return true;
}


bool pubSendMessage(){
	Broker broker;
	Subscriber sub1(1, broker), sub2(2, broker), sub3(2, broker);
	Publisher pub1(5, broker), pub2(4, broker), pub3(5, broker);
	subSubscribeToTopic(sub1, sub2, sub3);
	pubPublishTopic(pub1, pub2, pub3);

	ASSERT_THROW(Publisher::NonPublishedTopic,
			pub1.sendMessage("This shouldn't work!", "No topic"));
	ASSERT_THROW(Publisher::NonPublishedTopic,
			pub2.sendMessage("This shouldn't work!", "No topic"));
	pub2.sendMessage("Gaming, according to pub2, is for nerds!", "Gaming");
	pub3.sendMessage("Reminder from pub3 to go climbing!", "Climbing");

	return true;
}


bool encSubSubscribeToTopic(EncryptionSubscriber& encSub1,
		EncryptionSubscriber& encSub2){
	encSub1.subscribeToTopic("CIA");
	encSub1.subscribeToTopic("FBI");
	encSub2.subscribeToTopic("KGB");
	encSub2.subscribeToTopic("MOSSAD");

	return true;
}


bool encPubPublishTopic(EncryptionPublisher& encPub1,
		EncryptionPublisher& encPub2){
	encPub1.publishTopic("CIA");
	encPub1.publishTopic("FBI");
	encPub2.publishTopic("KGB");
	encPub2.publishTopic("MOSSAD");

	return true;
}


bool encSubReceiveMessage(){


	return true;
}


bool encPubSendMessage(){
	Broker broker;
	Subscriber sub1(1, broker);
	EncryptionSubscriber encSub1(10, broker, 'k'), encSub2(11, broker, 'l');
	EncryptionPublisher encPub1(20, broker, 'k'), encPub2(21, broker, 'l');
	sub1.subscribeToTopic("Mossad");
	sub1.subscribeToTopic("CIA");
	encSubSubscribeToTopic(encSub1, encSub2);
	encPubPublishTopic(encPub1, encPub2);
	encPub1.sendMessage("Only CIA agents should see this", "CIA");
	encPub1.sendMessage("Only FBI agents should see this", "FBI");
	encPub2.sendMessage("Only KGB agents should see this", "KGB");
	encPub2.sendMessage("Only MOSSAD agents should see this", "MOSSAD");

	return true;

}


bool lironsTest(){
	bool final = true;


	Broker broker;
	Subscriber sub1(1, broker), sub2(2, broker), sub3(2, broker);
	Publisher pub1(5, broker), pub2(4, broker), pub3(5, broker);
	EncryptionSubscriber encSub1(10, broker, 'k'), encSub2(11, broker, 'l');
	EncryptionPublisher encPub1(20, broker, 'k'), encPub2(21, broker, 'l');

	/*
	 * the clients in broker's list should be ordered as follows:
	 * Clients ids: 0 -> 1 -> 2-> 4-> 3-> 5-> 6-> 7-> 8-> 9
	 * or as named here: sub1-> sub2-> sub3-> pub2-> pub1-> pub3->
	 * 					 encSub1-> encSub2-> encPub1-> encPub2
	 */

	final &= clientGetId(sub1, pub1);
	final &= clientGetPriority(sub1, pub1);
	final &= clientReceiveMaintenanceMessage(sub1, pub1);

	final &= subSubscribeToTopic(sub1, sub2, sub3);
	final &= pubPublishTopic(pub1, pub2, pub3);

	final &= brokerSendMaintenanceMessageAny(broker);
	final &= brokerSendMaintenanceMessageAll(broker);

	final &= subUnsubscribeToTopic();
	final &= pubUnpublishTopic();

	final &= subUnsubscribeAll();
	final &= pubUnpublishAll();

	final &= subReceiveMessage();
	final &= pubSendMessage();


	final &= encSubSubscribeToTopic(encSub1, encSub2);
	final &= encPubPublishTopic(encPub1, encPub2);


	final &= encSubReceiveMessage(); 		// <<< next tests takes care of this
	final &= encPubSendMessage();

	return final;
}



/*
 * Hi there,
 * I wrote this test hoping that it should cover mostly everything.
 * The strange thing is that it handles throws pretty badly, in the sense that
 * before making it destruction-proof, as is caused by throws, it wouldn't pass
 * the test even though it should have, which is quite stupid.
 * Hopefully this is tough enough. The result, as printed to cout should be:
 *
 *
Client #0 received maintenance message: Sub1 got this message
Client #3 received maintenance message: Pub1 got this message
Client #0 received maintenance message: Welcome everyone! You're all nerds!
Client #1 received maintenance message: Welcome everyone! You're all nerds!
Client #4 received maintenance message: Welcome everyone! You're all nerds!
Client #3 received maintenance message: Welcome everyone! You're all nerds!
Client #0 received maintenance message: Wow, you're into some really boring things!
Client #3 received maintenance message: Wow, you're into some really boring things!
Topic: Gaming. Sender: #20. Receiver: #19. Message: Gaming is for nerds!
Topic: Climbing. Sender: #20. Receiver: #20. Message: Reminder to go climbing!
Topic: Gaming. Sender: #25. Receiver: #22. Message: Gaming, according to pub2, is for nerds!
Topic: Climbing. Sender: #26. Receiver: #23. Message: Reminder from pub3 to go climbing!
Topic: CIA. Sender: #30. Receiver: #27. Message: $K("*K
KKK
Topic: CIA. Sender: #30. Receiver: #28. Message: Only CIA agents should see this
Topic: FBI. Sender: #30. Receiver: #28. Message: Only FBI agents should see this
Topic: KGB. Sender: #31. Receiver: #29. Message: Only KGB agents should see this
Topic: MOSSAD. Sender: #31. Receiver: #29. Message: Only MOSSAD agents should see this
result returned: 1
 */



int main1(){
	bool result = lironsTest();
	std::cout << "result returned: " << result;
	return 0;
}



