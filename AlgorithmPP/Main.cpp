// Main.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"

typedef void(*FPTR)(int*, int);
enum SortEnum { BUBBLE, SELECTION, INSERTION, SHELL, MERGE, QUICKSORT, RANDQUICKSORT, RADIX, HEAPSORT, STL_SORT, STL_STABLESORT, STL_SORTHEAP, EndEnum };

std::map<SortEnum, FPTR> sort;

std::chrono::high_resolution_clock::time_point timerStart, timerStop;
std::chrono::duration<double> time_span;
int ARRAY_SIZE = 100000;
const int ORDER = 32;

void strassen();
void karatsuba();
void sortDisplay();
std::string toString(SortEnum sortEnum);
void initSortMap();
void initResultList(std::list<std::pair<SortEnum, double>> *list);
void fillArray(int *a);
void printArray(int *a, int size, std::string message = "");
int* copy(int*, int*);
double execution(int*, SortEnum);


void strassen(){
	Matrix *a = new Matrix(true, ORDER);
	Matrix *b = new Matrix(true, ORDER);
	a->print("A");
	b->print("B");

	Matrix c = (*a) * (*b);
	c.print("C = A * B (using strassen algorithm)");

	Matrix::multiplication(*a, *b)->print("C = A * B (using standard multiplication algorithm)");
}


void karatsuba() {
	BigInt *a = new BigInt;
	BigInt *b = new BigInt;

	BigInt *c = (*a) * (*b);
	c->print();
}


// Comparator for the result list
struct MyGreater {
	bool operator() (const std::pair<const SortEnum, double> &p1, const std::pair<const SortEnum, double> &p2) {
		return p1.second < p2.second;
	}
};

// Convert an enum into a string
std::string toString(SortEnum sortEnum){
	switch (sortEnum){
	case BUBBLE: return "Bubble Sort";
	case SELECTION: return "Selection Sort";
	case INSERTION: return "Insertion Sort";
	case SHELL: return "Shell Sort";
	case MERGE: return "Merge Sort";
	case QUICKSORT: return "Quick Sort";
	case RANDQUICKSORT: return "Quick Sort Rand";
	case RADIX: return "Radix Sort";
	case HEAPSORT: return "Heap Sort";
	case STL_SORT: return "STL sort";
	case STL_STABLESORT: return "STL Stable Sort";
	case STL_SORTHEAP: return "STL Heap Sort";
	default: return "Sort";
	}
}

// Init the sorting map with function pointers
void initSortMap(){
	sort[BUBBLE] = &Sort::bubbleSort;
	sort[SELECTION] = &Sort::selectionSort;
	sort[INSERTION] = &Sort::insertionSort;
	sort[SHELL] = &Sort::shellSort;
	sort[MERGE] = &Sort::mergeSort;
	sort[QUICKSORT] = &Sort::quickSort;
	sort[RANDQUICKSORT] = &Sort::randQuickSort;
	sort[RADIX] = &Sort::radixSort;
	sort[HEAPSORT] = &Sort::heapSort;
	sort[STL_SORT] = &Sort::sort;
	sort[STL_STABLESORT] = &Sort::stableSort;
	sort[STL_SORTHEAP] = &Sort::sortHeap;
}

// Init the result list
void initResultList(std::list<std::pair<SortEnum, double>> *list){
	list->clear();

	for (int sortEnum = 0; sortEnum != EndEnum; sortEnum++){
		SortEnum en = static_cast<SortEnum>(sortEnum);
		list->push_back(std::pair<SortEnum, double>(en, 0));
	}
}

// Fil an array with random values
void fillArray(int* a)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());;

	for (int i = 0; i < ARRAY_SIZE; ++i){
		std::uniform_int_distribution<int> dist(0, INT_MAX);
		a[i] = dist(engine);
	}
}

// Print an array with a message
void printArray(int* a, int size, std::string message)
{
	std::cout << message << std::endl;

	for (int i = 0; i < ARRAY_SIZE; ++i)
		std::cout << a[i] << " ";
	std::cout << std::endl << std::endl;
}

// Copy an array
int* copy(int* a, int* cpy){
	for (int i = 0; i < ARRAY_SIZE; ++i)
		cpy[i] = a[i];
	return cpy;
}

