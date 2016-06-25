/*	NOTES:
 * 	not sure which compiler I should be using
 * 	if you haven't noticed, there're a lot of errors because the header file
 * 	isn't recognized for some weird reason
 * 	also, some derefrencing of fields happens with "." while others, mostly on
 * 	"this" happens with "->", which is strange
 * 	a lot of changes need to go into the header file
 */




//
#include "Apartment.h"


//		<Static functions>

static void deleteSquares(Apartment::SquareType**& squares, const int length){
	for(int i=0; i<length; i++){
		delete[] squares[i];
	}
	delete[] squares;
}

static Apartment::SquareType** copySquares(Apartment::SquareType** original,
		int length, int width){
	Apartment::SquareType** squares = new Apartment::SquareType*[length];
	for(int i=0; i<length; i++){
		squares[i] = new Apartment::SquareType[width];
		for(int j=0; j<width; j++){
			squares[i][j] = original[i][j];
		}
	}
	return squares;
}


static Apartment::SquareType** addSquaresDown(Apartment::SquareType** squares1,
		Apartment::SquareType** squares2, const int length1,
		const int length2, const int width){
	Apartment::SquareType** squares = new Apartment::SquareType*
			[length1+length2];
	for(int i=0; i< length1; i++){
		squares[i] = new Apartment::SquareType[width];
		for(int j=0; j< width; j++){
			squares[i][j] = squares1[i][j];
		}
	}
	for(int i=length1; i<length1+length2; i++){
		squares[i] = new Apartment::SquareType[width];
		for(int j=0; j<width; j++){
			squares[i][j] = squares2[i-length1][j];
		}
	}
	return squares;
}

static Apartment::SquareType** addSquaresRight(Apartment::SquareType** squares1,
		Apartment::SquareType** squares2, const int length,
		const int width1, const int width2){
	Apartment::SquareType** squares = new Apartment::SquareType*[length];
	for(int i=0; i<length; i++){
		squares[i] = new Apartment::SquareType[width1+width2];
		for(int j=0; j<width1; j++){
			squares[i][j] = squares1[i][j];
		}
		for(int j=width1; j<width1+width2; j++){
			squares[i][j] = squares2[i][j-width1];
		}
	}
	return squares;
}


static Apartment::SquareType** fillSquares(Apartment::SquareType** squares,
		int length, const int width, const int delta){
	Apartment::SquareType** bigger = new Apartment::SquareType*[length];
	for(int i=0; i<length; i++){
		bigger[i] = new Apartment::SquareType[width+delta];
		for(int j=0; j<width; j++){
			bigger[i][j] = squares[i][j];
		}
		for(int j=0; j<delta; j++){
			bigger[i][width+j] = Apartment::WALL;
		}
	}
	return bigger;
}





//		</Static functions>






Apartment::Apartment(SquareType** squares, int length, int width, int price){
	if(length <=0 || width <= 0 || price < 0 || squares == NULL ||
			squares == NULL){
		throw IllegalArgException();
	}
	this->length = length;
	this->width = width;
	this->price = price;
	this->squares = copySquares(squares, length, width);
}


Apartment::Apartment(const Apartment& original){
	// the nicer way to do this would be using the previous constructor,
	// but it gave me a warning so I decided against it :(
	this->length = original.length;
	this->width = original.width;
	this->price = original.price;
	this->squares = copySquares(original.squares, this->length, this->width);
}


Apartment& Apartment::operator=(const Apartment& original){
	if(this == &original){
		return *this;
	}
	deleteSquares(this->squares, this->length);
	this->squares = copySquares(original.squares, original.length,
			original.width);
	this->length = original.length;
	this->width = original.width;
	this->price = original.price;
	return *this;	// <<<< might be a mistake
}


Apartment::~Apartment(){
	for(int i=0; i<this->length; i++){
		delete[] this->squares[i];
	}
	delete[] this->squares;
}


int Apartment::getTotalArea() const{
	int area = 0;
	for(int i=0; i<this->length; i++){
	for(int j=0; j<this->width; j++){
		if(this->squares[i][j] == EMPTY)
			area++;
		}
	}
	return area;
}


int Apartment::getPrice() const{
	return this->price;
}


int Apartment::getLength() const{
	return this->length;
}


int Apartment::getWidth() const{
	return this->width;
}

Apartment& Apartment::operator+=(const Apartment apartment){
	this->price += apartment.price;
	if(this->width == apartment.width){
		SquareType** squares = addSquaresDown(this->squares,
			apartment.squares, this->length, apartment.length,
			this->width);
		deleteSquares(this->squares, this->length);
		this->squares = squares;
		this->length+=apartment.length;
		return *this;
	}
	if(this->length == apartment.length){
		SquareType** squares = addSquaresRight(this->squares,
				apartment.squares, this->length, this->width,
				apartment.width);
		deleteSquares(this->squares, this->length);
		this->squares = squares;
		this->width+=apartment.width;
		return *this;
	}
	if(this->width > apartment.width){
		SquareType** squares = fillSquares(apartment.squares,
			apartment.length, apartment.width,
			this->width - apartment.width);
		SquareType** sum = addSquaresDown(this->squares, squares, this->length,
				apartment.length, this->width);
		deleteSquares(squares, apartment.length);
		deleteSquares(this->squares, this->length);
		this->squares = sum;
		this->length+=apartment.length;
		return *this;
	}
	SquareType** squares = fillSquares(this->squares,
			this->length, this->width, apartment.width- this->width);
	this->width=apartment.width;
	SquareType** sum = addSquaresDown(squares, apartment.squares, this->length,
			apartment.length, this->width);
	deleteSquares(squares, this->length);
	deleteSquares(this->squares, this->length);
	this->squares = sum;
	this->length+=apartment.length;
	return *this;
}


Apartment::SquareType Apartment::operator()(const int i, const int j){
	if(i < 0 || j < 0 || i >= this->length || j >= this->width){
		throw OutOfApartmentBoundsException();
	}
	return this->squares[i][j];
}


Apartment::SquareType Apartment::operator()(const int i, const int j)const{
	if(i < 0 || j < 0 || i >= this->length || j >= this->width){
		throw OutOfApartmentBoundsException();
	}
	return this->squares[i][j];
}


bool operator<(const Apartment& apartment1,
		const Apartment& apartment2){
	double ratio1 = (double(apartment1.price))/
			(double(apartment1.getTotalArea())),
			ratio2 = (double(apartment2.price))/
			(double(apartment2.getTotalArea()));
	if(ratio1 < ratio2)
		return true;
	if(ratio1 > ratio2)
		return false;
	if(apartment1.price < apartment2.price)
		return true;
	return false;

}


 Apartment operator+(const Apartment& apartment1,
			const Apartment& apartment2){
	Apartment copy = Apartment(apartment1);
	copy+=apartment2;
	return copy;
}
