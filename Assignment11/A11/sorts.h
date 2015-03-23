/////////////////////////////////////////////////////////
//					Sorting Routines				   //
/////////////////////////////////////////////////////////
// Add the function signatures of sorting routines here
#define STARS "***********************************"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Struct to access/hold all data for recording
struct dataInfo {
	int loops;
	int swaps;
	int recurse;
};

///////////// BUBBLE SORT
template <class T>
void bubbleSort(T list[], int size, dataInfo& data) {
	T temp = 0;

	bool flag = true;

	int i = (size - 1);
	int count = 0;

	while (flag == true){
		
		flag = false;

		for (i = (size-1); i>count; i--){
			
			if (list[i] < list[i-1]){
				temp = list[i];
				list[i] = list[i-1];
				list[i-1] = temp;
				data.swaps++;
				flag = true;
			}

			data.loops++;
		}
		count++;
	}
}

///////////// QUICK SORT 
template <class T>
void quickSort (T arr[], int first, int last, dataInfo& data) {
	data.recurse++;

	int i = first;
	int j = last;
	T pivot = arr[last];
	T temp;

	while(i <= j) {
		while(arr[i]<pivot) {
			i++;
			data.loops++;
		}
		while(arr[j]>pivot) {
			j--;
			data.loops++;
		}
		if (i<=j) {
			temp=arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
			data.swaps++;
		}
	}
	if (first < j)
		quickSort(arr, first, j, data);
	if (i < last)
		quickSort(arr, i, last, data);

}

///////////// INSERTION SORT 
template <class T>
void insertionSort(T arr[], int size, dataInfo& data) {
	T temp;
	for (int i=1; i<size; i++){
		int j = i;
		while (j > 0 && arr[j-1] > arr[j]) {
			temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
			j--;
			// recording data
			data.swaps++;
			data.loops++;
		}
	}
}

///////////// SELECTION SORT
template <class T>
void selectionSort(T arr[], int size, dataInfo& data) {
	T min;
	T temp;
	for (int i = 0; i< size-1; i++) {
		min = i;
		for (int j = (i+1); j < size; j++) {
			if (arr[j] < arr[min])
				min = j;
			data.loops++;
		}
		if (min != i) {
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
			data.swaps++;
		}
	}
}

///////////// MERGE SORT
template <class T>
T* mergeSort(T list[], int size, dataInfo& data) {
	data.recurse++;
	if ( size <= 1 )
		return list;
	int tempSize = size / 2;

	int leftSize = tempSize;
	int rightSize = size - tempSize;
	T* left = new T[leftSize];
	T* right = new T[rightSize];

	for ( int i = 0; i < leftSize; i++ )
		left[i] = list[i];
	for ( int i = 0; i < rightSize; i++ )
		right[i] = list[i+tempSize];

	left = mergeSort(left, leftSize, data);
	right = mergeSort(right, rightSize, data);

	return mergeHelp(left, right, leftSize, rightSize, data);
}

template <class T>
T* mergeHelp(T listA[], T listB[], int sizeA, int sizeB, dataInfo& data) {
	data.recurse++;

	T* listC = new T[sizeA+sizeB];
	// size placeholders
	int a = 0, b = 0, c = 0;

	while (a < sizeA && b < sizeB) {
		if ( listA[a] < listB[b] ) {
			listC[c] = listA[a];
			a++;
			data.swaps++;
		}
		else {
			listC[c] = listB[b];
			b++;
			data.swaps++;
		}
		c++;
	}

	while ( b < sizeB ) {
		listC[c] = listB[b];
		b++; c++;
		data.swaps++;
	}

	while ( a < sizeA ) {
		listC[c] = listA[a];
		a++; c++;
		data.swaps++;
	}
	
	return listC;
}

///////////// RADIX SORT
template <class T>
void radixSort(T list[], int size, dataInfo& data) {
	// find largest value
	T max = list[0];
	for ( int i = 1; i < size; i++ )
		if ( list[i] > max ) max = list[i];

	// find out how many digits it is
	int digits = 1;
	for ( int i = 1; ( max / i > 10 ); i*=10 )
		digits++;

	for ( int i = 1; i <= digits; i++ )
		radixInsert(list, size, i, data);
}

template <class T>
void radixInsert(T arr[], int size, int tenP, dataInfo& data) {
	// ( Number % CurrentTens ) / LastTens
	int pw1 = (int)pow(10, tenP);
	int pw2 = (int)pow(10, tenP-1);

	T min;
	T temp;
	for (int i = 0; i < size-1; i++) {
		min = i;
		for (int j = (i+1); j < size; j++) {
			if ((arr[j] % pw1) / pw2 < (arr[min] % pw1) / pw2)
				min = j;
			data.loops++;
		}
		if (min != i) {
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
			data.swaps++;
		}
	}
}

///////////// INSERT ANY ADDITIONAL SORTS HERE


///////////// MAIN MENU FUNCTION
template <class T>
void mainMenu(T arr[], int size) {
	char choice = 'd';
	dataInfo data;
	
	while ( choice != 'q' && choice != 'Q' ) {
		data.loops = 0;
		data.swaps = 0;
		data.recurse = 0;


		T* list = new T [size];
		for ( int i = 0; i < size; i++ )
			list[i] = arr[i];

		switch ( choice ) {
			case 'b': case 'B':
			{
				bubbleSort(list, size, data);
				recordData(data, size, "bubble.txt");
				break;
			}
			case 'u': case 'U':
			{
				quickSort(list, 0, size-1, data);
				recordData(data, size, "quick.txt");
				break;
			}
			case 'i': case 'I':
			{
				insertionSort(list, size, data);
				recordData(data, size, "insert.txt");
				break;
			}
			case 's': case 'S':
			{
				selectionSort(list, size, data);
				recordData(data, size, "select.txt");
				break;
			}
			case 'm': case 'M':
			{
				list = mergeSort(list, size, data);
				recordData(data, size, "merge.txt");
				break;
			}
			case 'r': case 'R':
			{
				radixSort(list, size, data);
				recordData(data, size, "radix.txt");
				break;
			}
			case 'd': case 'D':
			{
				cout << STARS << endl << "\tComparing Sorts" << endl << STARS << endl;
				cout << "B. Bubble Sort" << endl;
				cout << "U. Quick Sort" << endl;
				cout << "I. Insertion Sort" << endl;
				cout << "S. Selection Sort" << endl;
				cout << "M. Merge Sort" << endl;
				cout << "R. Radix Sort" << endl;
				cout << "A. Test All" << endl;
				cout << "D. Display Menu" << endl;
				cout << "Q. Quit" << endl;
				break;
			}
			default:
			{
				cout << "NOT A VALID CHOICE. Please try again." << endl;
			}
		}
		// end of switch

		cout << endl << "Current List: " << endl;
		printList(list, size);

		delete [] list;

		cout << "> ";
		cin >> choice;
	}
}

template <class T>
void printList(T* list, int size) {
	for ( int i = 0; i < size; i++ )
		cout << list[i] << " ";
	cout << endl;
}

void recordData(dataInfo data, int size, string filename) {
	ofstream record;
	record.open(filename);

	record << "Size of List: " << size << "\n\n";
	record << "Swaps: " << data.swaps << "\n";
	record << "Loops: " << data.loops << "\n";
	record << "Recursions: " << data.recurse << "\n";

	record.close();

	cout << endl << "Data saved into " << filename << "!" << endl;
}