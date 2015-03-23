#include "Fraction.h"
using namespace std;

Fraction::Fraction() {
	num = 0;
	den = 1;
}

Fraction::Fraction(int nNum) {
	num = nNum;
	den = 1;
}

Fraction::Fraction(int nNum, int nDen) {
	num = nNum;

	// 0 should NEVER be a denominator unless you like melting CPUs
	if ( nDen > 0 || nDen < 0 )	den = nDen;
	else den = 1;
}

/**************************************************************************************
FUNCTION:		operator+(const Fraction&)
PURPOSE:		Adds two fractions
INCOMING:		Constant address of a Fraction object
OUTGOING:		N/A
RETURN:			the sum in the form of Fraction
***************************************************************************************/
const Fraction Fraction::operator+(const Fraction& frac) {
	int sumNum, sumDen;

	// similar denominators means addition happens immediately
	if ( den == frac.den ) {
		sumNum = num + frac.num;
		sumDen = den;
	}
	else {
		// the function automatically converts to similar denominators
		int sNum1, sNum2, newDen;

		newDen = den * frac.den;
		sNum1 = den * frac.num;
		sNum2 = frac.den * num;

		sumNum = sNum1 + sNum2;
		sumDen = newDen;
	}

	Fraction sumFrac(sumNum, sumDen);

	return sumFrac;
}

/**************************************************************************************
FUNCTION:		operator-(const Fraction&)
PURPOSE:		Subtracts two fractions
INCOMING:		Constant address of a Fraction object
OUTGOING:		N/A
RETURN:			the difference in the form of Fraction
***************************************************************************************/
const Fraction Fraction::operator-(const Fraction& frac) {
	int diffNum, diffDen;

	// similar denominators means subtraction happens immediately
	if ( den == frac.den ) {
		diffNum = num - frac.num;
		diffDen = den;
	}
	else {
		// the function automatically converts to similar denominators
		int dNum1, dNum2, newDen;

		newDen = den * frac.den;
		dNum1 = den * frac.num;
		dNum2 = frac.den * num;

		diffNum = dNum2 - dNum1;
		diffDen = newDen;
	}

	Fraction diffFrac(diffNum, diffDen);

	return diffFrac;
}

/**************************************************************************************
FUNCTION:		operator*(const Fraction&, const Fraction&)
PURPOSE:		Multiplies the contents of two Fraction objects
INCOMING:		Constant address of two Fraction objects
OUTGOING:		N/A
RETURN:			the product in the form of Fraction
***************************************************************************************/
const Fraction operator*(const Fraction& frac1, const Fraction& frac2) {
	int prodNum, prodDen;

	prodNum = frac1.num * frac2.num;
	prodDen = frac1.den * frac2.den;

	Fraction prodFrac(prodNum,prodDen);

	return prodFrac;	
}

/**************************************************************************************
FUNCTION:		operator/(const Fraction&, const Fraction&)
PURPOSE:		Divides the contents of two Fraction objects
INCOMING:		Constant address of two Fraction objects
OUTGOING:		N/A
RETURN:			the quotient in the form of Fraction
***************************************************************************************/
const Fraction operator/(const Fraction& frac1, const Fraction& frac2) {
	int divNum, divDen;

	divNum = frac1.num * frac2.den;
	divDen = frac1.den * frac2.num;

	Fraction divFrac(divNum, divDen);

	return divFrac;
}

/**************************************************************************************
FUNCTION:		operator<<(ostream&, const Fraction&)
PURPOSE:		Send contents of a Fraction's address to an ostream
INCOMING:		Address of an ostream, constant address of a fraction object
OUTGOING:		N/A
RETURN:			the output stream
***************************************************************************************/
ostream& operator <<(ostream& outputStream, const Fraction& frac) {
	outputStream << frac.num << "/" << frac.den;

	return outputStream;
}

/**************************************************************************************
FUNCTION:		operator>>(istream&, Fraction&)
PURPOSE:		Send contents of a Fraction's address to an istream
INCOMING:		Address of an istream, address of a fraction object
OUTGOING:		N/A
RETURN:			the input stream
***************************************************************************************/
istream& operator>>(std::istream& inputStream, Fraction& frac) {
	char divisionLine = ' ';

	while ( divisionLine != '/' )
		inputStream >> frac.num >> divisionLine >> frac.den;

	return inputStream;
}