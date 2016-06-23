#ifndef MTM4_SORTEDSET_H
#define MTM4_SORTEDSET_H

#include <functional>
#include <iostream>

template <class T, class Compare = std::less<T> >


class SortedSet {


public:
	/////////////////// <Node> ///////////////////

	class Node{

	private:
		const T& data;
		Node* next;

	public:

		explicit Node(const T& data, Node* next = NULL):
		data(data), next(next)
		{
		}


		Node(const Node& node):
			data(node.data), next(node.next){
		}


		const T& operator*() const{	// dereferencing a Node will give you the T object
			return this->data;
		}


		bool operator==(const Node& node) const{		// probably has to be external
			return this->data==node.data;
		}


		bool operator!=(const Node& node) const{		// probably has to be external
			return this->data!=node.data;
		}


		Node* getNext() const{
			return this->next;
		}


		void setNext(Node* next){
			this->next = next;
		}


		void setData(const T& data){
			this->data = data;
		}


	};
	/////////////////// </NODE> ///////////////////
	void deleteNodes(const Node* nodeToDel){
		if(nodeToDel->getNext() == NULL){
			delete nodeToDel;
			return;
		}
		deleteNodes(nodeToDel->getNext());
		delete nodeToDel;
	}




	/////////////////// <ITERATOR> ///////////////////


	class iterator{

	public:


		explicit iterator(Node* node): node(node){
		}


		iterator(const iterator& original): node(original.node){
		}


		iterator& operator=(const Node* node){
			if(this->node == node)
				return *this;
			this->node = node;
			return *this;
		}


		iterator& operator=(const iterator& original){
			if(this->node == original.node)
				return *this;
			this->node = original.node;
			return *this;
		}


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


		Node* getNext() const{
			return node->getNext();
		}


		void setNext(Node* node){
			this->node->setNext(node);
		}


		Node* getNode(){			// gives you the address of the node node
			return this->node;
		}


		void setNode(Node* node){
			this->node = node;
		}


	private:
		Node* node;
	};


	/////////////////// </ITERATOR> ///////////////////


	/////////////////// <SORTED SET> ///////////////////



	SortedSet(){		// very impressive constructor, creates an empty set
		this->first = NULL;
	}


	SortedSet(const SortedSet<T>& set){
		this->first = NULL;
		// VVVVVVVVVVVVVVVVVVVVVV begin()????
		iterator current(set.begin());
		for(; current.getNode() != NULL; current++){
			this->insert(*current);
		}
	}


	SortedSet<T>& operator=(const SortedSet<T>& set){
		if(this == &set)
			return *this;
		iterator current;
		for(current = set.begin(); current.getNode() != NULL; current++){
			this->insert(*current);
		}
		return *this;
	}


	~SortedSet(){
		if(this->first!=NULL){
			SortedSet<T, Compare>::deleteNodes(this->first);
		}
	}


	iterator begin()const{		// returns the iterator to the first node
		return iterator(this->first);
	}


	iterator end()const{	// returns the pointer to the last node
		iterator current = this->begin();
		if(current.getNode() == NULL){
			return current;
		}
		for(; current.getNext() != NULL; current++){
		}
		return current;
	}


	iterator find(const T& data)const{
		iterator current =  this->begin();
		Compare lessThan = Compare();
		for(; current.getNode() != NULL; current++){
			if(!lessThan(*current, data) && !lessThan(data, *current)){
				return current;
			}
		}
		return current;		// current's node will be NULL
	}


	bool insert(const T& data){
		if(this->contains(data))
			return false;
		Compare lessThan = Compare();
		iterator current = this->begin();
		if(current.getNode() == NULL){
			Node* pointer = new Node(data);
			current.setNode(pointer);
			this->first = pointer;
			return true;
		}
		if(lessThan(data, *(current))){
			Node* pointer = new Node(data, current.getNode());
			this->first = pointer;
			return true;
		}
		for(; current.getNext() != end().getNode(); current++){
			if(lessThan(*(current), data) &&
					lessThan(data, *(iterator(current.getNext())))){
				Node* pointer = new Node(data,current.getNext());
				current.setNext(pointer);
				return true;
			}
		}
		// An if here is may not be needed.
		if(lessThan(*(current), data)){//the last node in the set
			Node* pointer = new Node(data);
			current.setNext(pointer);
		}
		return true;
	}


	bool remove(const T& data){
		if(!(this->contains(data)))
			return false;
		iterator current = iterator(begin());	// check if data is in the first node
		Compare lessThan = Compare();
		if(lessThan(*current, data) && lessThan(data, *current)){
			Node* first = this->first;
			(this->first)++;		// update first
			delete first;
			return true;
		}

		for(current = begin(); current.getNext() != NULL; current++){
			if(!lessThan(*iterator(current.getNext()), data) &&
					!lessThan(data, *iterator((current.getNext())))){
				Node* node = current.getNext();
				current.setNext(node->getNext());
				// (*current.getNext()).getNext()
				delete node;
				return true;
			}
		}
		return true;
	}


	int size()const{
		int size = 0;
		iterator current = begin();
		for(; current.getNode() != NULL; current++){
			size++;
		}
		return size;
	}


	bool contains(const T& data)const{
		// find returns an iterator, which will contain NULL if and only if
		// the given data is NOT stored in one of the nodes in the set
		if(this->first==NULL){
			return false;
		}
		iterator result = this->find(data);
		bool value = result.getNode() != NULL;
		//delete &result; 		// <<<<<<<< might be wrong
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
		for(; current.getNode() != NULL; current++){
			if(!(set.contains(*current)))
				result.insert(*current);
		}
		return result;
	}
	/////////////////// </SORTED SET> ///////////////////

private:

	Node* first;


};

template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator|(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	SortedSet<T, Compare> result = SortedSet<T, Compare>();
	for(typename SortedSet<T, Compare>::iterator current = set1.begin();
			current.getNode() != NULL; current++){
		result.insert(*current);
	}
	for(auto current = set2.begin(); current.getNode() != NULL; current++){
		result.insert(*current);
	}
	return result;
}




template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator&(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	SortedSet<T, Compare> result;
	for(typename SortedSet<T, Compare>::iterator current = set1.begin();
			current.getNode() != NULL; current++){
		if(set2.contains(*current))
			result.insert(*current);
	}
	return result;
}



template <class T, class Compare = std::less<T> >
SortedSet<T, Compare> operator^(const SortedSet<T, Compare>& set1,
		const SortedSet<T, Compare>& set2){
	return (set1-set2)|(set2-set1);		// (A/B)U(B/A) = A^B
}



#endif //MTM4_SORTEDSET_H
