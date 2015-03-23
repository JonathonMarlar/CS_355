/*
**			Simple Queue class 
**			 Joshua Reinoehl
**			   11/29/2012
*/



#include<iostream>
using namespace std;



template<class T>
class queue
{
public:
	queue(int);
	~queue();
	bool push(T);
	T pop();
	// to see if the queue is empty
	bool isEmpty();

private:
	T * ar; 
	int size,pos;
};


template<class T>
queue<T>::queue(int e)
{
	size=e;
	pos=0;
	ar=new T[size];
	for(int c=0;c<size;c++)
		ar[c]=-1;
}

template<class T>
queue<T>::~queue()
{
	delete [] ar;
}

template<class T>
bool queue<T>::push(T e)
{
	bool flag=false;
	for(int c=0;c<size;c++)
		if(ar[c]==-1)
			flag=true;
	if(flag)
	{
		ar[pos++]=e;
	}
	return flag;
}

template<class T>
T queue<T>::pop()
{
	T temp;
	temp=ar[0];
	for(int c=0;c<size-1;c++)
		ar[c]=ar[c+1];
	ar[size-1]=-1;
	if(pos>0)
		pos--;

	return temp;
}

// added function by cole
template<class T>
bool queue<T>::isEmpty() {
	bool e = false;
	
	if ( ar[0] == -1 )
		e = true;

	return e;
}