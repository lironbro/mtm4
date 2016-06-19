#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H

#include <functional>
#include "iterator.h"

template <class T, class Compare = std::less<T> >


class SortedSet {

private:

	Node<T>* first;

public:

	SortedSet(){		// very impressive constructor, creates an empty set
		this->first = NULL;
	}

	SortedSet(const SortedSet<T, Compare>& set){
		this->first = new Node<T>(*(set.begin));		// <<<<<<<<< begin()????
		iterator<T> current = iterator<T>();
		for(current = set.begin; current.getNode() != NULL; current++){
			this->insert(**(current));
		}
	}

	SortedSet<T>& operator=(const SortedSet<T>& set){
		if(this == &set)
			return *this;
		iterator<T> current = iterator<T>();
		for(current = set.begin(); current.getNode() != NULL; current++){
			this->insert(*(current));
		}
		return *this;
	}

	Node<T>* begin(){		// returns the pointer to the first node
		return this->first;
	}


	Node<T>* end(){	// returns the pointer to the last node
		iterator current = iterator();
		for(current = this->begin(); current.getNext() != NULL; current++){
		}
		return current.getNode();
	}


	iterator<T> find(const T data){
		iterator<T>* current = new iterator<T>();
		for(*current = begin(); (*current).getNode() != NULL; (*current)++){
			if(Compare(***current, data) && Compare(data, ***current)){
				return *current;
			}
		}
		return *current;		// current's node will be NULL
	}


	bool insert(T data){
		if(!(this->contains(data)))
			return false;
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNext() != NULL; current++){
			if(Compare(**(current), data) &&
					Compare(data, *(current.getNext()))){
				current.setNext(new Node<T>(data, current.getNext()));
				return true;
			}
		}
		if(Compare(**(current), data))	//the last node in the set
			current.setNext(new Node<T>(data));
		return true;
	}


	bool remove(T data){
		if(!(this->contains(data)))
			return false;
		iterator<T> current = iterator<T>(begin());	// check if data is in the first node
		if(Compare(**(current), data) && Compare(data, *(current))){
			Node<T>* first = this->first;
			(this->first)++;		// update first
			delete first;
			return true;
		}
		for(current = begin(); current.getNext() != NULL; current++){
			if(Compare(**(current.getNext()), data) &&
					Compare(data, **(current.getNext()))){
				Node<T>* node = current.getNext();
				current.setNext((*current.getNext()).getNext());
				delete node;
				return true;
			}
		}
		return true;
	}


	int size(){
		int size = 0;
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNode() != NULL; current++){
			size++;
		}
		return size;
	}


	bool contains(T data){
		// find returns an iterator, which will contain NULL if and only if
		// the given data is NOT stored in one of the nodes in the set
		iterator<T> result = this->find(data);
		bool value = result.getNode() != NULL;
		delete &result; 		// <<<<<<<< might be wrong
		return value;
	}


	/*
	 * okay
	 * so all of these operators need to be symetrical, meaning they need
	 * to be written outside of the class and be friendly
	 * but taking them out of the class causes an error
	 * leaving them inside the class still allows access to this, meaning
	 * they're not outside of the class (duh)
	 * and also there are the errors on .begin() which is really annoying
	 */
	friend SortedSet<T, Compare> operator|(const SortedSet<T, Compare>& set1,
			const SortedSet<T, Compare>& set2){
		SortedSet<T, Compare> result = new SortedSet<T, Compare>();
		iterator<T> current = iterator<T>();
		for(current = set1.begin(); current.getNode() != NULL; current++){
			result.insert(**current);
		}
		for(current = set2.begin(); current.getNode() != NULL; current++){
			result.insert(**current);
		}
		return result;
	}


	friend SortedSet<T, Compare> operator&(const SortedSet<T, Compare>& set1,
			const SortedSet<T, Compare>& set2){
		SortedSet<T, Compare> result = new SortedSet<T, Compare>();
		iterator<T> current = iterator<T>();
		for(current = set1.begin(); current.getNode() != NULL; current++){
			if(set2.contains(**current))
				result.insert(**current);
		}
		return result;
	}


	friend SortedSet<T> operator-(const SortedSet<T, Compare>& set1,
			const SortedSet<T, Compare>& set2){
		SortedSet<T, Compare> result = new SortedSet<T, Compare>();
		iterator<T> current = iterator<T>();
		for(current = set1.begin(); current.getNode() != NULL; current++){
			if(!(set2.contains(**current)))
				result.insert(**current);
		}
		return result;
	}


	friend SortedSet<T> operator^(const SortedSet<T, Compare>& set1,
			const SortedSet<T, Compare>& set2){
		return (set1-set2)|(set2-set1);		// (A/B)U(B/A) = A^B
	}
};




#endif //MTM4_SORTEDSET_H
