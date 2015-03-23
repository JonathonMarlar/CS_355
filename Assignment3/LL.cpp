#include "LL.h"
#include <new>
using namespace std;

template <class T>
Node<T>::Node() {
	data = 0;
	next = 0;
}

template <class T>
Node<T>::Node(T e) {
	data = e;
	next = 0;
}

template <class T>
Node<T>::Node(T e, Node * n) {
	data = e;
	next = n;
}

template <class T>
LL<T>::LL() : head(0), cursor(0) { }

template <class T>
LL<T>::LL(const LL& source) {
	this->head = 0;
	this->cursor = 0;

	Node<T> * tempnode = source.head;

	while ( tempnode != 0 ) {
		this->Insert(tempnode->data);
		tempnode = tempnode->next;
	}

	//delete tempnode;
}

template <class T>
LL<T>::~LL() {
	ClearList();
}

/*******************************************************************
FUNCTION:		Insert(T)
PURPOSE:		Inserts data into the front of a linked list
INCOMING:		T
OUTGOING:		A node in a linked list
RETURN:			TRUE if memory allocation was successful
********************************************************************/
template <class T>
bool LL<T>::Insert(T e) {
	if ( noMemory() ) return false;
	
	Node<T> * newNode = new Node<T>(e);

	// Nothing's in the list
	if ( head == 0 ) {
		head = newNode;
		cursor = head;
		return true;
	}
	else {
		// Something's in the list at head
		if ( head->data < newNode->data && head->next == 0 ) {
			head->next = newNode;
			cursor = head->next;
			return true;
		}
		else if ( head->data > newNode->data ) {
			newNode->next = head;
			head = newNode;
			cursor = head;
			return true;
		}

		// middle
		Node<T> * prevNode = head;
		Node<T> * nextNode = head->next;

		while ( nextNode != 0 ) {
			if ( prevNode->data <= newNode->data && nextNode->data > newNode->data ) {
				prevNode->next = newNode;
				newNode->next = nextNode;
				cursor = newNode;
				return true;
			}
			prevNode = prevNode->next;
			nextNode = nextNode->next;
		}

		if ( nextNode == 0 ) {
			prevNode->next = newNode;
			cursor = newNode;
			return true;
		}
	}

	return true;
}

/*******************************************************************
FUNCTION:		Remove(T)
PURPOSE:		Inserts data into the back of a linked list
INCOMING:		T
OUTGOING:		A node in a linked list
RETURN:			TRUE if memory allocation was successful
********************************************************************/
template <class T>
bool LL<T>::Remove(T e) {
	Node<T> * prev;
	Node<T> * current = head;

	while ( current != 0 ) {
		if ( current->data == e ) {
			if ( current == head )
				head = current->next;
			else
				prev->next = current->next;

			delete current;
			return true;
		}

		prev = current;
		current = current->next;
	}

	return false;
}

/*******************************************************************
FUNCTION:		Search(T)
PURPOSE:		Finds data of type T in a node and places the
				cursor there
INCOMING:		T
OUTGOING:		Cursor set to that node
RETURN:			Address of the cursor
********************************************************************/
template <class T>
Node<T> * LL<T>::Search(T e) {
	Node<T> * tempH = cursor;

	while ( tempH != 0 ) {
		if ( tempH->data == e ) {
			cursor = tempH;
			return tempH;
		}
		else if ( tempH->next == 0 ) {
			cursor = tempH;
			return NULL;
		}
		tempH = tempH->next;
	}
}

/*******************************************************************
FUNCTION:		goToBeginning()
PURPOSE:		Moves the cursor to the beginning of the list
INCOMING:		N/A
OUTGOING:		Cursor sent to head
RETURN:			TRUE if allocation was successful
********************************************************************/
template <class T>
bool LL<T>::GoToBeginning() {
	if ( head != 0 ) {
		cursor = head;
		return true;
	}

	// unable to set cursor to head
	return false;
}

/*******************************************************************
FUNCTION:		goToEnd()
PURPOSE:		Moves the cursor to the end of the list
INCOMING:		N/A
OUTGOING:		The cursor set to the last item of a list
RETURN:			TRUE if allocation was successful
********************************************************************/
template <class T>
bool LL<T>::GoToEnd() {
	Node<T> * tempH = head;

	while ( tempH !=0 ) {
		if ( tempH->next == 0 ) {
			cursor = tempH;
			return true;
		}

		tempH = tempH->next;
	}

	return false;
}

/*******************************************************************
FUNCTION:		goToNext()
PURPOSE:		Moves the cursor to the next item on the list
INCOMING:		N/A
OUTGOING:		The cursor moving to the next
RETURN:			TRUE if allocation was successful
********************************************************************/
template <class T>
bool LL<T>::GoToNext() {
	if ( cursor->next == 0 ) {
		cursor = head;
		return true;
	}
	else {
		cursor = cursor->next;
	}

	return false;
}

/*******************************************************************
FUNCTION:		goToPrev
PURPOSE:		Sets the cursor to the previous item
INCOMING:		N/A
OUTGOING:		The cursor set to the previous item
RETURN:			TRUE if allocation was successful
********************************************************************/
template <class T>
bool LL<T>::GoToPrev() {
	Node<T> * tempN = head;

	while ( tempN != 0 ) {
		if ( tempN->next == cursor ) {
			cursor = tempN;
			return true;
		}
		else if ( tempN->next == 0 && head == cursor ) {
			cursor = tempN;
			return true;
		}

		tempN = tempN->next;
	}

	return false;
}

