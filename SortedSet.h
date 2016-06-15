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
		for(current = this->begin(); current.getNode() != NULL; current++){
			this->insert(*(current));
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
		iterator<T> current = iterator<T>();
		for(current = this->begin(); current.getNext() != NULL; current++){
		}
		return current.getNode();
	}


	iterator<T>* find(const T& data){
		iterator<T>* current = new iterator<T>();
		for(*current = begin(); (*current).getNode() != NULL; (*current)++){
			if(Compare(*(current), data) && Compare(data, **(current))){
				return current;
			}
		}
		delete current;
		return NULL;		// NULL indicates the end of the set
	}


	bool insert(T data){
		if(!(this->contains(data)))
			return false;
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNext() != NULL; current++){
			if(Compare(*(current), data) &&
					Compare(data, *(current.getNext()))){
				current.setNext(new Node<T>(data, current.getNext()));
				return true;
			}
		}
		if(Compare(*(current), data))	//the last node in the set
			current.setNext(new Node<T>(data));
		return true;
	}


	bool remove(T data){
		if(!(this->contains(data)))
			return false;
		iterator<T> current = iterator<T>(begin());	// check if data is in the first node
		if(Compare(*(current), data) && Compare(data, *(current))){
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
		return this->find(data) != NULL;
	}


	SortedSet<T> operator&(const SortedSet<T>& set){
		SortedSet<T> result = new SortedSet<T>();
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNode() != NULL; current++){
			if(set.contains(*current))
				result.insert(*current);
		}
		return result;
	}


	SortedSet<T> operator|(const SortedSet<T>& set){
		SortedSet<T> result = new SortedSet<T>();
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNode() != NULL; current++){
			result.insert(*current);
		}
		for(current = set.begin(); current.getNode() != NULL; current++){
			result.insert(*current);
		}
		return result;
	}


	SortedSet<T> operator-(const SortedSet<T>& set){
		SortedSet<T> result = new SortedSet<T>();
		iterator<T> current = iterator<T>();
		for(current = begin(); current.getNode() != NULL; current++){
			if(!(set.contains(*current)))
				result.insert(*current);
		}
		return result;
	}


	SortedSet<T> operator^(const SortedSet<T>& set){
		return ((*this)-set)|(set-(*this));		// (A/B)U(B/A) = A^B
	}
};


#endif //MTM4_SORTEDSET_H
