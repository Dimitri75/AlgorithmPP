#include "stdafx.h"

typedef void(*FPTR)(int*, int);
enum SortEnum { BUBBLE, SELECTION, INSERTION, SHELL, MERGE, QUICKSORT, RANDQUICKSORT };
std::map<SortEnum, FPTR> sort;

void execution(int*, SortEnum);
void printArray(int *a, int size, std::string message = "");
void fillArray();


const int MAX = 999;
const int ARRAY_SIZE = 10;
int theArray[ARRAY_SIZE];
int temp[ARRAY_SIZE];

std::string toString(SortEnum sortEnum){
	switch (sortEnum){
	case BUBBLE :
		return "Bubble Sort";
		break;
	case SELECTION :
		return "Selection Sort";
		break;
	case INSERTION :
		return "Insertion Sort";
		break;
	case SHELL:
		return "Shell Sort";
		break;
	case MERGE:
		return "Merge Sort";
		break;
	case QUICKSORT:
		return "Quick Sort";
		break;
	case RANDQUICKSORT :
		return "Random Quick Sort";
		break;
	default :
		return "Sort";
		break;
	}
}

void initSortMap(){
	sort[BUBBLE] = &Sort::bubbleSort;
	sort[SELECTION] = &Sort::selectionSort;
	sort[INSERTION] = &Sort::insertionSort;
	sort[SHELL] = &Sort::shellSort;
	sort[MERGE] = &Sort::mergeSort;
	sort[QUICKSORT] = &Sort::quickSort;
	sort[RANDQUICKSORT] = &Sort::randQuickSort;
}

void execution(int* _array, SortEnum sortEnum){
	int size = sizeof(theArray) / sizeof(_array[0]);

	std::cout << std::endl << std::endl << "***** " << toString(sortEnum) << " *****" << std::endl;
	printArray(_array, size, "Unsorted list :");

	std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
		sort[sortEnum](_array, size);
	std::chrono::high_resolution_clock::time_point timeStop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);

	printArray(_array, ARRAY_SIZE, "Sorted list : ");
	std::cout << "(" << time_span.count() << " ticks)" << std::endl << std::endl;
}

void printArray(int* a, int size, std::string message)
{
	std::cout << message << std::endl;

	for (int i = 0; i < ARRAY_SIZE; ++i)
		std::cout << a[i] << " ";
	std::cout << std::endl << std::endl;
}

void fillArray()
{
	std::random_device seeder;
	std::mt19937 engine(seeder());;

	for (int i = 0; i < ARRAY_SIZE; ++i){
		std::uniform_int_distribution<int> dist(0, MAX);
		temp[i] = dist(engine);
	}

	std::copy(&temp[0], &temp[ARRAY_SIZE - 1], theArray);
}

int* copy(int* a){
	int *r = new int[ARRAY_SIZE];
	for (int i = 0; i <= ARRAY_SIZE; ++i)
		r[i] = a[i];
	return r;
}

int main(){
	initSortMap();
	fillArray();

	execution(copy(theArray), BUBBLE);
	execution(copy(theArray), SELECTION);
	execution(copy(theArray), INSERTION);
	execution(copy(theArray), SHELL);
	execution(copy(theArray), MERGE);
	execution(copy(theArray), RANDQUICKSORT);
	//execution(theArray, QUICKSORT);

	system("pause");

	return 0;
}