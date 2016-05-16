// Main.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"

const int ORDER = 32;


void strassen(){
	Matrix *a = new Matrix(true, ORDER);
	Matrix *b = new Matrix(true, ORDER);
	a->print("A");
	b->print("B");

	Matrix c = (*a) * (*b);
	c.print("C = A * B (using strassen algorithm)");

	Matrix::multiplication(*a, *b)->print("C = A * B (using standard multiplication algorithm)");
}

void sort(){
}

void karatsuba() {
	BigInt *a = new BigInt;
	BigInt *b = new BigInt;

	BigInt *c = (*a) * (*b);
	c->print();
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
			//mergeSort();
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

