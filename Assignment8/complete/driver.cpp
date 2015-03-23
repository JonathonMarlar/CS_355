/***************************************************************************
Jonathon Cole Marlar
CS 355
Assignment #8 - Hash Table
****************************************************************************/
#include "hash.h"
#include "hash.cpp"

void printMenu();

int main () {
	Hash<int> dalist;
	int data;
	char choice = 'h';

	while ( choice != 'q' && choice != 'Q') {
		switch ( choice ) {
			case 'h':
			case 'H':
				printMenu();
				break;
			case '+':
				cin >> data;
				dalist.Insert( data );
				break;
			case '-':
				cin >> data;
				dalist.Remove( data );
				break;
			case 'a':
			case 'A':
				{
				Hash<int> testlist = dalist;
				testlist.Insert( 1000 );
				cout << "The new list's added contents: " << endl;
				testlist.ShowContents();
				cout << "The old list (unchanged): " << endl;
				dalist.ShowContents();
				break;
				}
				//break;
			case 'c':
			case 'C':
				{
				Hash<int> testlist2( dalist );
				testlist2.Insert(9001);
				cout << "New list's added contents: " << endl;
				testlist2.ShowContents();
				cout << "The old list (unchanged): " << endl;
				dalist.ShowContents();
				break;
				}
			case 'f':
			case 'F':
				dalist.ShowFill();
				break;
			case 't':
			case 'T':
				dalist.ShowContents();
				break;
			case 's':
			case 'S':
				cin >> data;
				dalist.Search( data );
				break;
			case 'n':
			case 'N':
				cin >> data;
				int slot = dalist.NewSlot( data, 10 );
				cout << "The data " << data << " will be put in slot " << slot << endl;
				break;
			default:
				cout << "INVALID OPTION. Please try again." << endl;
		}
		cout << "--> ";
		cin >> choice;
	}

//	system("PAUSE");
	return 0;
}

void printMenu() {
	cout << "+# ... Add a number to the hash table" << endl;
	cout << "-# ... Remove a number from the hash table" << endl;
	cout << "A  ... Test assignment operator" << endl;
	cout << "C  ... Test copy constructor" << endl;
	cout << "F  ... Show all the contents of the hash table" << endl;
	cout << "T  ... Show taken spots in the hash table" << endl;
	cout << "S# ... Search for an item in a hash table" << endl;
	cout << "N# ... Find out which slot the item will go in the table" << endl;
	cout << "H  ... Show the HELP MENU again" << endl;
	cout << "Q  ... Quit the program" << endl;
	cout << endl;
	// cout << "--> ";
}
