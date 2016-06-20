/*
 * Node.h
 *
 *  Created on: 14 αιεπι 2016
 *      Author: Liron
 */

#ifndef NODE_H_
#define NODE_H_


#include <iostream>


template <class T>

class Node{

private:
	T data;
	Node* next;

public:

	explicit Node(const T& data, Node* next = nullptr):
	data(data), next(next)
	{
	}


	Node(const Node& node):
	data(node.data), next(node.next){
	}

	void destroyNodes(){

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


	void setData(T data){
		this->data = data;
	}


};



#endif /* NODE_H_ */
