#include "stdafx.h"

/*
Dimitri BUHON
Exercice 2
*/

typedef void(*FPTR)(int*, int);
enum SortEnum { BUBBLE, SELECTION, INSERTION, SHELL, MERGE, QUICKSORT, RANDQUICKSORT, RADIX, HEAPSORT, STL_SORT, STL_STABLESORT, STL_SORTHEAP, EndEnum };

std::map<SortEnum, FPTR> sort;
std::list<std::pair<SortEnum, double>> resultList;

std::chrono::high_resolution_clock::time_point timerStart, timerStop;
std::chrono::duration<double> time_span;
int ARRAY_SIZE = 10;

std::string toString(SortEnum sortEnum);
void initSortMap();
void initResultList();
void fillArray(int *a);
void printArray(int *a, int size, std::string message = "");
int* copy(int*, int*);
double execution(int*, SortEnum);

// Comparator for the result list
struct MyGreater {
	bool operator() (const std::pair<const SortEnum, double> &p1, const std::pair<const SortEnum, double> &p2)
	{
		return p1.second < p2.second;
	}
};

// Convert an enum into a string
std::string toString(SortEnum sortEnum){
	switch (sortEnum){
	case BUBBLE			: return "Bubble Sort";
	case SELECTION		: return "Selection Sort";
	case INSERTION		: return "Insertion Sort";
	case SHELL			: return "Shell Sort";
	case MERGE			: return "Merge Sort";
	case QUICKSORT		: return "Quick Sort";
	case RANDQUICKSORT	: return "Quick Sort Rand";
	case RADIX			: return "Radix Sort";
	case HEAPSORT		: return "Heap Sort";
	case STL_SORT			: return "STL sort";
	case STL_STABLESORT		: return "STL Stable Sort";
	case STL_SORTHEAP		: return "STL Heap Sort";
	default				: return "Sort";
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
void initResultList(){
	for (int sortEnum = 0; sortEnum != EndEnum; sortEnum++){
		SortEnum en = static_cast<SortEnum>(sortEnum);
		resultList.push_back(std::pair<SortEnum, double>(en, 0));
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
	int i = 1;

	// Execute the algorithm i times with the same array to improve the timer precision
	for (i = 1; i <= 1; i++){
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


int main(){
	ARRAY_SIZE = 10000;
	int *theArray = new int[ARRAY_SIZE], *arrayCopy = new int[ARRAY_SIZE];

	initSortMap();
	initResultList();

	// Generate a new array and sort it with each algorithm i times
	for (int i = 0; i < 10; i++){
		fillArray(theArray);

		// Execute each sorting algorithms
		for (auto it = resultList.begin(); it != resultList.end(); ++it){
			it->second += execution(theArray, arrayCopy, it->first);
		}
	}

	// Sort the results and print them
	resultList.sort(MyGreater());
	for (auto it = resultList.begin(); it != resultList.end(); ++it){
		std::cout << toString(it->first) << "\t : " << it->second << std::endl;
	}

	system("pause");
	delete[] theArray, arrayCopy;

	return 0;
}




