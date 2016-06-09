#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H
#include <iostream>

#include <exception>

enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

class Apartment
{
public:

	Apartment (SquareType** squares, int length, int width, int price);

    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    Apartment(SquareType** squares, int length, int width, int price);

    Apartment(const Apartment original);

    Apartment& operator=(const Apartment original);

    ~Apartment();

    int getTotalArea(const Apartment apartment);

    int getPrice(const Apartment apartment);

    int getLength(const Apartment apartment);

    int getWidth(const Apartment apartment);

    Apartment& operator+=(const Apartment apartment);

    SquareType operator()(const int i, const int j);

    SquareType operator()(const int i, const int j)const;

    bool operator<();

    Apartment operator+(Apartment apartment);

private:
	int price, width, length;
	SquareType** squares;
};

/*****************************
 * External operator function
 ****************************/

#endif //MTM4_APARTMENT_H
