// Dimitri BUHON - Algorithmes de tri

#include "stdafx.h"
#include "Sort.h"

//BUBBLE SORT
void Sort::bubbleSort(int a[], int size){
	int outer, inner;
	for (outer = size; outer > 0; --outer){
		for (inner = 0; inner < outer - 1; ++inner){
			if (a[inner] > a[inner + 1]){
				int tmp = a[inner];
				a[inner] = a[inner + 1];
				a[inner + 1] = tmp;
			}
		}
	}
}

//SELECTION SORT
void Sort::selectionSort(int a[], int size){
	int outer, inner, min;
	for (outer = 0; outer < size - 1; ++outer)	{
		min = outer;
		for (inner = outer + 1; inner < size; ++inner){
			if (a[inner] < a[min]){
				min = inner;
			}
		}

		int tmp = a[outer];
		a[outer] = a[min];
		a[min] = tmp;
	}
}

//INSERTION SORT
void Sort::insertionSort(int a[], int size){
	int i, j, tmp;
	for (i = 1; i < size; ++i){
		j = i;

		while (j > 0 && a[j - 1] > a[j]){
			tmp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = tmp;
			--j;
		}
	}
}

//SHELL SORT
void Sort::shellSort(int a[], int size){
	int i, j, increment, tmp;
	for (increment = size / 2; increment > 0; increment /= 2){
		for (i = increment; i<size; ++i){
			tmp = a[i];
			for (j = i; j >= increment; j -= increment){
				if (tmp < a[j - increment])
					a[j] = a[j - increment];
				else
					break;
			}
			a[j] = tmp;
		}
	}
}


//QUICK SORT
void Sort::quickSort(int a[], int right){
	return Sort::quickSort(a, 0, right);
}

void Sort::quickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int pivotIndex = partition(a, left, right);

		quickSort(a, left, pivotIndex - 1);
		quickSort(a, pivotIndex + 1, right);
	}
}


int Sort::partition(int a[], int left, int right)
{
	int p = left, pivot = a[left], location;

	for (location = left + 1; location <= right; location++){
		if (pivot > a[location]){
			a[p] = a[location];
			a[location] = a[p + 1];
			a[p + 1] = pivot;

			p++;
		}
	}
	return p;
}


// RAND QUICK SORT
void swap(int& a, int& b) {
	int t = b;
	b = a;
	a = t;
}

void Sort::randQuick(int a[], int left, int right) {
	if (right > left) {
		// partition
		int p = rand() % (right - left) + left;
		int d = a[p];
		// divide
		swap(a[left], a[p]);
		int i = left;
		int j = i + 1;
		while (j < right) {
			while (a[j] > d && j < right) j++;
			if (j < right) {
				i++;
				swap(a[i], a[j]);
				j++;
			}
		}
		swap(a[i], a[left]);
		randQuick(a, left, i);
		randQuick(a, i + 1, right);
	}
}

void Sort::randQuickSort(int a[], int size) {
	randQuick(a, 0, size);
}



// MERGE SORT
void Sort::merge(int a[], int left, int right) {
	if (right - left == 1) {
		if (a[left] > a[right]) {
			int t = a[left];
			a[left] = a[right];
			a[right] = t;
		}
	}
	else if (right != 1 && right > left) {
		int size = right - left + 1;
		int m = left + (right - left) / 2;
		merge(a, left, m);
		merge(a, m + 1, right);
		int* b = new int[size];
		int k = 0;
		int i = left;
		int j = m + 1;
		while (i <= m && j <= right)
			if (a[i] <= a[j])
				b[k++] = a[i++];
			else
				b[k++] = a[j++];

		while (i <= m)
			b[k++] = a[i++];

		while (j <= right)
			b[k++] = a[j++];

		for (k = 0; k < size; k++)
			a[left + k] = b[k];
	
		delete[] b;
	}
}

void Sort::mergeSort(int a[], int size) {
	merge(a, 0, size - 1);
}


// HEAP
void Sort::maxHeapify(int a[], int size, int i) {
	int left = (i + 1) * 2 - 1;
	int right = (i + 1) * 2;
	int largest = i;
	if (left < size && a[left] > a[largest])
		largest = left;
	if (right < size && a[right] > a[largest])
		largest = right;
	if (largest != i) {
		swap(a[i], a[largest]);
		maxHeapify(a, size, largest);
	}
}

void Sort::buildMaxHeap(int a[], int size) {
	for (int i = size / 2; i >= 0; i--) {
		maxHeapify(a, size, i);
	}
}

void Sort::heapSort(int a[], int size) {
	buildMaxHeap(a, size);
	int heap_size = size;
	for (int i = size - 1; i > 0; i--) {
		swap(a[0], a[i]);
		heap_size--;
		maxHeapify(a, heap_size, 0);
	}
}


// RADIX
int Sort::radixGetMax(int a[], int n){
	int mx = a[0];
	for (int i = 1; i < n; i++)
		if (a[i] > mx)
			mx = a[i];

	return mx;
}

void Sort::radixCountSort(int a[], int n, int exp, int size){
	int *output = new int[n];
	int i;
	int count[10];

	for (int j = 0; j < 10; j++){
		count[j] = 0;
	}

	for (i = 0; i < n; i++)
		count[(a[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = size - 1; i >= 0; i--){
		output[count[(a[i] / exp) % 10] - 1] = a[i];
		count[(a[i] / exp) % 10]--;
	}

	for (i = 0; i < n; i++)
		a[i] = output[i];

	delete[]output;
}

void Sort::radixSort(int a[], int size){
	int m = radixGetMax(a, size);
	for (int exp = 1; m / exp > 0; exp *= 10)
		radixCountSort(a, size, exp, size);
}



//// SORT
void Sort::sort(int a[], int size){
	std::sort(a, &a[size - 1]);
}


// STABLE SORT
void Sort::stableSort(int a[], int size){
	std::stable_sort(a, &a[size - 1]);
}


// SORT HEAP
void Sort::sortHeap(int a[], int size){
	std::sort_heap(a, &a[size - 1]);
}

