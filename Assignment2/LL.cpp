#include "LL.h"
#include <new>

Node::Node() {
	data = 0;
	next = 0;
}

Node::Node(int e) {
	data = e;
	next = 0;
}

Node::Node(int e, Node * n) {
	data = e;
	next = n;
}

LL::LL() : head(0) { }

LL::~LL() {
	Node * tempHead;

	while ( head != 0 ) {
		tempHead = head;
		head = head->next;
		delete tempHead;
	}
}

bool LL::Insert(int e) {
	if ( noMemory() ) return false;
	
	Node * newNode = new Node(e);

	// Nothing's in the list
	if ( head == 0 ) {
		head = newNode;
		return true;
	}
	else {
		// Something's in the list
		Node * prevNode = head;
		Node * nextNode = head->next;

		// at head
		if ( prevNode->data > newNode->data && prevNode == head && prevNode->next == 0 ) {
			newNode->next = head;
			head = newNode;
			return true;
		}
		else if ( prevNode->data <= newNode->data && prevNode == head ) {
			newNode->next = head->next;
			head->next = newNode;
			return true;
		}

		// middle
		while ( nextNode != 0 ) {
			if ( prevNode->data <= newNode->data && nextNode->data > newNode->data ) {
				prevNode->next = newNode;
				newNode->next = nextNode;
				return true;
			}
			prevNode = prevNode->next;
			nextNode = nextNode->next;
		}
	}

	return true;
}

bool LL::Remove(int e) {
	return true;
}

/*******************************************************************
FUNCTION:		insertFront(int)
PURPOSE:		Inserts an integer into the front of a linked list
INCOMING:		Integer
OUTGOING:		A node in a linked list
RETURN:			TRUE if memory allocation was successful
********************************************************************/
bool LL::insertFront(int e) {
	if ( noMemory() ) return false;
	else {
		Node * newNode = new Node(e,head);
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
bool LL::insertBack(int e) {
	if ( noMemory() ) return false;
	else {
		Node * newNode = new Node(e);
		Node * tempNode = head;

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
bool LL::removeFront() {
	Node * tempNode = head;

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
bool LL::removeBack() {
	Node * tempPrev = head;
	Node * tempNext = head->next;

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
void LL::printLL(std::ostream * os) const {
	Node * tempNode = head;

	while ( tempNode != 0 ) {
		*os << tempNode->data << std::endl;
		tempNode = tempNode->next;
	}
}

/*******************************************************************
FUNCTION:		noMemory()
PURPOSE:		Checks to see if the computer has enough memory for
				allocation
INCOMING:		N/A
OUTGOING:		N/A
RETURN:			TRUE if there is no more memory
********************************************************************/
bool LL::noMemory() {
	Node * testNode;

	try {
		testNode = new Node;
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
std::ostream & operator << (std::ostream & os, const LL & source) {
	source.printLL(&os);

	return os;
}