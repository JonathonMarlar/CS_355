/****************************************
Cole Marlar & Andrew Hamilton
Assignment 11
*****************************************/
#include <iostream>
#include "sorts.h"
using namespace std;

int main( int argc, char* argv[] ) {
	int mylist[100];

	ifstream import ("hundred.txt");

	for (int i = 0; i < 100 && import.good(); i++) {
		import >> mylist[i];
	}

	mainMenu(mylist, 100);

	system("PAUSE"); // remove on UNIX
	return 0;
}