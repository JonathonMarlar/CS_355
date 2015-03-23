#include "BST.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu();


int main(){
	
	BST testBST;
	BST testAssign;
	BNode* temp;
	int data;

	PrintMenu();
	cout << "-->";
	char choice;
	cin >> choice;

	while(choice != 'q' && choice != 'Q'){
		
		if (choice == '!'){
			BST testCopy(testBST);
			cout << "Result:" << "Print New Copy" << endl;
			testCopy.PrintIn(cout); cout << endl;
			testCopy.Insert(-10000);
			cout << "Result: " << "Print Modified Copy" << endl;
			testCopy.PrintIn(cout); cout << endl;
			cout << "Result: " << "Print Original Test List" << endl;
			testBST.PrintIn(cout); cout << endl;
		}
		else{
			switch (choice){
				case 'h':
				case 'H': PrintMenu(); break;
				case '+':
					cin >> data;
					testBST.Insert(data);
					break;		
				case '-':
					cin >> data;
					testBST.Remove(data);
					break;
				
				case '@':
					cout <<"Result:";
					temp = testBST.AtCursor();
					if (temp)
						cout << temp->GetData() << endl;
					else
						cout << "NULL POINTER" << endl;
					break;
				case '<':
					testBST.GoToBeginning();
					break;
				case '>':
					testBST.GoToEnd();
					break;
				case 'n':
				case 'N':
					testBST.GoToNext();
					break;
				case 'p':
				case 'P':
					testBST.GoToPrev();
					break;
				case 'c':
				case 'C':
					testBST.ClearList();
					break;
					
				case 'e':
				case 'E':
					if (testBST.Empty())
						cout <<"Result:" <<  "List Is Empty" << endl;
					else
						cout <<"Result:" <<  "List is Not Empty" << endl;
					break;
				case '#':
					//assign list
					testAssign = testBST;
					testAssign.Insert(-100000);
					cout << "Modify New List" << endl;
					testAssign.PrintIn(cout); cout << endl;
					cout << "Old List should not be affected" << endl;
					testBST.PrintIn(cout); cout << endl;
					testAssign.~BST();
					cout << "Destroy New List" << endl;
					cout << "Old List should not be affected" << endl;
					testBST.PrintIn(cout); cout << endl;
					break;
				case '?':
					cin >> data;
					if (testBST.Find(data) != NULL)
						cout << "Result:" << data << "\tfound" << endl;
					else
						cout << "Result:" << data << "\tnot found" << endl;
					break;
				case 'i':
				case 'I':
					cout << "Print INORDER" << endl;
					testBST.PrintIn(cout); cout << endl;
					break;
				case 'r':
				case 'R':
					cout << "Print PREORDER" << endl;
					testBST.PrintPre(cout); cout << endl;
					break;
				case 'o':
				case 'O':
					cout << "Print POSTORDER" << endl;
					testBST.PrintPost(cout); cout << endl;
					break;
				default:
					cout << "INVALID CHOICE, Choose Again" << endl;
			}

		}
		testBST.PrintIn(cout); cout << endl;
		cout << "-->";
		cin >> choice;
	}

	return 0;
}

void PrintMenu(){
	/*Commands borrowed from Lab*/
	cout << endl << endl;
	cout << "  Command Line Options" << endl;
	cout << "  H\tHelp: Show Comman Line Options" << endl;
	cout << "  +x\tInsert x in order" << endl;
	cout << "  -x\tRemove x" << endl;
	cout << "  @   : Display the data item marked by the cursor" << endl;
    cout << "  <   : Go to the beginning of the list" << endl;
    cout << "  >   : Go to the end of the list" << endl;
    cout << "  N   : Go to the next data item" << endl;
    cout << "  P   : Go to the prior data item" << endl;
    cout << "  C   : Clear the list" << endl;
    cout << "  E   : Empty list?" << endl;
    cout << "  !   : Test copy constructor" << endl;
    cout << "  #   : Test assignment operator, ClearList must work first before testing" << endl;
    
    cout << "  ?x  : Search rest of list for x " << endl;
	cout << "  I   : Print the List InOrder" << endl;
	cout << "  R   : Print the List PreOrder" << endl;
	cout << "  O   : Print the List PostOrder" << endl;
    cout << "  Q   : Quit the test program" << endl;
    cout << endl << endl << endl;
	
}