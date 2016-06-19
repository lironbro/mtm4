#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H
#include <iostream>

#include <exception>

//enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

class Apartment{


public:


    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

    Apartment(SquareType** squares, int length, int width, int price);

    Apartment(const Apartment& original);

    Apartment& operator=(const Apartment original);

    ~Apartment();

    int getTotalArea() const;

    int getPrice() const;

    int getLength() const;

    int getWidth() const;

    Apartment& operator+=(const Apartment apartment);

    SquareType operator()(const int i, const int j);

    SquareType operator()(const int i, const int j)const;

    friend bool operator<(const Apartment& apartment1,
    		const Apartment& apartment2);

    friend Apartment operator+(const Apartment apartment1,
    		const Apartment apartment2);

private:
	int price, width, length;
	SquareType** squares;
};

/*****************************
 * External operator function
 ****************************/

#endif //MTM4_APARTMENT_H
