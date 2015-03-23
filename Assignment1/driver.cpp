/***************************************************************************
Jonathon Cole Marlar
CS 355
Assignment #1
Description: Fraction class -- manipulate fractions such as:
- Basic addition, subtraction, multiplication, & division
- I/O functions for fractions for printing on screen or input from user
****************************************************************************/

#include "Fraction.h"
#include <iostream>
using namespace std;

int main( int argc, char * argv[] ) {
	Fraction frac1;
	Fraction frac2(5);
	Fraction frac3(4,5);

	// Output testing
	cout << frac1 << endl << frac2 << endl << frac3 << endl << endl;

	// Addition
	cout << frac1 << " plus " << frac2 << " equals " << frac1 + frac2 << endl;
	cout << frac2 << " plus " << frac3 << " equals " << frac2 + frac3 << endl;

	// Subtraction
	cout << frac2 << " minus " << frac1 << " equals " << frac2 - frac1 << endl;
	cout << frac2 << " minus " << frac3 << " equals " << frac2 - frac3 << endl;

	// Multiplication
	cout << frac2 << " times " << frac3 << " equals " << frac2 * frac3 << endl;

	// Division
	cout << frac2 << " divided by " << frac3 << " equals " << frac2 / frac3 << endl;

	// Input
	Fraction frac4;
	cout << "Enter a fraction, please: ";
	cin >> frac4;
	cout << "The fraction you just entered is: " << frac4 << endl;

	system("PAUSE"); // remove/comment if running on OS's other than Windows
	return 0;
}