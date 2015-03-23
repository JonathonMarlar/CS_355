/***************************************************************************
Jonathon Cole Marlar
CS 355
Assignment #2
****************************************************************************/
#include "LL.h"
#include <iostream>
using namespace std;

int main ( int argc, char * argv[] ) {
	LL alinklist;

	alinklist.Insert(10);
	alinklist.Insert(20);
	alinklist.Insert(30);
	alinklist.Insert(40);

	cout << alinklist << endl;

	system("PAUSE");
	return 0;
}