#pragma once
#include "SeqList.h"
class Sort
{
private:
	static void shiftDown(SeqList &list, int i, int tmpSize);
	static void createHeap(SeqList &list);
	static int Partition(SeqList &list, int start, int end);
	static void merge(SeqList &list, int s1, int s2, int end);
	static int cmpCnt, moveCnt;

public:
	static void insertionSort(SeqList &list);
	static void shellSort(SeqList &list);
	static void bubbleSort(SeqList &list);
	static void selectionSort(SeqList &list);
	static void mergeSort(SeqList &list, int start, int end);
	static void quickSort(SeqList &list, int start, int end);
	static void quickSort2(SeqList &list, int start, int end);
	static void heapSort(SeqList &list);

	static int getCmp();
	static int getMove();
	static void reset();
};
