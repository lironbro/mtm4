//
//  PubSubTest.cpp
//  Matam 4
//
//  Created by Dean Leitersdorf on 6/23/16.
//  Copyright © 2016 Dean Leitersdorf. All rights reserved.
//

#include <cstdlib>
#include "MtmTst.h"
#include "Broker.h"
#include "Client.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "EncryptionSubscriber.h"
#include "EncryptionPublisher.h"

#include <list>
#include <assert.h>



/*

 We are going to implement a mini-YouTube.
 All the participants (broker, and all clients) are global variables.
 
 The first function test will connect all clients to relevant topics.
 
 The second function test will send maintance messages.
 
 The third function test will send messages between publishers and subscribers.
 
 The fourth function will disconnect the graph, replace the clients with their
 encrypted version and then reconnect the graph by calling the first function.
 
 The second function will be called again to show that the encryption doesn't 
 effect the maintainence messages.
 
 The fifth function will send encrypted messages between pubs and subs.
 
 Other functions:
 constructorDestructorTest - makes many Clients and Brokers. Check valgrind.

 
 
 ALL TOPICS:
 Funny
 TV & Movies
 Gaming
 Music
 Education
*/


//Globals:
Broker youtube;
std::stringstream youtubeServer;
std::stringstream expectedServer;
#define funny "funny"
#define tv "TV & Movies"
#define gaming "gaming"
#define music "Music"
#define education "education"
std::list<Topic> all_topics = {funny, tv, gaming, music, education};
std::string message = "";

#define checkEqual ASSERT_EQUALS(expectedServer.str(), youtubeServer.str())

#define maintanance(c) expectedServer<< "Client #" << c->getId() << \
" received maintenance message: " << message << std::endl;

#define sendMail(to, from, topic) expectedServer << "Topic: " \
<< topic <<". Sender: #" << from->getId() << \
". Receiver: #" << to->getId() << ". Message: " << message << std::endl;


Subscriber client0(2, youtube, youtubeServer);
Subscriber client1(2, youtube, youtubeServer);
Subscriber client2(0, youtube, youtubeServer);
Publisher client3(2, youtube, youtubeServer);
Publisher client4(0, youtube, youtubeServer);
Subscriber client5(1, youtube, youtubeServer);
Subscriber client6(3, youtube, youtubeServer);
Publisher client7(5, youtube, youtubeServer);
Publisher client8(0, youtube, youtubeServer);
Publisher client9(6, youtube, youtubeServer);
Publisher client10(6, youtube, youtubeServer);
Publisher client11(1, youtube, youtubeServer);
Publisher client12(3, youtube, youtubeServer);
Publisher client13(1, youtube, youtubeServer);
Subscriber client14(2, youtube, youtubeServer);
Subscriber client15(3, youtube, youtubeServer);
Subscriber client16(8, youtube, youtubeServer);
Publisher client17(6, youtube, youtubeServer);


Subscriber *outlaw37 = &client0;
Subscriber *G1 = &client1;
Subscriber *FuSioNuReX = &client2;
Publisher *VEVO = &client3;
Publisher *gameRanks = &client4;
Subscriber *naed90 = &client5;
Subscriber *Elmo582 = &client6;
Publisher *UNITY = &client7;
Publisher *pewdiepie = &client8;
Publisher *technion = &client9;
Publisher *TED = &client10;
Publisher *theSmithPlays = &client11;
Publisher *Dreamworks = &client12;
Publisher *failArmy = &client13;
Subscriber *holyShit33 = &client14;
Subscriber *EZIO = &client15;
Subscriber *zombii = &client16;
Publisher *DNews = &client17;

EncryptionSubscriber client0B(2, youtube, 'c' ,youtubeServer);
Subscriber client1B(2, youtube, youtubeServer);//not encrypted
EncryptionSubscriber client2B(0, youtube, 'a', youtubeServer);
EncryptionPublisher client3B(2, youtube, 'b', youtubeServer);
EncryptionPublisher client4B(0, youtube, 'b', youtubeServer);
Subscriber client5B(1, youtube, youtubeServer);//not encrypted
EncryptionSubscriber client6B(3, youtube, 'a', youtubeServer);
EncryptionPublisher client7B(5, youtube, 'b', youtubeServer);
EncryptionPublisher client8B(0, youtube, 'a', youtubeServer);
Publisher client9B(6, youtube, youtubeServer);//not encrypted
EncryptionPublisher client10B(6, youtube, 'a', youtubeServer);
Publisher client11B(1, youtube, youtubeServer);//not encrypted
Publisher client12B(3, youtube, youtubeServer);//not encrypted
EncryptionPublisher client13B(1, youtube, 'c', youtubeServer);
EncryptionSubscriber client14B(2, youtube, 'b', youtubeServer);
EncryptionSubscriber client15B(3, youtube, 'b', youtubeServer);
EncryptionSubscriber client16B(8, youtube, 'a', youtubeServer);
EncryptionPublisher client17B(6, youtube, 'a', youtubeServer);

