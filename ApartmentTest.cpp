#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"


static void deleteSquares(Apartment::SquareType** squares, int length){
	for(int i = 0; i < length; ++i){
		delete[] squares[i];
	}
	delete[] squares;
}


bool apartmentTestExample() {
    const int length = 5;
    const int width = 4;
    const int price = 10000;
    Apartment::SquareType** squares = new Apartment::SquareType*[length];
    for (int i = 0; i < length; ++i) {
        squares[i] = new Apartment::SquareType[width];
        for (int j = 0; j < width; ++j) {
        	if(j == 0 || i == 0 || j == width-1 || i == length-1)
        		squares[i][j] = Apartment::EMPTY;
        	else
        		squares[i][j] = Apartment::WALL;
        }
    }
    ASSERT_NO_THROW(Apartment(squares, length, width, price));
    const Apartment apt(squares, length, width, price);
    ASSERT_EQUALS(length, apt.getLength());
    Apartment apt2(apt);
    ASSERT_NO_THROW(apt2+=apt);
    ASSERT_EQUALS(true, apt < apt2);
    deleteSquares(squares, length);
    return true;
}

static Apartment::SquareType** squaresCreateForTest(const int length, const int width){
	Apartment::SquareType** squares = new Apartment::SquareType*[length];
	for (int i = 0; i < length; ++i){
		squares[i] = new Apartment::SquareType[width];
		for (int j = 0; j < width; ++j){
			if(j%2 == 0){
				squares[i][j] = Apartment::WALL;
			}
			else
				squares[i][j] = Apartment::EMPTY;
		}
	}
	return squares;
}

// Every different apartment(not a copy) won't be of different width - only
// the price and length will change in this test.
bool apartmentTestFirst(){
	const int length = 4;
	const int width = 4;
	const int price = 500000;
	Apartment::SquareType** squares = squaresCreateForTest(length, width);
	ASSERT_NO_THROW(Apartment(squares, length, width, price));
	/*
	 * apt:
	 * W E W E
	 * W E W E
	 * W E W E
	 * W E W E
	 */
	const Apartment apt(squares, length, width, price);
	Apartment copy(apt); // Checking the copy constructor.
	ASSERT_EQUALS(width, apt.getWidth());
	ASSERT_EQUALS(length, apt.getLength());
	ASSERT_EQUALS(price, apt.getPrice());
	ASSERT_EQUALS(8, apt.getTotalArea());
	ASSERT_EQUALS(Apartment::WALL, apt(2,2)); // Checking a random square.
	// NEXT LINE throws std::exception instead of OutOfApartmentBoundsException.
	ASSERT_THROW(Apartment::OutOfApartmentBoundsException, apt(-1,1));

	copy += apt; // Now apt should be added down from copy. checking operator+=.
	ASSERT_EQUALS(2*length, copy.getLength());
	ASSERT_EQUALS(width, copy.getWidth());
	ASSERT_EQUALS(Apartment::WALL, copy(4,0));
	ASSERT_EQUALS(false, copy < apt); // Copy's price is doubled with += action.
	copy = apt; // Now copy will be the original apt. checking operator=.
	ASSERT_EQUALS(4, copy.getLength());

	ASSERT_EQUALS(true, Apartment(squares, length, width, price/2) < apt);
	Apartment::SquareType** squares2 = squaresCreateForTest(length/2, width);
	Apartment apt2(squares2, length/2, width, price/2);
	ASSERT_EQUALS(true, apt2 < apt);
	Apartment apt3(squares2, length/2, width, price);
	ASSERT_EQUALS(false, apt3 < apt);

	apt3 = apt + apt2;
	ASSERT_EQUALS(6, apt3.getLength());
	ASSERT_EQUALS((int)price+price/2, apt3.getPrice());
	ASSERT_EQUALS(12, apt3.getTotalArea());

	deleteSquares(squares, length);
	deleteSquares(squares2, length/2);
	return true;
}

// Here, also the width will change.
bool apartmentTestSecond(){
	const int length = 6;
	const int width = 4;
	const int price = 333000;
	Apartment::SquareType** squares = squaresCreateForTest(length, width);
	Apartment apt(squares, length, width, price);
	// apt will be of length 6 and width 4.
	/*
	 * apt:
	 * W E W E
	 * W E W E
	 * W E W E
	 * W E W E
	 * W E W E
	 * W E W E
	 */
	Apartment::SquareType** squares2 = squaresCreateForTest(length, width/2);
	Apartment apt2 = apt + Apartment(squares2, length, width/2, price);
	ASSERT_EQUALS(2*price, apt2.getPrice());
	// apt2 will be of length 6 and width 6.
	ASSERT_EQUALS(6, apt2.getWidth());
	ASSERT_EQUALS(Apartment::EMPTY, apt2(3, 5));

	deleteSquares(squares2, length);
	squares2 = squaresCreateForTest(length+1, width+2);
	Apartment apt3 = apt + Apartment(squares2, length+1, width+2, price);
	// apt 3 will be of length 13 and width 6
	ASSERT_EQUALS(13, apt3.getLength());
	ASSERT_EQUALS(6, apt3.getWidth());
	ASSERT_EQUALS(2*price, apt3.getPrice());
	for(int i=0; i<apt3.getWidth(); i++){
		ASSERT_EQUALS(Apartment::WALL, apt3(i,4));
		ASSERT_EQUALS(Apartment::WALL, apt3(i,5));
	}

	deleteSquares(squares2, length+1);
	squares2 = squaresCreateForTest(length+1, width);
	Apartment apt4 = apt2 + Apartment(squares2, length+1, width, price);
	// apt4 should be of length 13 and width 6
	ASSERT_EQUALS(13, apt4.getLength());
	ASSERT_EQUALS(6, apt4.getWidth());
	for(int i = 6; i<apt4.getLength(); i++){
		ASSERT_EQUALS(Apartment::WALL, apt4(i,4));
		ASSERT_EQUALS(Apartment::WALL, apt4(i,5));
	}

	deleteSquares(squares, length);
	deleteSquares(squares2, length+1);
	return true;
}

bool apartmentTest() {
    RUN_TEST(apartmentTestExample);
    RUN_TEST(apartmentTestFirst);
    RUN_TEST(apartmentTestSecond);
    return true;
}

