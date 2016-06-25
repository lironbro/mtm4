/*
 * SortedSetTest.cpp
 *
 *  Created on: 24 αιεπι 2016
 *      Author: Zivkr
 */

#include <cstdlib>
#include "SortedSet.h"
#include "MtmTst.h"

class Int
{
    int this_int;

public:
    Int (int n) : this_int(n){};

    bool operator<(Int const& second) const
    {
        return this->this_int < second.this_int;
    }

};

bool IntsEqual(const Int& a, const Int& b){
    return (!(a<b) && !(b<a));
}

template<class T, class Compare>
bool operator==(const SortedSet<T, Compare>& set_1,
		const SortedSet<T, Compare>& set_2) {
	auto iterator_1 = set_1.begin(), iterator_2 = set_2.begin(),
			end = set_1.end();
	while (iterator_1 != end && iterator_2 != end) {
		if (Compare()(*iterator_1, *iterator_2) ||
				Compare()(*iterator_2++, *iterator_1++)) {
			return false;
		}
	}
	if (iterator_1 != end || iterator_2 != end) {
		return false;
	}
	return true;
}

bool testConstruct(){

	int delta = 1;
	SortedSet<Int> set1;
	//Checks for empty set:
	ASSERT_EQUALS(true, nullptr == set1.begin().getNode());
	for(int i = 1; i < 100; i++, delta+=i){
		set1.insert(delta);
	}
	SortedSet<Int> set1copy(set1);
	ASSERT_EQUALS(true, set1 == set1copy);

	SortedSet<Int> set2;
	for(int i=1, delta = 100; i<10000; i++, delta-=i){
		set2.insert(delta);
	}
	SortedSet<Int> set2copy(set2);
	ASSERT_EQUALS(true, set2copy == set2);

	SortedSet<Int> setEmpty;
	SortedSet<Int> setEmptyCopy(setEmpty);
	ASSERT_EQUALS(true, setEmpty == setEmptyCopy);
	ASSERT_EQUALS(true, setEmptyCopy.begin().getNode() == nullptr);

	return true;
}

bool testInsert(){

	Int toInsert = 10;
	SortedSet<Int> set1;
	// Inserting into an empty set:
	set1.insert(toInsert);
	toInsert = 5;
	// Inserting before first object:
	ASSERT_EQUALS(true, set1.insert(toInsert));
	ASSERT_EQUALS(false, set1.insert(toInsert));
	SortedSet<Int>::iterator ite = set1.begin();
	ASSERT_EQUALS(true, IntsEqual(*(ite), toInsert));
	// Inserting after last object:
	toInsert = 15;
	ASSERT_EQUALS(true, set1.insert(toInsert));
	ASSERT_EQUALS(false, set1.insert(toInsert));
	ite++;
	toInsert = 10;
	ASSERT_EQUALS(false, set1.insert(toInsert));
	ASSERT_EQUALS(true, IntsEqual(*(ite), toInsert));
	// Inserting between objects:
	toInsert = 12;
	ASSERT_EQUALS(true, set1.insert(toInsert));
	ASSERT_EQUALS(false, set1.insert(toInsert));
	ite++;
	ASSERT_EQUALS(true, IntsEqual(*(ite), toInsert));
	ite++;
	toInsert = 15;
	ASSERT_EQUALS(true, IntsEqual(*(ite), toInsert));

	SortedSet<Int> set2;
	// Continuous insert:
	int delta=1;
	for(int i=0; i<1000; i++, delta+=2*i){
		ASSERT_EQUALS(true, set2.insert(delta));
	}

	// Trying to insert values that already exist.
	for(int i=0, delta=1; i<1000; i++, delta+=2*i){
		ASSERT_EQUALS(false, set2.insert(delta));
	}

	return true;
}

bool testAssignment(){
	SortedSet<Int> set1;
	SortedSet<Int> set2;
	// Checking assignment of empty set to non empty set:
	Int data(5);
	set1.insert(data);
	ASSERT_EQUALS(true, IntsEqual(*(set1.begin()), data));
	set1 = set2;
	ASSERT_EQUALS(true, set1.begin().getNode() == nullptr);

	// Checking assignment of non empty set to empty set:
	int delta=5;
	for(int i=0; i<100; i++, delta+=5){
		data = delta;
		set2.insert(data);
	}
	set1 = set2;
	SortedSet<Int>::iterator ite1 = set1.begin();
	delta = 5;
	for(; ite1 != set1.end(); ite1++, delta+=5){
		data=delta;
		ASSERT_EQUALS(true, IntsEqual(*ite1, data));
	}

	// Checking assignment of non empty set to non empty set:
	SortedSet<Int> set3;
	delta = 3;
	for(int i=0; i<100; i++, delta+=3){
		data = delta;
		set3.insert(data);
	}
	set1 = set3;
	SortedSet<Int>::iterator ite2 = set1.begin();
	delta = 3;
	for(; ite2 != set1.end(); ite2++, delta+=3){
		data=delta;
		ASSERT_EQUALS(true, IntsEqual(*ite2, data));
	}

	return true;
}

