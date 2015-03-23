/***************************************************************************
Jonathon Cole Marlar
CS 355
Assignment #3
****************************************************************************/

#include "LL.h"
#include "LL.cpp"
#include <iostream>
using namespace std;

void PrintMenu();


int main(){
	LL<int> testList;
	LL<int> testAssign;
	int data;

	PrintMenu();
	char choice;
	cin >> choice;

	while(choice != 'q' && choice != 'Q'){
		
		if (choice == '!'){
			LL<int> testCopy(testList);
			cout << "Result:" << "Print New Copy" << endl;
			testCopy.Print(); cout << endl;
			testCopy.Insert(-10000);
			cout << "Result: " << "Print Modified Copy" << endl;
			testCopy.Print(); cout << endl;
			cout << "Result: " << "Print Original Test List" << endl;
			//testList.Print(); cout << endl;
		}
		else{
			switch (choice){
				case 'h':
				case 'H': PrintMenu();
				case '+':
					cin >> data;
					testList.Insert(data);
					break;		
				case '-':
					cin >> data;
					testList.Remove(data);
					break;
				
				case '@':
					cout <<"Result:" <<  testList.AtCursor() << endl;
					break;
				case '<':
					testList.GoToBeginning();
					break;
				case '>':
					testList.GoToEnd();
					break;
				case 'N':
					testList.GoToNext();
					break;
				case 'P':
					testList.GoToPrev();
					break;
				case 'C':
					testList.~LL();
					break;
					testList.ClearList();
				case 'E':
					if (testList.Empty())
						cout <<"Result:" <<  "List Is Empty" << endl;
					else
						cout <<"Result:" <<  "List is Full" << endl;
					break;
				case '#':
					//assign list
					testAssign = testList;
					testAssign.Insert(-100000);
					cout << "Modify New List" << endl;
					testAssign.Print(); cout << endl;
					cout << "Old List should not be affected" << endl;
					testList.Print(); cout << endl;
					testAssign.~LL();
					cout << "Destroy New List" << endl;
					cout << "Old List should not be affected" << endl;
					testList.Print(); cout << endl;
					break;
				case '?':
					cin >> data;
					if (testList.Search(data) == NULL)
						cout << "Result:" << data << "\tnot found" << endl;
					else
						cout << "Result:" << data << "\tfound" << endl;
					break;
				default:
					cout << "INVALID CHOICE, Choose Again" << endl;
			}

		}
		testList.Print(); cout << endl;
		cout << "-->";
		cin >> choice;
	}

	return 0;
}

void PrintMenu(){
	/*Commands borrowed from Lab*/
	cout << "  Command Line Options" << endl;
	cout << "  H\tHelp: Show Comman Line Options" << endl;
	cout << "  +x\tInsert x in order" << endl;
	cout << "  @   : Display the data item marked by the cursor" << endl;
    cout << "  <   : Go to the beginning of the list" << endl;
    cout << "  >   : Go to the end of the list" << endl;
    cout << "  N   : Go to the next data item" << endl;
    cout << "  P   : Go to the prior data item" << endl;
    cout << "  C   : Clear the list" << endl;
    cout << "  E   : Empty list?" << endl;
    cout << "  F   : Full list?" << endl;
    cout << "  !   : Test copy constructor" << endl;
    cout << "  #   : Test assignment operator, ClearList must work first before testing" << endl;
    
    cout << "  ?x  : Search rest of list for x " << endl;
    cout << "  Q   : Quit the test program" << endl;
    cout << endl;
	
}