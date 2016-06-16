#include <cstdlib>
#include "Apartment.h"
#include "MtmTst.h"

static void deleteSquares(SquareType** squares, int length){
	for(int i=0; i<length; i++){
			delete squares[i];
		}
	delete squares;
}

bool apartmentTestExample() {
    const int length = 3;
    const int width = 4;
    const int price = 1;
    SquareType** squares = new SquareType*[length];
    for (int i = 0; i < length; ++i) {
        squares[i] = new SquareType[width];
        for (int j = 0; j < width; ++j) {
                squares[i][j] = EMPTY;
        }
    }
    ASSERT_NO_THROW(Apartment(squares, length, width, price));
    const Apartment apt(squares, length, width, price);
    ASSERT_EQUALS(length, apt.getLength());
    Apartment apt2(apt);
    ASSERT_NO_THROW(apt2 += apt);
    //ASSERT_EQUALS(true, apt.operator<(const apt2)); //IN ORIGINAL VERSION IT IS 'apt < apt2'.
    deleteSquares(squares, length);
    return true;
}

bool apartmentTest() {
    RUN_TEST(apartmentTestExample);
    return true;
}

int main(){
	bool FINAL = apartmentTest();
	return 0;
}
