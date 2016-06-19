#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"


void deleteSquares(SquareType** squares, int length){
	for(int i=0; i<length; i++){
		delete[] squares[i];
	}
	delete[] squares;
}


bool apartmentTestExample() {
    const int length = 5;
    const int width = 4;
    const int price = 10000;
    SquareType** squares = new SquareType*[length];
    for (int i = 0; i < length; ++i) {
        squares[i] = new SquareType[width];
        for (int j = 0; j < width; ++j) {
        	if(j == 0 || i == 0 || j == width-1 || i == length-1)
        		squares[i][j] = EMPTY;
        	else
        		squares[i][j] = WALL;
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

bool apartmentTest() {
    RUN_TEST(apartmentTestExample);
    return true;
}

