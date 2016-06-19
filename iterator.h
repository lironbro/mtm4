#ifndef ITERATOR_H_
#define ITERATOR_H_


#include "Node.h"


template <class T>

class iterator{


private:

	Node<T>* node;


public:

	explicit iterator(const Node<T>* node): node(node){
	}


	iterator(const iterator<T>& original) = default;


	iterator& operator=(const Node<T>* node){
		if(this->node == node)
			return *this;
		Node<T>* temp = new Node<T>(node);
		delete this->node;
		this->node = temp;
		return *this;
	}


	iterator& operator=(const iterator<T>& original) = default;


	iterator operator++(){			// iterator++ <<<<<<<<ADDIR
		this->node = (this->node).getNext();
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



#endif /* ITERATOR_H_ */
