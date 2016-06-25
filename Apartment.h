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

    /*
     * Apartment's constructor.
     *
     * @param:
     * 	squares - an array that represents the structure of the apartment-
     * 		where there's a wall and where it's empty. cannot be NULL.
     * 	length - the length of the created apartment. Has to be positive.
     * 	width - the width of the created apartment. Has to be positive.
     * 	price - the price of the new apartment. Has to be not negative.
     *
     * @return:
     * 	Exception of type IllegalArgException if one of the parameters given
     * 		is not legal according to the paragraph param.
     * 	Constructs a new object of type Apartment otherwise.
     */
    Apartment(SquareType** squares, int length, int width, int price);

    /*
     * Apartment's copy constructor.
     *
     * @param:
     * 	original - a reference to the apartment that needs to be copied.
     *
     * @return:
     * 	Constructs a new object of type Apartment.
     */
    Apartment(const Apartment& original);

    /*
     * Assignment operator.
     * 		Assign a existing apartment with an another existing apartment.
     *
     * @param:
     * 	original - a reference to the apartment that is used to assign from.
     *
     * @return:
     * 	Reference to the current apartment(this) if the apartment in the paramter
     * 		original is the same.
     * 	Assigns the new values to the current apartment(this) otherwise.
     */
    Apartment& operator=(const Apartment& original);

    /*
     * Apartment's destructor.
     * Frees each row in the apartment(since it's SquareType*).
     * Then frees the squares array itself(since it's SquareType**).
     */
    ~Apartment();

    /*
     * getTotalArea.
     *
     * Calculates and returns the area of the apartment(area of empty squares).
     */
    int getTotalArea() const;

    /*
     * getPrice.
     *
     * Returns the price of the apartment.
     */
    int getPrice() const;

    /*
     * getLength.
     *
     * Returns the length of the apartment.
     */
    int getLength() const;

    /*
     * getWidth.
     *
     * Returns the width of the apartment.
     */
    int getWidth() const;

    /*
     * += operator.
     * Adds an apartment to an existing apartment.
     * If the width of the two apartments is the same then it adds the second
     * apartment down from the first(this) apartment(the new length of the
     * apartment will increase).
     * Then, if the two apartments are of the same length it will add the
     * second apartment to the right of the current(this) apartment.
     * Then, if current apartment's width is bigger than the second apartment's
     * width it will add the second apartment to the first down from the first
     * apartment. Then it will fill the missing cells with walls(so the new
     * apartment will be a rectangle and not an unknown shape).
     * Otherwise, it will add the first apartment down from the second
     * apartment. just like in the previous case, it will fill the empty cells
     * in the first apartment with walls.
     *
     * @param:
     * 	apartment - the apartment that needs to be added to the current
     * 		apartment(this).
     *
     * 	Returns a reference to the new apartment.
     */
    Apartment& operator+=(const Apartment apartment);

    /*
     * () operator.
     * Returns the type of square in a certain location of the array.
     *
     * @param:
     * 	i - row number of selected square.
     * 	j - column number of selected square.
     *
     * @return:
     * WALL or EMPTY depends on the type of the square.
     */
    SquareType operator()(const int i, const int j);

    SquareType operator()(const int i, const int j)const;

    /*
     * < operator.
     * Checks if the first apartment is smaller than the second apartment
     * according to the conditions given in the assignment file.
     *
     * @param:
     * 	apartment1 - a reference to the first apartment.
     * 	apartment2 - a reference to the second apartment.
     *
     * @return:
     * TRUE if the first apartment is smaller than the first.
     * FALSE otherwise.
     */
    friend bool operator<(const Apartment& apartment1,
    		const Apartment& apartment2);

    /*
     * + operator.
     * uses the operator += .
     * Adds the apartment2 to apartment1.
     *
     * @param:
     * 	apartment1 - a reference to the first apartment.
     * 	apartment2 - a reference to the second apartment.
     *
     * @return:
     * Returns the new apartment that consists of the two apartments.
     */
    friend Apartment operator+(const Apartment& apartment1,
    		const Apartment& apartment2);

private:
	int price, width, length;
	SquareType** squares;
};

/*****************************
 * External operator function
 ****************************/

#endif //MTM4_APARTMENT_H