template <class T>
T LL<T>::AtCursor() {
	return cursor->data;
}

/*******************************************************************
FUNCTION:		clearList()
PURPOSE:		Deallocates memory back into the computer
INCOMING:		N/A
OUTGOING:		Freed memory
RETURN:			N/A
********************************************************************/
template <class T>
void LL<T>::ClearList() {
	Node<T> * tempHead;

	while ( head != 0 ) {
		tempHead = head;
		head = head->next;
		delete tempHead;
	}

	head = 0;
	cursor = 0;
}

template <class T>
bool LL<T>::Empty() {
	if ( head == 0 )
		return true;
	else
		return false;
}

/*******************************************************************
FUNCTION:		insertFront(int)
PURPOSE:		Inserts an integer into the front of a linked list
INCOMING:		Integer
OUTGOING:		A node in a linked list
RETURN:			TRUE if memory allocation was successful
********************************************************************/
template <class T>
bool LL<T>::insertFront(T e) {
	if ( noMemory() ) return false;
	else {
		Node<T> * newNode = new Node<T>(e,head);
		head = newNode;
	}

	return true;
}

/*******************************************************************
FUNCTION:		insertBack(int)
PURPOSE:		Inserts an integer on the back of a linked list
INCOMING:		Integer
OUTGOING:		A new node at the end of a linked list
RETURN:			TRUE if memory allocation was successful
********************************************************************/
template <class T>
bool LL<T>::insertBack(T e) {
	if ( noMemory() ) return false;
	else {
		Node<T> * newNode = new Node<T>(e);
		Node<T> * tempNode = head;

		if ( head->next == 0 )
			head->next = newNode;
		else {
			while ( tempNode != 0 ) {
				if ( tempNode->next == 0 ) {
					tempNode->next = newNode;
					return true;
				}
				tempNode = tempNode->next;
			}
		}
	}

	return true;
}

/*******************************************************************
FUNCTION:		removeFront()
PURPOSE:		removes a node at the top of the linked list
INCOMING:		N/A
OUTGOING:		Deletion of a node
RETURN:			TRUE if deletion was successful
********************************************************************/
template <class T>
bool LL<T>::removeFront() {
	Node<T> * tempNode = head;

	if ( tempNode != 0 ) {
		head = tempNode->next;
		delete tempNode;
	}

	return true;
}

/*******************************************************************
FUNCTION:		removeBack()
PURPOSE:		Deletes a node at the end of a linked list
INCOMING:		N/A
OUTGOING:		deleted node
RETURN:			TRUE if deletion was successful
********************************************************************/
template <class T>
bool LL<T>::removeBack() {
	Node<T> * tempPrev = head;
	Node<T> * tempNext = head->next;

	if ( head->next == 0 )
		return true;
	else {
			while ( tempNext != 0 ) {
				if ( tempNext->next == 0 ) {
					tempPrev->next = 0;
					delete tempNext;
					return true;
				}
				tempPrev = tempPrev->next;
				tempNext = tempNext->next;
			}
		}

	return true;
}

/*******************************************************************
FUNCTION:		printLL(ostream*)
PURPOSE:		Prints the data stored in a node
INCOMING:		output stream
OUTGOING:		the changed output stream
RETURN:			N/A
********************************************************************/
/*
template <class T>
void LL<T>::printLL(std::ostream * os) const {
	Node<T> * tempNode = head;

	while ( tempNode != 0 ) {
		if ( cursor == tempNode )
			*os << "[" << tempNode->data << "]" << endl;
		else *os << tempNode->data << std::endl;
		tempNode = tempNode->next;
	}
}
*/

/*******************************************************************
FUNCTION:		noMemory()
PURPOSE:		Checks to see if the computer has enough memory for
				allocation
INCOMING:		N/A
OUTGOING:		N/A
RETURN:			TRUE if there is no more memory
********************************************************************/
template <class T>
bool LL<T>::noMemory() {
	Node<T> * testNode;

	try {
		testNode = new Node<T>;
		delete testNode;
		return false;
	}

	catch(std::bad_alloc e) {
		return true;
	}
}

/*******************************************************************
FUNCTION:		operator<<(ostream&, LL&)
PURPOSE:		Overload the << so that linked lists can be printed
				easily
INCOMING:		An output stream, the linked list to be printed
OUTGOING:		The output stream to printLL()
RETURN:			The edited output stream
********************************************************************/
/*
template <class T>
ostream & operator << (ostream & os, const LL<T> & source) {
	source.printLL(&os);

	return os;
}
*/

template <class T>
LL<T> & LL<T>::operator = (const LL& source) {
	/*
	// need two pointers
	// one for this head and one for source head
	this->head = 0;
	this->cursor = 0;

	Node<T> * tempnode = source.head;

	while ( tempnode != 0 ) {
		this->Insert(tempnode->data);
		tempnode = tempnode->next;
	}

	return &this;
	*/
	return NULL;
}

template <class T>
void LL<T>::Print() {
	Node<T> * tempNode = head;

	while ( tempNode != 0 ) {
		if ( cursor == tempNode )
			cout << "[" << tempNode->data << "]" << "\t";
		else 
			cout << tempNode->data << "\t";

		tempNode = tempNode->next;
	}
}