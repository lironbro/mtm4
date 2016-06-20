#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H

#include <functional>
#include "Node.h"

template <class T, class Compare = std::less<T> >


class SortedSet {

private:

	Node<T>* first;

public:
	/////////////////// ITERATOR ///////////////////
	class iterator{

	private:
		Node<T>* node;

	public:
		explicit iterator(Node<T>* node): node(node){
		}


		iterator(const iterator& original) = default;


		iterator& operator=(const Node<T>* node){
			if(this->node == node)
				return *this;
			Node<T>* temp = new Node<T>(node);
			delete this->node;
			this->node = temp;
			return *this;
		}


		iterator& operator=(const iterator& original) = default;


		iterator operator++(){			// iterator++ <<<<<<<<ADDIR
			this->node = (this->node)->getNext();
			return *this;
		}


		iterator operator++(int){		// ++iterator
			iterator temp(*this);
			operator++();
			return temp;
		}


		const T& operator*() const{	// returns the T object pointed
			return *(*node);
		}


		// maybe this needs to be external
		bool operator==(const iterator iterator) const{
			return this->node==iterator.node;
		}


		bool operator!=(const iterator iterator) const{
			return this->node!=iterator.node;
		}


		Node<T>* getNext() const{
			return node->getNext();
		}


		void setNext(Node<T>* node){
			node->setNext(node);
		}


		Node<T>* getNode(){			// gives you the address of the node node
			return this->node;
		}


		void setNode(Node<T>* node){
			this->node = node;
		}
	};

	/////////////////// SORTED SET ///////////////////
	SortedSet(){		// very impressive constructor, creates an empty set
		this->first = nullptr;
	}

	SortedSet(const SortedSet<T, Compare>& set){
		this->first = new Node<T>(*(set.begin));		// <<<<<<<<< begin()????
		iterator current = iterator();
		for(current = set.begin; current.getNode() != nullptr; current++){
			this->insert(**(current));
		}
	}

	SortedSet<T>& operator=(const SortedSet<T>& set){
		if(this == &set)
			return *this;
		iterator current = iterator();
		for(current = set.begin(); current.getNode() != nullptr; current++){
			this->insert(*(current));
		}
		return *this;
	}

	iterator begin(){		// returns the iterator to the first node
		return iterator(this->first);
	}


	iterator end(){	// returns the pointer to the last node
		iterator current = this->begin();
		for(; current.getNext() != nullptr; current++){
		}
		return current;
	}


	iterator find(const T data){
		iterator current =  this->begin();
		Compare lessThan = Compare();
		for(; current.getNode() != nullptr; current++){
			if(!lessThan(*current, data) && !lessThan(data, *current)){
				return current;
			}
		}
		return current;		// current's node will be nullptr
	}


	bool insert(T data){
		if(!(this->contains(data)))
			return false;
		Compare lessThan = Compare();
		iterator current = this->begin();
		for(; current.getNext() != nullptr; current++){
			if(lessThan(*(current), data) &&
					lessThan(data, **(current.getNext()))){
				Node<T>* pointer = new Node<T>(data,current.getNext());
				current.setNext(pointer);
				return true;
			}
		}
		if(lessThan(*(current), data))	//the last node in the set
			current.setNext(new Node<T>(data));
		return true;
	}


	bool remove(T data){
		if(!(this->contains(data)))
			return false;
		iterator current = iterator(begin());	// check if data is in the first node
		Compare lessThan = Compare();
		if(lessThan(*current, data) && lessThan(data, *current)){
			Node<T>* first = this->first;
			(this->first)++;		// update first
			delete first;
			return true;
		}
		for(current = begin(); current.getNext() != nullptr; current++){
			if(lessThan(**(current.getNext()), data) &&
					lessThan(data, **(current.getNext()))){
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
		iterator current = begin();
		for(; current.getNode() != nullptr; current++){
			size++;
		}
		return size;
	}


	bool contains(T data){
		// find returns an iterator, which will contain nullptr if and only if
		// the given data is NOT stored in one of the nodes in the set
		iterator result = this->find(data);
		bool value = result.getNode() != nullptr;
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


	SortedSet<T, Compare> operator-(const SortedSet<T, Compare>& set){
		SortedSet<T, Compare> result = SortedSet<T, Compare>();
		iterator current = this->begin();
		for(; current.getNode() != nullptr; current++){
			if(!(set.contains(*current)))
				result.insert(*current);
		}
		return result;
	}


};

template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator|(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	SortedSet<T, Compare> result = new SortedSet<T, Compare>();
	typename SortedSet<T, Compare>::iterator current;
	for(current = set1.begin(); current.getNode() != nullptr; current++){
		result.insert(**current);
	}
	for(current = set2.begin(); current.getNode() != nullptr; current++){
		result.insert(**current);
	}
	return result;
}




template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator&(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	SortedSet<T, Compare> result = new SortedSet<T, Compare>();
	typename SortedSet<T, Compare>::iterator current;
	for(current = set1.begin(); current.getNode() != nullptr; current++){
		if(set2.contains(**current))
			result.insert(**current);
	}
	return result;
}



template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator^(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	return (set1-set2)|(set2-set1);		// (A/B)U(B/A) = A^B
}



#endif //MTM4_SORTEDSET_H
