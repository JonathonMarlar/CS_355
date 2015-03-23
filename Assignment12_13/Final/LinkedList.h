/////////////////////////////////////////////////////////////////////////
//		Michael Bretherick
//		Templated Linked List
//		Description: Linked list templated for any data type with cursor
//					 functions to access and manipulate list data.
/////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#ifndef LinkedList_H
#define LinkedList_H

template <class T>
class LinkedList;

template <class T>
class Node{
	T data;
	Node* next;
	Node();
	Node(T e);
	Node(T e, Node* n);
 	friend ostream& operator<< <>(ostream& out,const LinkedList<T>& list);
	friend class LinkedList<T>;
};

template<class T>
class LinkedList{
	Node<T>* head;
	Node<T>* cursorLocation;
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<T>& right);
	void printCursor() const;
	bool Insert(T e);
	bool Remove(T e);
	Node<T>* Search(T e);
	void Print(ostream&) const;
	T AtCursor() const;
	void GoToBeginning();
	void GoToEnd();
	void GoToNext();
	void GoToPrev();
	void ClearList();
	bool Empty() const;
	LinkedList& operator=	(const LinkedList<T>& right);
 	friend ostream& operator<< <>(ostream& out,const LinkedList<T>& list);
};

template <class T>
Node<T>::Node(){
	next = NULL;
}

template <class T>
Node<T>::Node(T e){
	data = e;
	next = NULL;
}

template <class T>
Node<T>::Node(T e, Node* n){
	data = e;
	next = n;
}

template <class T>
LinkedList<T>::LinkedList(){
	head = NULL;
	cursorLocation = NULL;
}

template <class T>
LinkedList<T>::~LinkedList(){
	Node<T>* tempHead;
	while(head != NULL){
		tempHead = head;
		head = head->next;
		delete tempHead;
	}
	head =  NULL;
	cursorLocation = NULL;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& right){
	head = NULL;
	Node<T>* tempHead = right.head;
	while(tempHead->next != NULL){
		this->Insert(tempHead->data);
		tempHead = tempHead->next;
	}
	this->Insert(tempHead->data);
}

template <class T>
void LinkedList<T>::printCursor() const{
	if(cursorLocation != NULL){
		cout << cursorLocation->data;
	}
}

template <class T>
bool LinkedList<T>::Insert(T e){

	Node<T>* tempNode = new Node<T>(e);
	Node<T>* tempHead;
	Node<T>* lastNode;

	if(head == NULL){												//Puts data into an empty list.
		head = tempNode;
	}
	else if(head->data >= e){										//Puts new lowest number at start of list.
		tempNode->next = head;
		head = tempNode;
	}
	else {
		tempHead = lastNode = head;
		while(tempHead->next != NULL && tempHead->data <= e){		//Goes through the list checking if at the end and if the data in the current spot is greater than the input.
			lastNode = tempHead;
			tempHead = tempHead->next;
		}
		if(tempHead->next == NULL && tempHead->data <= e){			//Puts data in last spot of list.
			tempHead->next = tempNode;
		}
		else if(tempHead->next == NULL){							//Puts data in second to last spot of list.
			tempNode->next = tempHead;
			lastNode->next = tempNode;
		}
		else{														//Puts data anywhere else in list.
			tempNode->next = tempHead;
			lastNode->next = tempNode;
		}
	}
	cursorLocation = tempNode;
	return true;
}

template <class T>
bool LinkedList<T>::Remove(T e){

	if(head == NULL){												//If empty list do nothing
		return false;
	}

	Node<T>* tempNode = head;
	Node<T>* lastNode = NULL;

	if(tempNode->data == e){										//Removes if first entry in list.
		head = head->next;
		cursorLocation = head;
	}
	else{															
		while(tempNode->next != NULL){								//Loop to find value to remove
			if(tempNode->data == e){
				break;
			}
			lastNode = tempNode;
			tempNode = tempNode->next;
		}

		if(tempNode->next == NULL && tempNode->data != e){			//If value is not in the list return false.
			cursorLocation = tempNode;
			return false;
		}

		else if(tempNode->next == NULL && tempNode->data == e){		//If value is last in the list.
			lastNode->next = NULL;
			cursorLocation = lastNode;
		}
		else{														//If value is in the middle of the list somewhere.
			cursorLocation = tempNode->next;
			lastNode->next = tempNode->next;
		}
	}
	return true;
}

template <class T>
Node<T>* LinkedList<T>::Search(T e){
	Node<T>* tempHead = head;

	while(tempHead->next != NULL && tempHead->data != e){
		tempHead = tempHead->next;
	}

	if(tempHead->data != e){
		tempHead = NULL;
		cursorLocation = tempHead;
	}
	else{
		cursorLocation = tempHead;
	}
	return tempHead;
}

template <class T>
void LinkedList<T>::Print(ostream& out) const{
	Node<T>* tempNode = head;

	while(tempNode != NULL){
		if(tempNode == cursorLocation){
			out << "[" << tempNode->data << "]";
			tempNode = tempNode->next;
		}
		else{
			out << tempNode->data;
			tempNode = tempNode->next;
		}
		out << "\t";
	}
}

template <class T>
T LinkedList<T>::AtCursor() const{
	return cursorLocation->data;
}

template <class T>
void LinkedList<T>::GoToBeginning(){
	cursorLocation = head;
}

template <class T>
void LinkedList<T>::GoToEnd(){
	if(head == NULL){
		cursorLocation = NULL;
	}
	else{
		Node<T>* tempHead = head;
		while(tempHead->next != NULL){
			tempHead = tempHead->next;
		}
	cursorLocation = tempHead;
	}
}

template <class T>
void LinkedList<T>::GoToNext(){
	if(cursorLocation->next == NULL){
		cursorLocation = head;
	}
	else{
		cursorLocation = cursorLocation->next;
	}
}

template <class T>
void LinkedList<T>::GoToPrev(){
	Node<T>* tempHead = head;
	
	if(cursorLocation != head){
		while(tempHead->next != cursorLocation){
			tempHead = tempHead->next;
		}
		cursorLocation = tempHead;
	}
	else{
		while(tempHead->next != NULL){
			tempHead = tempHead->next;
		}
		cursorLocation = tempHead;
	}
}

template <class T>
void LinkedList<T>::ClearList(){
	delete this;
}

template <class T>
bool LinkedList<T>::Empty() const{
	if(head == NULL){
		return true;
	}
	return false;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& right){
	
	this->head = NULL;
	Node<T>* tempHead = right.head;

	while(tempHead->next != NULL){
		this->Insert(tempHead->data);
		tempHead = tempHead->next;
	}

	this->Insert(tempHead->data);

	return *this;
}

template <class T>
ostream& operator<<(ostream& out,const LinkedList<T>& list){
	
	Node<T>* tempNode = list.head;

	while(tempNode!=NULL){
		out << tempNode->data << " ";
		tempNode = tempNode->next;
	}

	return out;
}

#endif
