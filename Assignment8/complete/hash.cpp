#include "hash.h"
#include <iostream>
using namespace std;

template <class T>
Hash<T>::Hash() {
	// default call
	hashSize = 11;
	hashList = new T [hashSize] ();
}

template <class T>
Hash<T>::Hash( int size ) {
	hashSize = ( size * 2 ) + 1;
	hashList = new T [hashSize] ();
}

template <class T>
Hash<T>::Hash( const Hash& Val ) {
	hashSize = Val.giveSize();
	hashList = new T [hashSize] ();
	for ( int i = 0; i < hashSize; i++ )
		hashList[i] = Val.giveData(i);
}

template <class T>
Hash<T>::~Hash() {
	delete [] hashList;
}

template <class T>
Hash<T> & Hash<T>::operator=( const Hash& Val ) {
	delete [] this->hashList;

	this = new Hash(Val);

	return this;
}

template <class T>
void Hash<T>::ShowFill() const {
	for ( int i = 0; i < hashSize; i++ ) {
		if ( hashList[i] == NULL )
			cout << "X" << endl;
		else cout << hashList[i] << endl;
	}
}

template <class T>
void Hash<T>::ShowContents() const {
	for ( int i = 0; i < hashSize; i++ ) {
		if ( hashList[i] != NULL )
			cout << "Slot " << i << ": " << hashList[i] << endl;
	}
}

template <class T>
int Hash<T>::Insert( T key ) {
	int hitCounter = 0;

	int row = key % hashSize;

	while ( hashList[row] != NULL ) {
		row++;
		if ( row >= hashSize )
			row = 0;
		hitCounter++;
	}
	if ( hashList[row] == NULL ){
		hashList[row] = key;
		hitCounter++;
	}
	else {
		cout << "Hash list full." << endl;
	}

	return hitCounter;
}

template <class T>
int Hash<T>::Remove( T key ) {
	int hitCounter = 0;

	for ( int i = 0; i < hashSize; i++ ) {
		if ( hashList[i] == key ) {
			hashList[i] = NULL;
		}
		hitCounter++;
	}

	return hitCounter;
}

template <class T>
int Hash<T>::Search( T key ) {
	int hitCounter = 0;
	bool found = false;
	
	for ( int i = 0; i < hashSize; i++ ) {
		if ( hashList[i] == key ) {
			found = true;
			break;
		}
		hitCounter++;
	}

	if ( found == true ) cout << "Found!" << endl;
	else cout << "Not found..." << endl;

	return hitCounter;
}

template <class T>
int Hash<T>::NewSlot( T HashVal, int trynumber ) {
	// int hitCounter = 0;
	int slot = HashVal % hashSize;
	
	while ( hashList[slot] != NULL ) {
		slot++;
		if ( slot >= hashSize )
			slot = 0;
	}
	
	return slot;
}

template <class T>
T Hash<T>::giveData( int slot ) const {
	if ( slot < hashSize )
		return hashList[slot];
	else
		return 0;
}

template <class T>
int Hash<T>::giveSize() const {
	return hashSize;
}
