// Dimitri BUHON
// Main.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"

typedef void(*FPTR)(int*, int);
enum SortEnum { BUBBLE, SELECTION, INSERTION, SHELL, MERGE, QUICKSORT, RANDQUICKSORT, RADIX, HEAPSORT, STL_SORT, STL_STABLESORT, STL_SORTHEAP, EndEnum };
enum SortType { NON_SORTED, SORTED, REVERSED_SORTED };

std::map<SortEnum, FPTR> sort;

std::chrono::high_resolution_clock::time_point timerStart, timerStop;
std::chrono::duration<double> time_span;
int ARRAY_SIZE = 100000;

void strassen();
void karatsuba();
void sortDisplay();
void sortAverageTime(SortType sortType);
std::string toString(SortEnum sortEnum);
void initSortMap();
void initResultList(std::list<std::pair<SortEnum, double>> *list);
void fillArray(int *a);
void printArray(int *a, int size, std::string message = "");
int* copy(int*, int*);
double execution(int*, SortEnum, bool display);

inline bool is_number(const std::string& s){
	return count_if(s.begin(), s.end(), isdigit) == s.size();
}

void strassen(){
	std::string input;
	std::cout << "   Choisir un ordre n : ";
	while (!(std::cin >> input) || !is_number(input)){
		std::cerr << "   Erreur de saisie" << std::endl;
		std::cout << "   Choisir un ordre n : ";
	}

	Matrix *a = new Matrix(true, std::stoi(input));
	Matrix *b = new Matrix(true, std::stoi(input));
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
double execution(int* _array, int* arrayCopy, SortEnum sortEnum, bool display = false){
	if (display){
		std::cout << std::endl << std::endl << "***** " << toString(sortEnum) << " *****" << std::endl;
		printArray(_array, ARRAY_SIZE, "Unsorted list :");
	}

	double timeSpan = 0;
	int i = 1;
	int maxIterations = ARRAY_SIZE < 5000 ? 100 : 1;
	maxIterations = ARRAY_SIZE < 500 ? 1000 : 1;

	// Execute the algorithm i times with the same array to improve the timer precision
	for (i = 1; i <= maxIterations; i++){
		copy(_array, arrayCopy);

		timerStart = std::chrono::high_resolution_clock::now();

		sort[sortEnum](arrayCopy, ARRAY_SIZE);

		timerStop = std::chrono::high_resolution_clock::now();
		time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(timerStop - timerStart);
		timeSpan += time_span.count();
	}

	if (display) {
		printArray(arrayCopy, ARRAY_SIZE, "Sorted list : ");
		std::cout << "(" << timeSpan / i << " ticks)" << std::endl << std::endl;
	}

	return (timeSpan / i);
}

void sortAverageTime(SortType sortType = NON_SORTED){
	int n = 1000;
	std::vector<int> vector = {1, 2, 3, 5, 7, 10, 100};
	// Use different size of arrays
	for (auto it = vector.begin(); it != vector.end(); ++it){
		ARRAY_SIZE = *it * n;
		int* theArray = new int[ARRAY_SIZE], *arrayCopy = new int[ARRAY_SIZE];
		std::list<std::pair<SortEnum, double>> resultList;
		initResultList(&resultList);

		std::cout << std::endl << std::endl << "|||||||||| ARRAY OF " << *it * n << " ELEMENTS ||||||||||" << std::endl;

		// Generate a new array and sort it with each algorithm i times
		for (int i = 0; i < 10; i++){
			fillArray(theArray);

			if (sortType == SORTED)
				execution(theArray, theArray, SortEnum::STL_SORTHEAP);
			else if (sortType == REVERSED_SORTED)
				std::sort(theArray, &theArray[ARRAY_SIZE - 1], std::greater<int>());

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

void sortDisplay(){
	std::string input, options;
	std::cout << std::endl << std::endl << "   Choisir une option : " << std::endl;

	int sortEnum = 0;
	for (sortEnum = 0; sortEnum != EndEnum; sortEnum++){
		options.append("&" + std::to_string(sortEnum));
		SortEnum en = static_cast<SortEnum>(sortEnum);
		std::cout << "   " << sortEnum << " - " << toString(en) << std::endl;
	}
	std::cout << "   " << sortEnum << " - Temps moyens" << std::endl;
	std::cin >> input;
	
	if (options.find("&" + input) != std::string::npos){
		ARRAY_SIZE = 100;
		int* theArray = new int[ARRAY_SIZE];
		int* arrayCopy = new int[ARRAY_SIZE];

		fillArray(theArray);

		execution(theArray, arrayCopy, static_cast<SortEnum>(std::stoi(input)), true);

		delete[] theArray, arrayCopy;
	}
	else {
		std::cout << "   Choisir la maniere dont les elements seront disposes dans le tableau :" << std::endl
			<< "0 - Non tries" << std::endl
			<< "1 - Tries" << std::endl
			<< "2 - Tries inverses" << std::endl;

		std::cin >> input;
		if (input == "1")
			sortAverageTime(SortType::SORTED);
		else if (input == "2")
			sortAverageTime();
		else
			sortAverageTime(SortType::NON_SORTED);
	}
}

int _tmain(int argc, _TCHAR* argv[]){
	initSortMap();

	std::cout << "TP1 - Dimitri BUHON" << std::endl;
	std::string input;
	while (input != "q"){
		std::cout << std::endl << "Choisir une option : " << std::endl
			<< "1 - Strassen" << std::endl
			<< "2 - Tri" << std::endl
			<< "3 - Karatsuba" << std::endl
			<< "q - Quitter" << std::endl << std::endl;

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

