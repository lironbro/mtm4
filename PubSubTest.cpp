#include <cstdlib>
#include "Broker.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"
#include "MtmTst.h"

//*********************************************************//
using namespace std;
//*********************************************************//
bool pubSubTestExample() {
	Broker broker;
    stringstream ss;
    Publisher p1(0, broker, ss);
    Subscriber s1(1, broker, ss);
    Subscriber s2(0, broker, ss);
    EncryptionPublisher ep1(1, broker, static_cast<char>(0xFF), ss);
    EncryptionSubscriber es1(2, broker, static_cast<char>(0xFF), ss);

    p1.publishTopic("Cat Videos");
    p1.publishTopic("Dog Videos");
    ep1.publishTopic("Marianas Web");

    s1.subscribeToTopic("Cat Videos");
    s2.subscribeToTopic("Cat Videos");
    s2.subscribeToTopic("Dog Videos");
    es1.subscribeToTopic("Marianas Web");

    p1.sendMessage("This is a cat video", "Cat Videos");
    p1.sendMessage("This is a dog video", "Dog Videos");
    ep1.sendMessage("This is a big secret", "Marianas Web");

    stringstream expected;
    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
            ". Receiver: #" << s2.getId() << ". Message: " << "This is a cat video" << endl;
    expected << "Topic: " << "Cat Videos" << ". Sender: #" << p1.getId() <<
    ". Receiver: #" << s1.getId() << ". Message: " << "This is a cat video" << endl;
    expected << "Topic: " << "Dog Videos" << ". Sender: #" << p1.getId() <<
    ". Receiver: #" << s2.getId() << ". Message: " << "This is a dog video" << endl;
    expected << "Topic: " << "Marianas Web" << ". Sender: #" << ep1.getId() <<
    ". Receiver: #" << es1.getId() << ". Message: " << "This is a big secret" << endl;

    ASSERT_EQUALS(expected.str(), ss.str());

    return true;
}
//*********************************************************//
bool subscribeToTopicTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.subscribeToTopic("Appetizers");
	/*illegal priority exception*/
	ASSERT_THROW(Client::IllegalPriority, (Subscriber(-100, broker, ss)));

	ASSERT_NO_THROW(Subscriber(0, broker, ss));
	return true;
}
//*********************************************************//
bool unsubscribeToTopicTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.subscribeToTopic("Appetizers");

	hungry.unsubscribeToTopic("Desserts");
	hungry.unsubscribeToTopic("Main courses");
	hungry.unsubscribeToTopic("Brunches");
	hungry.unsubscribeToTopic("Midnight snacks");
	hungry.unsubscribeToTopic("Salads");