bool testMaintenanceSingular();//implemented below
bool testLinkAll()
{
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(funny));
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(gaming));
    ASSERT_NO_THROW(outlaw37->unsubscribeToTopic(education));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(funny));
    ASSERT_THROW(Client::NonSubscribedTopic, outlaw37->unsubscribeToTopic(funny));
    ASSERT_NO_THROW(holyShit33->unsubscribeToTopic(funny));
    
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(music));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(education));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(music));
    ASSERT_NO_THROW(EZIO->subscribeToTopic(tv));
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(education));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(naed90->subscribeToTopic(music));
    ASSERT_NO_THROW(naed90->subscribeToTopic(tv));
    ASSERT_NO_THROW(naed90->subscribeToTopic(education));
    ASSERT_NO_THROW(naed90->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(outlaw37->unsubscribeAll());
    
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_NO_THROW(Dreamworks->publishTopic(music));
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_THROW(Client::NonPublishedTopic, Dreamworks->unpublishTopic(music));
    
    ASSERT_NO_THROW(naed90->unsubscribeAll());
    ASSERT_THROW(Client::NonSubscribedTopic, naed90->unsubscribeToTopic(tv));
    
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeAll());
    ASSERT_NO_THROW(EZIO->unsubscribeAll());
    
    //Now, create actual graph
    //Add subscribers first (testing the FAQ) to show that they get messages
    //even though these topics aren't yet published (they'll get messages
    //when publishers are added and send stuff)
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(funny));
    ASSERT_NO_THROW(outlaw37->subscribeToTopic(tv));
    
    ASSERT_NO_THROW(G1->subscribeToTopic(music));
    ASSERT_NO_THROW(G1->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(funny));
    ASSERT_NO_THROW(holyShit33->subscribeToTopic(tv));
    
    ASSERT_NO_THROW(EZIO->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(zombii->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(tv));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(music));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(funny));
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(education));
    
    ASSERT_NO_THROW(naed90->subscribeToTopic(music));
    ASSERT_NO_THROW(naed90->subscribeToTopic(education));
    ASSERT_NO_THROW(naed90->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(Elmo582->subscribeToTopic(education));
    
    
    
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    ASSERT_NO_THROW(failArmy->publishTopic(gaming));
    //should be removed down the road:
    ASSERT_NO_THROW(failArmy->publishTopic(tv));
    ASSERT_NO_THROW(failArmy->unpublishTopic(tv));
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    ASSERT_NO_THROW(failArmy->unpublishTopic(funny));
    ASSERT_NO_THROW(failArmy->publishTopic(funny));
    
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->publishTopic(gaming));
    ASSERT_NO_THROW(Dreamworks->publishTopic(tv));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(tv));
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->publishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(funny));
    ASSERT_THROW(Client::NonPublishedTopic, Dreamworks->unpublishTopic(funny));
    ASSERT_NO_THROW(Dreamworks->unpublishTopic(gaming));
    ASSERT_NO_THROW(Dreamworks->publishTopic(tv));
    
    ASSERT_NO_THROW(pewdiepie->publishTopic(tv));
    ASSERT_NO_THROW(pewdiepie->publishTopic(gaming));
    ASSERT_NO_THROW(pewdiepie->publishTopic(funny));
    ASSERT_NO_THROW(pewdiepie->unpublishAll());
    ASSERT_NO_THROW(pewdiepie->publishTopic(tv));
    ASSERT_NO_THROW(pewdiepie->publishTopic(gaming));
    ASSERT_NO_THROW(pewdiepie->publishTopic(funny));
    
    ASSERT_NO_THROW(theSmithPlays->publishTopic(gaming));
    ASSERT_NO_THROW(theSmithPlays->publishTopic(funny));
    
    ASSERT_NO_THROW(gameRanks->publishTopic(gaming));
    ASSERT_NO_THROW(gameRanks->publishTopic(tv));
    
    ASSERT_NO_THROW(VEVO->publishTopic(music));
    
    ASSERT_NO_THROW(UNITY->publishTopic(gaming));
    ASSERT_NO_THROW(UNITY->publishTopic(music));
    ASSERT_NO_THROW(UNITY->publishTopic(education));
    
    ASSERT_NO_THROW(technion->publishTopic(education));
    
    ASSERT_NO_THROW(TED->publishTopic(education));
    
    ASSERT_NO_THROW(DNews->publishTopic(education));
    
    //check that everyone is connected
    if(!testMaintenanceSingular())
    {
        assert(false);
        return false;
    }
    
    return true;
}

