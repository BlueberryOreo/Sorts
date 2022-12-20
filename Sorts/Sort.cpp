#include "Sort.h"

int Sort::cmpCnt = 0;
int Sort::moveCnt = 0;

void Sort::shiftDown(SeqList &list, int i, int tmpSize)
{
	// i：要调整的位置  tmpSize：堆的大小
	while (2 * i + 1 < tmpSize || 2 * i + 2 < tmpSize) {
		int lChild = 0, rChild = 0;
		if (2 * i + 1 < tmpSize) lChild = 2 * i + 1;
		if (2 * i + 2 < tmpSize) rChild = 2 * i + 2;
		cmpCnt++;
		if (lChild && rChild) {
			if (list[lChild] > list[i] && list[rChild] > list[i]) {
				if (list[lChild] > list[rChild]) {
					swap(list[lChild], list[i]);
					moveCnt++;
					i = lChild;
				}
				else {
					swap(list[rChild], list[i]);
					moveCnt++;
					i = rChild;
				}
				continue;
			}
		}
		if (lChild && list[lChild] > list[i]) {
			swap(list[lChild], list[i]);
			moveCnt++;
			i = lChild;
		}
		else if (rChild && list[rChild] > list[i]) {
			swap(list[rChild], list[i]);
			moveCnt++;
			i = rChild;
		}
		else {
			break;
		}
	}
}

void Sort::createHeap(SeqList &list)
{
	// 创建大根堆
	for (int i = list.size() / 2 + 1; i >= 0; i--) {
		shiftDown(list, i, list.size());
	}
}

int Sort::Partition(SeqList &list, int start, int end)
{
	int i = start;
	int j = end - 1;
	while (i < j) {
		cmpCnt++;
		while (i < j && list[i] <= list[j]) j--, cmpCnt++;
		if (i < j) {
			swap(list[i], list[j]);
			moveCnt++;
			i++;
		}
		cmpCnt++;
		while (i < j && list[i] <= list[j]) i++, cmpCnt++;
		if (i < j) {
			swap(list[i], list[j]);
			moveCnt++;
			j--;
		}
	}
	return i;
}

void Sort::merge(SeqList &list, int s1, int s2, int end)
{
	int i = s1, j = s2;
	vector<int> tmp;
	while (i < s2 && j < end) {
		cmpCnt++;
		if (list[i] < list[j]) {
			tmp.push_back(list[i]);
			i++;
		}
		else {
			tmp.push_back(list[j]);
			j++;
		}
	}
	while (i < s2) tmp.push_back(list[i]), i++;
	while (j < end) tmp.push_back(list[j]), j++;
	//for (int k = 0; k < tmp.size(); k ++) {
	//	cout << tmp[k] << " ";
	//}
	//cout << endl;
	for (int k = 0; k < tmp.size(); k++) list[s1 + k] = tmp[k], moveCnt++;
}

void Sort::insertionSort(SeqList& list)
{
	for (int i = 0; i < list.size(); i++) {
		int j = i;
		cmpCnt++;
		while (j - 1 >= 0 && list[j] < list[j - 1]) {
			cmpCnt++;
			swap(list[j], list[j - 1]);
			moveCnt++;
			j--;
		}
	}
}

void Sort::shellSort(SeqList& list)
{
	int d = list.size() / 2;
	while (d > 0) {
		// 分组
		for (int i = 0; i < d; i++) {
			// 各分组插入排序
			for (int j = i; j < list.size(); j += d) {
				int k = j;
				cmpCnt++;
				while (k - d >= 0 && list[k] < list[k - d]) {
					cmpCnt++;
					swap(list[k], list[k - d]);
					moveCnt++;
					k -= d;
				}
			}
		}
		//cout << d << endl;
		d /= 2;
	}
}

void Sort::bubbleSort(SeqList& list)
{
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list.size() - i - 1; j++) {
			cmpCnt++;
			if (list[j + 1] < list[j]) {
				swap(list[j + 1], list[j]);
				moveCnt++;
			}
		}
	}
}

void Sort::selectionSort(SeqList& list)
{
	for (int i = 0; i < list.size(); i++) {
		int minj = i;
		for (int j = i; j < list.size(); j++) {
			cmpCnt++;
			if (list[j] < list[minj]) {
				minj = j;
			}
		}
		swap(list[i], list[minj]);
		moveCnt++;
	}
}

void Sort::mergeSort(SeqList& list, int start, int end)
{
	if (start >= end - 1) {
		return;
	}
	//cout << start << " " << end << endl;
	int mid = (start + end) / 2;
	mergeSort(list, start, mid);
	mergeSort(list, mid, end);
	merge(list, start, mid, end);
}

void Sort::quickSort(SeqList& list, int start, int end)
{
	// 方法1
	// 枢轴不动，全部交换结束再调整枢轴
	//cout << start << " " << end << endl;
	if (start >= end) return;
	// list[start]: 枢轴元素
	/*
	int last_small = start;
	for (int i = start + 1; i < end; i++) {
		cmpCnt++;
		if (list[i] < list[start]) {
			last_small++;
			swap(list[i], list[last_small]);
			moveCnt++;
		}
	}
	*/
	// 枢轴的选择对排序性能的影响，写到实验报告中
	swap(list[start], list[(start + end) >> 1]);
	int i = start, j = end - 1;
	while (i < j) {
		cmpCnt++;
		while (i < j && list[j] >= list[start]) j--, cmpCnt++;
		cmpCnt++;
		while (i < j && list[i] <= list[start]) i++, cmpCnt++;
		if (i < j) swap(list[i], list[j]);
		moveCnt++;
	}
	swap(list[start], list[i]);
	//if(start != last_small) moveCnt++;
	if (start != i) moveCnt++;
	quickSort(list, start, i);
	quickSort(list, i + 1, end);
}

void Sort::quickSort2(SeqList& list, int start, int end)
{
	// 方法2
	// 枢轴在交换的时候就动
	if (start >= end) return;
	int nxtStart = Partition(list, start, end);
	quickSort2(list, start, nxtStart);
	quickSort2(list, nxtStart + 1, end);
}

void Sort::heapSort(SeqList& list)
{
	createHeap(list); // 创建大根堆
	int i = list.size() - 1;
	while (i > 0) {
		swap(list[0], list[i]);
		moveCnt++;
		i--;
		shiftDown(list, 0, i + 1);
	}
}

int Sort::getCmp()
{
	return cmpCnt;
}

int Sort::getMove()
{
	return moveCnt;
}

void Sort::reset()
{
	cmpCnt = 0;
	moveCnt = 0;
}
