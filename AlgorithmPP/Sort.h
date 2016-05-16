#pragma once
class Sort
{
private:
	static const int ARRAY_SIZE = 20000;

public:
	static void bubbleSort(int a[], int size);
	static void selectionSort(int a[], int size);
	static void insertionSort(int a[], int size);
	static void shellSort(int a[], int size);
	static void mergeSort(int a[], int size);
	static void quickSort(int a[], int right);
	static void randQuickSort(int a[], int size);

	static void merge(int a[], int l, int h);
	static void quickSort(int a[], int left, int right);
	static int partition(int a[], int left, int right);
	static void randQuick(int a[], int l, int h);
};