//checks topic by topic
bool testMaintenanceSingular()
{
    checkEqual;//nothing yet
    
    message = "ALL FUNNY RAISE YOUR HANDS!";
    youtube.sendMaintenanceMessageAny(std::list<Topic>{funny}, message);
    
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    message = "NEW! Trailer for star wars this week!";
    youtube.sendMaintenanceMessageAny(std::list<Topic>{tv}, message);
    
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    maintanance(Dreamworks);
    checkEqual;
    
    message = "Ra Ra Oo La La Roma Roma Ma Ga Ga";
    youtube.sendMaintenanceMessageAny(std::list<Topic>{music}, message);
    
    maintanance(FuSioNuReX);
    maintanance(naed90);
    maintanance(G1);
    maintanance(VEVO);
    maintanance(UNITY);
    checkEqual;
    
    message = "Last night on Runescape, a lvl 37...";
    youtube.sendMaintenanceMessageAny(std::list<Topic>{gaming}, message);
    
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(G1);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(zombii);
    checkEqual;
    
    message = "David Zileg: The determinant... zzZZ";
    youtube.sendMaintenanceMessageAny(std::list<Topic>{education}, message);
    
    maintanance(FuSioNuReX);
    maintanance(naed90);
    maintanance(Elmo582);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    checkEqual;
    
    return true;
}

