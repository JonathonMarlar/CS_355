#pragma once

#include <iostream>

class Node {
	int data;
	Node * next;

	Node();
	Node(int e);
	Node(int e, Node * n);

	friend class LL;
};

class LL {
	private:
		Node * head;
	
	public:
		LL();
		~LL();

		bool Insert(int e);
		bool Remove(int e);

		bool insertFront(int e);
		bool insertBack(int e);
		bool removeFront();
		bool removeBack();

		void printLL(std::ostream * os) const;
		friend std::ostream & operator << (std::ostream & os, const LL & source);

		bool noMemory();
};