/*unsubscribing same topic*/
	hungry.unsubscribeToTopic("Appetizers");
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("Appetizers"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("None existing topic"));
	ASSERT_THROW(Subscriber::NonSubscribedTopic,hungry.unsubscribeToTopic("Appetizers"));

	return true;
}
//*********************************************************//
bool unsubscribeAllTest() {
	Broker broker;
	stringstream ss;
	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");
	hungry.unsubscribeAll();
	hungry.unsubscribeAll();

	Subscriber thirsty(1, broker, ss);
	thirsty.unsubscribeAll();
	return true;
}
//*********************************************************//
bool receiveMessageTest() {
	Broker broker;
	stringstream ss;
	Publisher bakery_house(5, broker, ss);

	Subscriber hungry(1, broker, ss);
	hungry.subscribeToTopic("Desserts");
	hungry.subscribeToTopic("Main courses");
	hungry.subscribeToTopic("Appetizers");
	hungry.subscribeToTopic("Brunches");
	hungry.subscribeToTopic("Midnight snacks");
	hungry.subscribeToTopic("Salads");

	hungry.receiveMessage("chocolate croissant", "Desserts", bakery_house);
	hungry.receiveMessage("mini pizza", "Appetizers", bakery_house);
	hungry.receiveMessage("fruit salad", "Salads", bakery_house);
	hungry.receiveMessage("egg muffin", "Main courses", bakery_house);
	hungry.receiveMessage("chocolate chip cookies and milk", "Midnight snacks",
			bakery_house);
	hungry.receiveMessage("waffles with icecream", "Brunches", bakery_house);
	hungry.receiveMessage("eggs and bacon muffins", "Brunches", bakery_house);

	stringstream expected;
	expected << "Topic: " << "Desserts" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "chocolate croissant" << endl;
	expected << "Topic: " << "Appetizers" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "mini pizza" << endl;
	expected << "Topic: " << "Salads" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "fruit salad" << endl;
	expected << "Topic: " << "Main courses" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "egg muffin" << endl;

	expected << "Topic: " << "Midnight snacks" << ". Sender: #"
			<< bakery_house.getId() << ". Receiver: #" << hungry.getId()
			<< ". Message: " << "chocolate chip cookies and milk" << endl;

	expected << "Topic: " << "Brunches" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "waffles with icecream" << endl;
	expected << "Topic: " << "Brunches" << ". Sender: #" << bakery_house.getId()
			<< ". Receiver: #" << hungry.getId() << ". Message: "
			<< "eggs and bacon muffins" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("hamburger and chips", "junk food",
					bakery_house));

	hungry.unsubscribeToTopic("Desserts");
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("french toast", "Desserts", bakery_house));
	hungry.subscribeToTopic("Desserts");
	ASSERT_NO_THROW(
			hungry.receiveMessage("french toast", "Desserts", bakery_house));

	hungry.unsubscribeAll();

	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("bagel", "Brunches", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("banana split", "Desserts", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("pancakes with freshly cut fruit and nutella",
					"Appetizers", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("mjaddara", "Main courses", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("take abreak..have some snickers",
					"Midnight snacks", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("Tabboli", "Salads", bakery_house));
	ASSERT_THROW(Client::NonSubscribedTopic,
			hungry.receiveMessage("junk food is healthy.", "junk food",
					bakery_house));

	return true;
}
//*********************************************************//
bool PublishTopicTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	return true;
}
//*********************************************************//
bool unPublishTopicTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("Dominos crappy pizza"));
	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("Munch yum yum"));
	ASSERT_THROW(Subscriber::NonPublishedTopic,Pizza_Hut.unpublishTopic("pizza is love.. pizza is life!"));

	Pizza_Hut.unpublishTopic("Cheesy Bites");
	Pizza_Hut.unpublishTopic("Pizza Dip");
	Pizza_Hut.unpublishTopic("Family Sized Pizza");
	Pizza_Hut.unpublishTopic("Cheese Stuffed Crust");
	Pizza_Hut.unpublishTopic("Magaritta");

	ASSERT_THROW(Publisher::NonPublishedTopic,Pizza_Hut.unpublishTopic("Cheesy Bites"));

	Pizza_Hut.publishTopic("Cheesy Bites");
	ASSERT_NO_THROW(Pizza_Hut.unpublishTopic("Cheesy Bites"));

	return true;
}
//*********************************************************//
bool unPublishAllTest() {
	Broker broker;
	stringstream ss;
	Publisher Pizza_Hut(2, broker, ss);
	Pizza_Hut.publishTopic("Cheesy Bites");
	Pizza_Hut.publishTopic("Pizza Dip");
	Pizza_Hut.publishTopic("Family Sized Pizza");
	Pizza_Hut.publishTopic("Cheese Stuffed Crust");
	Pizza_Hut.publishTopic("Magaritta");
	Pizza_Hut.publishTopic("Cheesy Bites");

	Pizza_Hut.unpublishAll();
	return true;
}
//*********************************************************//
bool sendMessageTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	Publisher Resturant(10, broker, ss);
	Resturant.publishTopic("Lunch Deals");
	Resturant.sendMessage("Nobody should get this message", "Lunch Deals");
	ASSERT_EQUALS(expected.str(), ss.str());
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(2, broker, ss);
	Subscriber customer3(4, broker, ss);
	Subscriber customer4(3, broker, ss);
	Subscriber customer5(5, broker, ss);
	Subscriber customer6(5, broker, ss);

	customer1.subscribeToTopic("Lunch Deals");
	customer3.subscribeToTopic("Lunch Deals");
	customer2.subscribeToTopic("Lunch Deals");
	customer4.subscribeToTopic("Lunch Deals");
	customer5.subscribeToTopic("Lunch Deals");

	Resturant.sendMessage("Great Lunch deal! fish and chips for 50%",
			"Lunch Deals");

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer2.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer4.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer3.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;
	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer1.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;
	expected << "Topic: " << "Lunch Deals" << ". Sender: #" << Resturant.getId()
			<< ". Receiver: #" << customer5.getId() << ". Message: "
			<< "Great Lunch deal! fish and chips for 50%" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	ASSERT_THROW(Client::NonPublishedTopic,
			Resturant.sendMessage("this is spam!", "Dinner Deals"));

	Resturant.unpublishTopic("Lunch Deals");
	ASSERT_THROW(Client::NonPublishedTopic,
			Resturant.sendMessage("this is spam!", "Lunch Deals"));

	Resturant.publishTopic("Sunday Brunch");
	Resturant.sendMessage("Free cocktail!", "Sunday Brunch");

	ASSERT_EQUALS(expected.str(), ss.str());

	return true;
}
//*********************************************************//
bool sendMaintenanceMessageAnyTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	//publishers
	Publisher Mccdonalds(7, broker, ss);
	Publisher Burger_king(9, broker, ss);
	Publisher Zesty(1, broker, ss);
	Publisher Japanika(8, broker, ss);
	Publisher Max_Brenner(2, broker, ss);
	//subscribers
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(9, broker, ss);
	Subscriber customer3(3, broker, ss);
	Subscriber customer4(7, broker, ss);
	Subscriber customer5(4, broker, ss);

	//creating topics list
	std::list<Topic> topics;
	topics.insert(topics.begin(), "Desserts");
	topics.insert(topics.begin(), "Main courses");
	topics.insert(topics.begin(), "Appetizers");
	topics.insert(topics.begin(), "Brunches");
	topics.insert(topics.begin(), "Salads");
	topics.insert(topics.begin(), "Midnight snacks");

	broker.sendMaintenanceMessageAny(topics, "Everybody is HUNGRY!");
	ASSERT_EQUALS(expected.str(), ss.str());

	customer5.subscribeToTopic("Junk Food");

	customer1.subscribeToTopic("Appetizers");
	customer2.subscribeToTopic("Salads");
	customer3.subscribeToTopic("Salads");
	customer4.subscribeToTopic("Salads");
	Mccdonalds.publishTopic("Midnight snacks");
	Burger_king.publishTopic("Brunches");
	Zesty.publishTopic("Appetizers");
	Japanika.publishTopic("Main courses");
	Max_Brenner.publishTopic("Desserts");


	broker.sendMaintenanceMessageAny(topics, "Sushi Rolls on the house!");

	expected << "Client #" << Zesty.getId() << " received maintenance message: "
			<< "Sushi Rolls on the house!" << endl;
	expected << "Client #" << Max_Brenner.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer3.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer1.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Mccdonalds.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer4.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Japanika.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Burger_king.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer2.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;