// Execute an algorithm and return the timer taken
double execution(int* _array, int* arrayCopy, SortEnum sortEnum){
	//std::cout << std::endl << std::endl << "***** " << toString(sortEnum) << " *****" << std::endl;
	//printArray(_array, ARRAY_SIZE, "Unsorted list :");

	double timeSpan = 0;
	int i = 1, maxIterations = ARRAY_SIZE < 1000 ? 100 : 1;

	// Execute the algorithm i times with the same array to improve the timer precision
	for (i = 1; i <= maxIterations; i++){
		copy(_array, arrayCopy);

		timerStart = std::chrono::high_resolution_clock::now();

		sort[sortEnum](arrayCopy, ARRAY_SIZE);

		timerStop = std::chrono::high_resolution_clock::now();
		time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(timerStop - timerStart);
		timeSpan += time_span.count();
	}

	//printArray(arrayCopy, ARRAY_SIZE, "Sorted list : ");
	//std::cout << "(" << time_span.count() / i << " ticks)" << std::endl << std::endl;

	return (timeSpan / i);
}

void sortDisplay(){
	initSortMap();

	// Use different size of arrays
	for (int i = 1; i <= 100000; i *= 10){
		ARRAY_SIZE = i;
		int* theArray = new int[ARRAY_SIZE], *arrayCopy = new int[ARRAY_SIZE];
		std::list<std::pair<SortEnum, double>> resultList;
		initResultList(&resultList);

		std::cout << std::endl << std::endl << "|||||||||| ARRAY OF " << i << " ELEMENTS ||||||||||" << std::endl;

		// Generate a new array and sort it with each algorithm i times
		for (int i = 0; i < 10; i++){
			fillArray(theArray);

			// Execute each sorting algorithms in the list
			for (auto it = resultList.begin(); it != resultList.end(); ++it){
				it->second += execution(theArray, arrayCopy, it->first);
			}
		}

		// Sort the results and print them
		resultList.sort(MyGreater());
		for (auto it = resultList.begin(); it != resultList.end(); ++it){
			std::cout << toString(it->first) << "\t : " << it->second << std::endl;
		}

		delete[] theArray, arrayCopy;
	}
}


int _tmain(int argc, _TCHAR* argv[]){
	std::cout << "TP1 - Dimitri BUHON" << std::endl;
	std::string input;
	while (input != "0"){
		std::cout << std::endl << "Choisir une option : " << std::endl
			<< "1 - Strassen" << std::endl
			<< "2 - Tri" << std::endl
			<< "3 - Karatsuba" << std::endl
			<< "0 - Quitter" << std::endl << std::endl;

		std::cin >> input;

		if (input == "1"){
			std::cout << std::endl << std::endl << "Exercice 1 : Strassen" << std::endl;
			strassen();
		}
		else if (input == "2"){
			std::cout << std::endl << std::endl << "Exercice 2 : Tri" << std::endl;
			sortDisplay();
		}
		else if (input == "3"){
			std::cout << std::endl << std::endl << "Exercice 3 : Karatsuba" << std::endl;
			karatsuba();
		}
	}

	return 0;
}
























