/*
 * Apartment.cpp

 *
 *  Created on: 26 במאי 2016
 *      Author: Liron
 */


/*	NOTES:
 * 	not sure which compiler I should be using
 * 	if you haven't noticed, there're a lot of errors because the header file
 * 	isn't recognized for some weird reason
 * 	also, some derefrencing of fields happens with "." while others, mostly on
 * 	"this" happens with "->", which is strange
 * 	a lot of changes need to go into the header file
 */




//
#include "Apartment.h"		// doesn't work for some reason


//		<Static functions>

static SquareType** copySquares(SquareType** original, int length,
		int width){
	SquareType** squares = new SquareType[length][width];
	for(int i=0; i<length; i++){
		for(int j=0; j<width; j++){
			squares[i][j] = original[i][j];
		}
	}
	return squares;
}


static SquareType** addSquaresDown(const SquareType** squares1,
		const SquareType** squares2, const int length1,
		const int length2, const int width){
	SquareType** squares =
			new SquareType[length1+length2]
						   [width];
	for(int i=0; i< length1; i++){
		for(int j=0; j< width; j++){
			squares[i][j] = squares1[i][j];
		}
	}
	for(int i=length1; i<length1+length2; i++){
		for(int j=0; j<width; j++){
			squares[i][j] = squares2[i-length1][j];
		}
	}
	return squares;
}

static SquareType** addSquaresRight(const SquareType** squares1,
		const SquareType** squares2, const int length,
		const int width1, const int width2){
	SquareType** squares =
			new SquareType[length]
						   [width1+width2];
	for(int i=0; i<length; i++){
		for(int j=0; j<width1; j++){
			squares[i][j] = squares1[i][j];
		}
		for(int j=width1; j<width1+width2; j++){
			squares[i][j] = squares2[i][j-width1];
		}
	}
	return squares;
}


static SquareType** fillSquares(const SquareType** squares,const int length,
		const int width, const int delta){
	SquareType** bigger = new SquareType[length][width+delta];
	for(int i=0; i<length; i++){
		for(int j=0; j<width; j++){
			bigger[i][j] = squares[i][j];
		}
		for(int j=0; j<delta; j++){
			bigger[i][width+j] = WALL;
		}
	}
	return bigger;
}
//		</Static functions>

Apartment::Apartment(SquareType** squares, int length, int width, int price){
		if(length <=0 || width <= 0 || price < 0 || squares == NULL){
			throw IllegalArgException();
		}
		this->length = length;
		this->width = width;
		this->price = price;
		this->squares = copySquares(squares, this->squares, length, width);
}


Apartment::Apartment(const Apartment original){
		Apartment(original.squares, original.length,
				original.width, original.price);
}


Apartment& Apartment::operator=(const Apartment original){
	if(original == NULL){
		throw IllegalArgException;
	}
	if(this == &original){
		return *this;
	}
	delete this->squares;
	this->squares = copySquares(original.squares, original.length,
			original.width);
	this->length = original.length;
	this->width = original.width;
	this->price = original.price;
	return &this;	// <<<< might be a mistake
}


Apartment::~Apartment(){
	delete this->squares;
	delete this->length;
	delete this->width;
	delete this->price;
	delete this;
}


int Apartment::getTotalArea(const Apartment apartment){
	int area = 0;
	for(int i=0; i<apartment.length; i++){
	for(int j=0; j<apartment.width; j++){
		if(apartment.squares[i][j] == EMPTY)
			area++;
		}
	}
	return area;
}


int Apartment::getPrice(const Apartment apartment){
	return apartment.price;
}


int Apartment::getLength(const Apartment apartment){
	return apartment.length;
}


int Apartment::getWidth(const Apartment apartment){
	return apartment.width;
}


Apartment& Apartment::operator+=(const Apartment apartment){
	if(this->width == apartment.width){
		SquareType** squares = addSquaresDown(this->squares,
			apartment.squares, this->length, apartment.length,
			this->width);
		delete this->squares;
		this->squares = squares;
		return &this;
	}
	if(this->length == apartment.length){
		SquareType** squares = addSquaresRight(this->squares,
				apartment.squares, this->length, this->width,
				apartment.width);
		delete this->squares;
		this->squares = squares;
		return &this;
	}
	if(this->width > apartment.width){
		SquareType** squares = fillSquares(apartment.squares,
			apartment.length, apartment.width,
			this->width - apartment.width);
		SquareType** sum = addSquaresDown(this->squares, squares);
		delete squares;
		delete this->squares;
		this->squares = sum;
		return &this;
	}
	SquareType** squares = fillSquares(this->squares,
			this->length, this->width, apartment.width- this->width);
	SquareType** sum = addSquaresDown(squares, apartment.squares);
	delete squares;
	delete this->squares;
	this->squares = sum;
	return &this;
}


SquareType Apartment::operator()(const int i, const int j){
	if(i < 0 || j < 0 || i >= this->length || j >= this->width){
		throw OutOfApartmentBoundsException;
	}
	return this->squares[i][j];
}


SquareType Apartment::operator()(const int i, const int j)const{
	if(i < 0 || j < 0 || i >= this->length || j >= this->width){
		throw OutOfApartmentBoundsException;
	}
	return this->squares[i][j];
}


bool operator<(){	// more correct price? inside or outside of class????

}


Apartment Apartment::operator+(Apartment apartment){
	Apartment copy = Apartment(this);
	copy+=apartment;
	return copy;
	}
}



