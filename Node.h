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

	explicit Node(const T data, const Node* next = NULL):
	data(data), next(next)
	{
	}


	Node(const Node<T>& node) : data(node.data), next(node.next){
	}


	Node& operator=(const Node original){
		if(this == &original)
			return *this;
		this->data = T(original.data);			// <<<<<<<< might be wrong
		this->next = original.next;
		return *this;
	}


	~Node(){
		//delete data;		// if template is a simple object then this isn't necessary
	}						// if it's not, then it won't get deleted


	void deleteNodes(){
		if(this->next != NULL)
			*(this->next).deleteNodes();
		delete data;
		delete this;
	}


	Node operator++(){				// Node++
		Node value = *this;
		this = this->next;
		return value;
	}


	Node& operator++(int){		// ++Node
		*this = *(this->next);
		return *this;			// <<<<<< check return values
	}


	T operator*() const{			// derefrencing a Node will give you the T object
		return this->data;
	}


	bool operator==(const Node node){
		return this->data==node.data;
	}


	bool operator!=(const Node node){
		return this->data!=node.data;
	}


	Node* getNext() const{
		return this->next;
	}


	void setNext(Node* next){
		this->next = next;
	}


	void setData(T* data){		// recieves a POINTER to the object
		this->data = data;
	}


};



#endif /* NODE_H_ */