bool testFindContain(){ // Contains() is used mainly from find().
	SortedSet<Int> set1;
	Int data = 0;
	int delta = 5;
	for(int i=0; i<5; i++, delta+=5){
		data = delta;
		set1.insert(data);
	}
	// Searching for existing objects:
	SortedSet<Int>::iterator ite = set1.begin();
	delta = 5;
	for(; ite != set1.end(); ite++, delta+=5){
		data = delta;
		ASSERT_EQUALS(true,  IntsEqual(*(set1.find(data)), delta));
	}
	// Searching for data that doesn't exist:
	data = 3;
	ASSERT_EQUALS(true, set1.find(data) == SortedSet<Int>::iterator(nullptr));

	//Searching in an empty set:
	SortedSet<Int> setEmpty;
	ASSERT_EQUALS(true, set1.find(data) == SortedSet<Int>::iterator(nullptr));

	return true;
}

bool testRemove(){
	//Int data = 1;
	SortedSet<Int> set1;
	set1.insert(1);
	set1.insert(2);
	set1.insert(3);
	set1.insert(4);
	set1.insert(5);
	// Checking removal of first object:
	SortedSet<Int>::Node* second = (set1.find(2)).getNode();
	ASSERT_NOT_EQUALS(nullptr, second);
	set1.remove(1); // Removes first object.
	ASSERT_EQUALS(second, set1.begin().getNode());
	// Checking removal of last object:
	SortedSet<Int>::Node* fourth = (set1.find(4)).getNode();
	ASSERT_NOT_EQUALS(nullptr, fourth);
	set1.remove(5);
	SortedSet<Int>::iterator ite = set1.begin();
	for(; ite.getNext()!=nullptr; ite++){
	}
	ASSERT_EQUALS(fourth, ite.getNode());
	ASSERT_EQUALS(false, set1.remove(5));
	ASSERT_EQUALS(false, set1.remove(1));

	// Continuous removal:
	SortedSet<Int> set2;
	for(int i=0; i<20; i++){
		set2.insert(i);
	}
	ASSERT_EQUALS(false, set2.remove(21));
	for(int i=0; i<20; i++){
		ASSERT_EQUALS(true, set2.remove(i));
	}
	ASSERT_EQUALS(set2.begin(), SortedSet<Int>::iterator(nullptr));

	// Checking removal of an object on a set with only one object:
	SortedSet<Int> set3;
	set3.insert(1);
	ASSERT_EQUALS(true, set3.remove(1));
	ASSERT_EQUALS(set3.begin(), SortedSet<Int>::iterator(nullptr));

	return true;
}

bool testSize(){
	SortedSet<Int> set1;
	// Checking size of an empty set:
	ASSERT_EQUALS(0, set1.size());
	// Checking size of a non empty set:
	for(int i=0; i<50; i++){
		set1.insert(i);
		ASSERT_EQUALS(i+1, set1.size());
	}

	return true;
}

bool testOpGroups(){
	SortedSet<Int> set1;
	SortedSet<Int> set2;

	// Checking minus operator:
	for(int i=1; i<=10; i++){
		set1.insert(i);
	}
	set2.insert(3);
	set2.insert(6);
	set2.insert(9);
	set1 -= set2;
	ASSERT_EQUALS(true, !set1.contains(3) && !set1.contains(6)
			&& !set1.contains(9));
	SortedSet<Int> set3; // Empty set.
	set2 -= set3;
	ASSERT_EQUALS(3, set2.size());
	ASSERT_EQUALS(true, set2.contains(3) && set2.contains(6)
			&& set2.contains(9));
	set1 -= set1; // After this set1 should be empty.
	ASSERT_EQUALS(SortedSet<Int>::iterator(nullptr), set1.begin());

	// Checking | operator:
	set3.insert(1);
	set3.insert(2);
	set3.insert(4);
	set3.insert(5);
	set3.insert(7);
	set3.insert(8);
	set2 |= set3;
	for(int i=1; i<=9; i++){
		ASSERT_EQUALS(true, set2.contains(i));
	}
	set3 = set2; // Checking | operator on same sets:
	SortedSet<Int> set4 = set3 | set2;
	for(int i=1; i<=9; i++){
		ASSERT_EQUALS(true, set4.contains(i));
	}

	// Checking & operator:
	SortedSet<Int> set5;
	SortedSet<Int> set6;
	ASSERT_EQUALS(SortedSet<Int>::iterator(nullptr), (set5 & set6).begin());
	set5.insert(1);
	set5.insert(2);
	set5.insert(3);
	set5.insert(4);
	set6.insert(2);
	set6.insert(4);
	set6.insert(6);
	set6 &= set5;
	ASSERT_EQUALS(true, set6.size()==2 && set6.contains(2)
			&& set6.contains(4));
	set5.remove(2);
	set5.remove(4);
	set6 &= set5;
	ASSERT_EQUALS(SortedSet<Int>::iterator(nullptr), set6.begin());

	// Checking the ^ operator:
	set6 = set5;
	set6 ^= set5;
	ASSERT_EQUALS(SortedSet<Int>::iterator(nullptr), set6.begin());
	set6.insert(2);
	set6.insert(4);
	set6 ^= set5;
	ASSERT_EQUALS(4, set6.size());
	set6 ^= set5;
	ASSERT_EQUALS(2, set6.size());
	SortedSet<Int> set7; // Check this operator when one of the sets is empty.
	set7 ^= set6;
	ASSERT_EQUALS(true, set7 == set6);

	return true;
}

void runTests(){
	RUN_TEST(testConstruct);
	RUN_TEST(testInsert);
	RUN_TEST(testAssignment);
	RUN_TEST(testFindContain);
	RUN_TEST(testRemove);
	RUN_TEST(testSize);
	RUN_TEST(testOpGroups);
}

int main(){
	runTests();
	return 0;
}