ASSERT_EQUALS(expected.str(),ss.str());
	return true;
}
//*********************************************************//
bool sendMaintenanceMessageAllTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;
	//publishers
	Publisher Mccdonalds(7, broker, ss);
	Publisher Burger_king(9, broker, ss);
	Publisher Zesty(1, broker, ss);
	Publisher Japanika(8, broker, ss);
	Publisher Max_Brenner(2, broker, ss);
	//subscribers
	Subscriber customer1(5, broker, ss);
	Subscriber customer2(9, broker, ss);
	Subscriber customer3(3, broker, ss);
	Subscriber customer4(7, broker, ss);
	Subscriber customer5(4, broker, ss);

	//creating topics list
	std::list<Topic> topics;
	topics.insert(topics.begin(), "Desserts");
	topics.insert(topics.begin(), "Main courses");
	topics.insert(topics.begin(), "Salads");

	customer5.subscribeToTopic("Salads");
	customer5.subscribeToTopic("Desserts");

	customer1.subscribeToTopic("Salads");
	customer2.subscribeToTopic("Salads");
	customer3.subscribeToTopic("Salads");
	customer4.subscribeToTopic("Salads");
	Mccdonalds.publishTopic("Salads");
	Burger_king.publishTopic("Salads");
	Zesty.publishTopic("Salads");
	Japanika.publishTopic("Salads");
	Max_Brenner.publishTopic("Salads");

	customer1.subscribeToTopic("Main courses");
	customer2.subscribeToTopic("Main courses");
	customer3.subscribeToTopic("Main courses");
	customer4.subscribeToTopic("Main courses");
	Mccdonalds.publishTopic("Main courses");
	Burger_king.publishTopic("Main courses");
	Zesty.publishTopic("Main courses");
	Japanika.publishTopic("Main courses");
	Max_Brenner.publishTopic("Main courses");

	customer1.subscribeToTopic("Desserts");
	customer2.subscribeToTopic("Desserts");
	customer3.subscribeToTopic("Desserts");
	customer4.subscribeToTopic("Desserts");
	Mccdonalds.publishTopic("Desserts");
	Burger_king.publishTopic("Desserts");
	Zesty.publishTopic("Desserts");
	Japanika.publishTopic("Desserts");
	Max_Brenner.publishTopic("Desserts");

	broker.sendMaintenanceMessageAll(topics, "Sushi Rolls on the house!");

	expected << "Client #" << Zesty.getId() << " received maintenance message: "
			<< "Sushi Rolls on the house!" << endl;
	expected << "Client #" << Max_Brenner.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer3.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer1.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Mccdonalds.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer4.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Japanika.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << Burger_king.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;
	expected << "Client #" << customer2.getId()
			<< " received maintenance message: " << "Sushi Rolls on the house!"
			<< endl;

	ASSERT_EQUALS(expected.str(), ss.str());

	topics.insert(topics.begin(), "Sushi");
	broker.sendMaintenanceMessageAll(topics, "Sushi Rolls on the house!");
	ASSERT_EQUALS(expected.str(), ss.str());



	return true;
}
//*********************************************************//
bool EncryptionTest() {
	Broker broker;
	stringstream ss;
	stringstream expected;

	EncryptionPublisher Cafe_cafe(1, broker, static_cast<char>(0xFF), ss);
	EncryptionPublisher Mandarin(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer1(3, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer2(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer3(4, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer4(2, broker, static_cast<char>(0xFF), ss);
	EncryptionSubscriber customer5(2, broker, static_cast<char>(0xFF), ss);

	Cafe_cafe.publishTopic("Afternoon Sale");
	Mandarin.publishTopic("Free Ice-coffee");

	customer1.subscribeToTopic("Afternoon Sale");
	customer2.subscribeToTopic("Afternoon Sale");
	customer3.subscribeToTopic("Afternoon Sale");
	customer4.subscribeToTopic("Afternoon Sale");
	customer5.subscribeToTopic("Afternoon Sale");

	Cafe_cafe.sendMessage("All pasta meals for 20% off!", "Afternoon Sale");

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer2.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer4.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer5.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;
	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer1.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;
	expected << "Topic: " << "Afternoon Sale" << ". Sender: #"
			<< Cafe_cafe.getId() << ". Receiver: #" << customer3.getId()
			<< ". Message: " << "All pasta meals for 20% off!" << endl;

	ASSERT_EQUALS(expected.str(), ss.str());
	return true;
}
//*********************************************************//
bool pubSubTest() {
 RUN_TEST(pubSubTestExample);
	//Subscriber
	RUN_TEST(subscribeToTopicTest);
	RUN_TEST(unsubscribeToTopicTest);
	RUN_TEST(unsubscribeAllTest);
	RUN_TEST(receiveMessageTest);
	//Publisher
	RUN_TEST(PublishTopicTest);
	RUN_TEST(unPublishTopicTest);
	RUN_TEST(unPublishAllTest);
	RUN_TEST(sendMessageTest);
	//Broker
	RUN_TEST(sendMaintenanceMessageAnyTest);
	RUN_TEST(sendMaintenanceMessageAllTest);
	RUN_TEST(EncryptionTest);
	return true;
}
//*********************************************************//

int main(){
	pubSubTest();
	return 0;
}