bool testMaintenance()
{
    if(!testMaintenanceSingular())
    {
        assert(false);
        return false;
    }
    
    message = "EVERYONE! WAKE UP!";
    youtube.sendMaintenanceMessageAny(all_topics, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(G1);
    maintanance(VEVO);
    maintanance(holyShit33);
    maintanance(Elmo582);
    maintanance(Dreamworks);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    maintanance(zombii);
    checkEqual;
    
    message = "Fuze - Only you my man";
    youtube.sendMaintenanceMessageAll(all_topics, message);
    maintanance(FuSioNuReX);
    checkEqual;
    
    youtube.sendMaintenanceMessageAny({}, "Sleep everyone, sleep...");
    checkEqual;
    
    //according to izik, the following should send to no one
    youtube.sendMaintenanceMessageAll({}, "Sleep everyone, sleep...");
    checkEqual;
    
    youtube.sendMaintenanceMessageAny(std::list<Topic>{"shiiiiit"}, message);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll(std::list<Topic>{"shiiiiit", funny}, message);
    checkEqual;
    
    message = "HAHAHAHAHAHA HAHAHA";
    youtube.sendMaintenanceMessageAll({funny, tv}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll({tv, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(outlaw37);
    maintanance(holyShit33);
    checkEqual;
    
    message = "OPERA OPERA!!!";
    youtube.sendMaintenanceMessageAll(std::list<Topic>{funny, tv, music}, message);
    maintanance(FuSioNuReX);
    checkEqual;
    
    youtube.sendMaintenanceMessageAll(std::list<Topic>{funny, music, tv}, message);
    maintanance(FuSioNuReX);
    checkEqual;
    
    message = "this exists?";
    youtube.sendMaintenanceMessageAll({gaming, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(pewdiepie);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    checkEqual;
    
    
    message = "fdsanfsdfinewuobfdsn";
    youtube.sendMaintenanceMessageAny({gaming, funny}, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(outlaw37);
    maintanance(G1);
    maintanance(holyShit33);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(zombii);
    checkEqual;
    
    message = "smart and exotic";
    youtube.sendMaintenanceMessageAny({gaming, education}, message);
    maintanance(FuSioNuReX);
    maintanance(gameRanks);
    maintanance(pewdiepie);
    maintanance(naed90);
    maintanance(theSmithPlays);
    maintanance(failArmy);
    maintanance(G1);
    maintanance(Elmo582);
    maintanance(EZIO);
    maintanance(UNITY);
    maintanance(technion);
    maintanance(TED);
    maintanance(DNews);
    maintanance(zombii);
    checkEqual;
    
    return true;
}

bool sendMessages()
{
    message = "m";
    ASSERT_NO_THROW(failArmy->sendMessage(message, funny));
    sendMail(FuSioNuReX, failArmy, funny);
    sendMail(outlaw37, failArmy, funny);
    sendMail(holyShit33, failArmy, funny);
    checkEqual;
    
    message = "fdason";
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    failArmy->unpublishTopic(gaming);
    ASSERT_THROW(Client::NonPublishedTopic, failArmy->sendMessage(message, gaming));
    checkEqual;
    
    failArmy->publishTopic(gaming);
    failArmy->publishTopic(gaming);
    failArmy->publishTopic(gaming);
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeToTopic(gaming));
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    ASSERT_NO_THROW(FuSioNuReX->subscribeToTopic(gaming));
    
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    sendMail(FuSioNuReX, failArmy, gaming);
    sendMail(naed90, failArmy, gaming);
    sendMail(G1, failArmy, gaming);
    sendMail(EZIO, failArmy, gaming);
    sendMail(zombii, failArmy, gaming);
    checkEqual;
    
    return true;
}

bool unlinkAll()
{
    
    ASSERT_NO_THROW(outlaw37->unsubscribeAll());
    ASSERT_NO_THROW(G1->unsubscribeAll());
    ASSERT_NO_THROW(FuSioNuReX->unsubscribeAll());
    ASSERT_NO_THROW(VEVO->unpublishAll());
    ASSERT_NO_THROW(gameRanks->unpublishAll());
    ASSERT_NO_THROW(naed90->unsubscribeAll());
    ASSERT_NO_THROW(Elmo582->unsubscribeAll());
    ASSERT_NO_THROW(UNITY->unpublishAll());
    ASSERT_NO_THROW(pewdiepie->unpublishAll());
    ASSERT_NO_THROW(technion->unpublishAll());
    ASSERT_NO_THROW(TED->unpublishAll());
    ASSERT_NO_THROW(theSmithPlays->unpublishAll());
    ASSERT_NO_THROW(Dreamworks->unpublishAll());
    ASSERT_NO_THROW(failArmy->unpublishAll());
    ASSERT_NO_THROW(holyShit33->unsubscribeAll());
    ASSERT_NO_THROW(EZIO->unsubscribeAll());
    ASSERT_NO_THROW(zombii->unsubscribeAll());
    ASSERT_NO_THROW(DNews->unpublishAll());
    
    return true;
}

bool turnOnEncryption()
{
    
    if(!unlinkAll())
    {
        assert(false); //instead of doing RUN_TEST(unlinkAll), because we
        //want to return a value from this function.
        return false;
    }
    
    checkEqual;
    
    //Test that no topic holds any person anymore:
    youtube.sendMaintenanceMessageAny(all_topics,
                                      "You should be disconnected!");
    checkEqual;
    //above equals makes sure that server did not change, which means
    //nobody got the message, meaning everyone is disconnected.
    
    
    //Replace pointers with encrypted versions of clients
    outlaw37 = &client0B;
    G1 = &client1B;
    FuSioNuReX = &client2B;
    VEVO = &client3B;
    gameRanks = &client4B;
    naed90 = &client5B;
    Elmo582 = &client6B;
    UNITY = &client7B;
    pewdiepie = &client8B;
    technion = &client9B;
    TED = &client10B;
    theSmithPlays = &client11B;
    Dreamworks = &client12B;
    failArmy = &client13B;
    holyShit33 = &client14B;
    EZIO = &client15B;
    zombii = &client16B;
    DNews = &client17B;
    
    //attempt to reconnect the graph - this shouldn't fail
    if(!testLinkAll())
    {
        assert(false);
        return false;
    }
    
    
    //All passed well:
    return true;
}

bool sendEncryptedMessages()
{
    
    message = "ccccc";
    ASSERT_NO_THROW(failArmy->sendMessage(message, funny));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, funny);
    message = "ccccc";
    sendMail(outlaw37, failArmy, funny);
    message = "bbbbb";
    sendMail(holyShit33, failArmy, funny);
    checkEqual;
    /*
    message = "ccccc";
    ASSERT_NO_THROW(failArmy->sendMessage(message, gaming));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, gaming);
    message = "\0\0\0\0\0";
    sendMail(naed90, failArmy, gaming);
    message = "\0\0\0\0\0";
    sendMail(G1, failArmy, gaming);
    message = "bbbbb";
    sendMail(EZIO, failArmy, gaming);
    message = "aaaaa";
    sendMail(zombii, failArmy, gaming);
    
    
    std::cout << expectedServer.str() << std::endl;
    std::cout << youtubeServer.str() << std::endl;
    checkEqual;*/
    
    /*
    //message = "\0\0\0\0\0";
    naed90->unsubscribeToTopic(gaming);
    G1->unsubscribeToTopic(gaming);
    std::string specialMessage("\0\0\0\0\0",5);
    ASSERT_NO_THROW(theSmithPlays->sendMessage(specialMessage, gaming));
    message = "aaaaa";
    sendMail(FuSioNuReX, failArmy, gaming);
    //message = "";
    //sendMail(naed90, failArmy, gaming);
    //message = "";
    //sendMail(G1, failArmy, gaming);
    message = "bbbbb";
    sendMail(EZIO, failArmy, gaming);
    message = "aaaaa";
    sendMail(zombii, failArmy, gaming);
    std::cout << expectedServer.str() << std::endl;
    std::cout << youtubeServer.str() << std::endl;
    checkEqual;*/
    
    return true;
}

bool constructorDestructorTest()
{
    
    std::stringstream blah;
    Broker *b4 = new Broker();
    
    try {
        Subscriber cNeg (-1, *b4, blah);
        assert(false);
    } catch (Client::IllegalPriority) {
        //ok
    } catch (...)
    {
        assert(false);
    }
    
    try {
        Publisher cNeg (-1, *b4, blah);
        assert(false);
    } catch (Client::IllegalPriority) {
        //ok
    } catch (...)
    {
        assert(false);
    }
    
    Subscriber client0(2, *b4, blah);
    EncryptionSubscriber client1(2, *b4, 'a', blah);
    Publisher client2(2, *b4, blah);
    Subscriber client3(2, *b4, blah);
    EncryptionPublisher client4(2, *b4, 'b', blah);
    Subscriber client5(2, *b4, blah);
    Publisher client6(2, *b4, blah);
    
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("f");
    client0.subscribeToTopic("e");
    client0.subscribeToTopic("t");
    client0.subscribeToTopic("g");
    client0.subscribeToTopic("n");
    client0.subscribeToTopic("d");
    client0.subscribeToTopic("s");
    client0.subscribeToTopic("e");
    
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("f");
    client1.subscribeToTopic("e");
    client1.subscribeToTopic("t");
    client1.subscribeToTopic("g");
    client1.subscribeToTopic("n");
    client1.subscribeToTopic("d");
    client1.subscribeToTopic("s");
    client1.subscribeToTopic("e");
    
    
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("f");
    client2.publishTopic("e");
    client2.publishTopic("t");
    client2.publishTopic("g");
    client2.publishTopic("n");
    client2.publishTopic("d");
    client2.publishTopic("s");
    client2.publishTopic("e");
    
    
    
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("f");
    client3.subscribeToTopic("e");
    client3.subscribeToTopic("t");
    client3.subscribeToTopic("g");
    client3.subscribeToTopic("n");
    client3.subscribeToTopic("d");
    client3.subscribeToTopic("s");
    client3.subscribeToTopic("e");
    
    
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("f");
    client4.publishTopic("e");
    client4.publishTopic("t");
    client4.publishTopic("g");
    client4.publishTopic("n");
    client4.publishTopic("d");
    client4.publishTopic("s");
    client4.publishTopic("e");
    
    client2.sendMessage("blah1", "f");
    client2.sendMessage("blah1", "e");
    client2.sendMessage("blah1", "t");
    client2.sendMessage("blah1", "d");
    client2.sendMessage("blah1", "n");
    
    
    client3.unsubscribeAll();
    
    client2.unpublishAll();
    
    delete b4;
    
    return true;
}

void pubSubTest()
{
    RUN_TEST(constructorDestructorTest);
    RUN_TEST(testLinkAll);
    RUN_TEST(testMaintenance);
    RUN_TEST(sendMessages);
    RUN_TEST(turnOnEncryption);
    RUN_TEST(testMaintenance);
    RUN_TEST(sendEncryptedMessages);
}

int main()
{
    pubSubTest();
    return 0;
}