/*
#include <iostream>
#include <math.h>
#include <chrono>

//Is this less offensive than using the entire std namespace?
using std::cout;
using std::endl;

//These little functions are used by the heap-sort algorithm
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i)   (2 * i + 1)
#define RIGHT(i)  (2 * i + 2)



//First comes bubble-sort, the most brute-force sorting method.
//Bubble-sort is a simple sorting algorithm that repeatedly steps 
//through the list to be sorted, compares each pair of adjacent items 
//and swaps them if they are in the wrong order

void bubble_sort(int list[], int size)
{
	int temp;
	for (int i = 0; i<size; i++)
	{
		for (int j = size - 1; j>i; j--)
		{
			if (list[j]<list[j - 1])
			{
				temp = list[j - 1];
				list[j - 1] = list[j];
				list[j] = temp;
			}
		}
	}
}


//Insertion sort is another n^2 algorithm, which works by taking each element
//and inserting it into the proper spot.  Can work quickly on arrays that 
//are either small or nearly sorted already.

void insertion_sort(int list[], int size)
{
	for (int j = 1; j<size; j++)
	{
		int key = list[j];
		int i = j - 1;
		while (i>-1 && list[i]>key)
		{
			list[i + 1] = list[i];
			i = i - 1;
		}
		list[i + 1] = key;

	}
}

//Merge-sort is much faster than insertion-sort in general, and works by
//dividing the array successively into smaller arrays, sorting them, and then
//merging the results.  merge_sort is written as two functions, `merge` which takes two
//pre-sorted lists and merges them to a single sorted list.  This is called on by merge_sort, 
//which also recursively calls itself.

void merge(int list[], int p, int q, int r)
{
	//n1 and n2 are the lengths of the pre-sorted sublists, list[p..q] and list[q+1..r]
	int n1 = q - p + 1;
	int n2 = r - q;
	//copy these pre-sorted lists to L and R
	int *L = new int[n1 + 1];
	int *R = new int[n2 + 1];
	for (int i = 0; i<n1; i++)
	{
		L[i] = list[p + i];
	}
	for (int j = 0; j<n2; j++)
	{
		R[j] = list[q + 1 + j];
	}


	//Create a sentinal value for L and R that is larger than the largest
	//element of list
	int largest;
	if (L[n1 - 1]<R[n2 - 1]) largest = R[n2 - 1]; else largest = L[n1 - 1];
	L[n1] = largest + 1;
	R[n2] = largest + 1;

	//Merge the L and R lists
	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			list[k] = L[i];
			i++;
		}
		else
		{
			list[k] = R[j];
			j++;
		}
	}

	delete(R, L);
}

void merge_sort_aux(int list[], int p, int r)
{
	if (p<r)
	{
		int q = floor((p + r) / 2);
		merge_sort_aux(list, p, q);
		merge_sort_aux(list, q + 1, r);
		merge(list, p, q, r);
	}

}

void merge_sort(int list[], int size)
{
	merge_sort_aux(list, 0, size - 1);
}

//Heap-sort is a really interesting algorithm, which first arranges the 
//array into a max-heap, before sorting.  In a max-heap, each element is 
//greater than its 'children', LEFT and RIGHT.

class heap
{
public:
	int *nodes;
	int length;
	int heap_size;
};

//max_heapify places the element list[index] into the subarray list[index+1...], 
//which is assumed to already be in max-heap form

void max_heapify(heap list, int index)
{

	int left, right, largest, exchange_temp;

	left = LEFT(index);
	right = RIGHT(index);

	if (left <list.heap_size && list.nodes[left] > list.nodes[index])
	{
		largest = left;
	}
	else
	{
		largest = index;
	}

	if (right <list.heap_size && list.nodes[right] > list.nodes[largest])
	{
		largest = right;
	}


	if (largest != index)
	{
		exchange_temp = list.nodes[index];
		list.nodes[index] = list.nodes[largest];
		list.nodes[largest] = exchange_temp;
		max_heapify(list, largest);
	}

}

//build_max_heap turns an array into max-heap form by repeatedly calling
//max_heapify

void build_max_heap(heap list)
{
	list.heap_size = list.length;
	for (int i = floor(list.length / 2); i >= 0; i--)
	{
		max_heapify(list, i);
	}
}

//Since one property of a max-heap is that the first element is the largest,
//heap_sort swaps this element with the last element, then re-heapifies the 
//rest, recursively until the whole array is sorted

void heap_sort(int list[], int size)
{
	int exchange_temp;
	heap tempheap;
	tempheap.length = size;
	tempheap.nodes = list;
	tempheap.heap_size = size;
	build_max_heap(tempheap);


	for (int i = tempheap.length - 1; i >= 1; i--)
	{
		exchange_temp = tempheap.nodes[0];
		tempheap.nodes[0] = tempheap.nodes[i];
		tempheap.nodes[i] = exchange_temp;
		tempheap.heap_size = tempheap.heap_size - 1;

		max_heapify(tempheap, 0);
	}

}

//Quicksort works by dividing the array based upon a 'pivot' element, everything
//to the right of it are greater than or equal to the pivot, everything 
//smaller than the pivot are moved to the left.  Then the left and right
//arrays are sorted in the same way.  Works great on a random array, but
//data that is nearly already sorted are very slow by this method.

int partition(int list[], int p, int r)
{
	int pivot, index, exchange_temp;
	pivot = list[r];
	index = p - 1;
	for (int i = p; i < r; i++)
	{
		if (list[i] <= pivot)
		{
			index++;
			exchange_temp = list[i];
			list[i] = list[index];
			list[index] = exchange_temp;
		}
	}
	exchange_temp = list[r];
	list[r] = list[index + 1];
	list[index + 1] = exchange_temp;
	return index + 1;
}

void quicksort_aux(int list[], int p, int r)
{
	int q;
	if (p<r)
	{
		q = partition(list, p, r);
		quicksort_aux(list, p, q - 1);
		quicksort_aux(list, q + 1, r);
	}
}

void quick_sort(int list[], int size)
{
	quicksort_aux(list, 0, size - 1);
}*/

