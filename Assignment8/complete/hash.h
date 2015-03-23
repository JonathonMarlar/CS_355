#pragma once

template <class T>
class Hash {
private:
	T* hashList;
	int hashSize;
	// int makePrime(int size);

public:
	Hash();
	Hash( int size );
	Hash( const Hash& );
	~Hash();

	Hash& operator=( const Hash& Val );
	void ShowFill() const;
	void ShowContents() const;
	int Insert( T key );
	int Remove( T key );
	int Search( T key );
	int NewSlot( T HashVal, int trynumber );

	// added functions to help get information
	T giveData( int slot ) const;
	int giveSize() const;
};
