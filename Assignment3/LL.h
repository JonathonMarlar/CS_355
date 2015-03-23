#pragma once

#include <iostream>
using namespace std;

template <class T>
class Node {
	T data;
	Node<T> * next;

	Node();
	Node(T e);
	Node(T e, Node * n);
	template <class T>
	friend class LL;
};

template <class T>
class LL {
	private:
		Node<T> * head;
		Node<T> * cursor;
	
	public:
		LL();
		LL(const LL& source);
		~LL();

		bool Insert(T e);
		bool Remove(T e);
		Node<T> * Search(T e);

		bool GoToBeginning();
		bool GoToEnd();	
		bool GoToNext();
		bool GoToPrev();

		T AtCursor();

		void ClearList();
		bool Empty();

		bool insertFront(T e);
		bool insertBack(T e);
		bool removeFront();
		bool removeBack();

		//void printLL(std::ostream * os) const;
		//friend ostream & operator << <>(ostream & os, const LL<T> & source);

		LL & operator = (const LL& source);

		void Print(); // needs const

		bool noMemory();
};