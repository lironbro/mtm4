#ifndef ITERATOR_H_
#define ITERATOR_H_


#include "Node.h"


template <class T>

class iterator{


private:

	Node<T>* node;


public:

	iterator(const T data, const Node<T>* next = NULL){
		this->node = new Node<T>(data, next);
	}

	iterator(const T* data = NULL, const Node<T>* next = NULL){
		this->node = new Node<T>(*data, next);
	}


	iterator(const Node<T> node){
		this->node = new Node<T>(node);
	}

	iterator(const Node<T>* node){
		this->node = new Node<T>(*node);
	}


	iterator(const iterator<T>& original){
		// this copy constructor only copies the object in original.node
		this->node = new Node<T>(*(original.node));
	}


	~iterator(){
		delete node;
	}


	iterator& operator=(const Node<T> node){
		if(this->node == node)
			return *this;
		this->node = Node<T>(*node);
		return *this;
	}


	iterator& operator=(const iterator<T>& original){
		if(this == &original)
			return *this;
		this->node = Node<T>(*original);		// <<<<<<< might need to place & to make it address
		return *this;
	}


	Node<T> operator++(){			// iterator++
		Node<T> value = *(this->node);
		*(this->node)++;
		return value;
	}


	Node<T>& operator++(int){		// ++iterator
		(*(this->node))++;			// <<<<< needs checking
		return *(this->node);
	}


	T operator*(){		// derefrencing an iterator will give you the T object
		return *(*node);
	}


	bool operator==(const iterator iterator){
		return this->node==iterator.node;
	}


	bool operator!=(const iterator iterator){
		return this->node!=iterator.node;
	}

	Node<T>* getNext(){
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



#endif /* ITERATOR_H_ */
