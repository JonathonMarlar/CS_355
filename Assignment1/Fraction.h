#pragma once

#include <iostream>

class Fraction {
private:
	int num;
	int den;

public:
	Fraction();
	Fraction(int);
	Fraction(int,int);

	const Fraction operator+(const Fraction&);
	const Fraction operator-(const Fraction&);
	friend const Fraction operator*(const Fraction&, const Fraction&);
	friend const Fraction operator/(const Fraction&, const Fraction&);
	friend std::ostream& operator<<(std::ostream& outputStream, const Fraction& frac);
	friend std::istream& operator>>(std::istream& inputStream, Fraction& frac);
};