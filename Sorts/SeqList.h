#pragma once
#include "utility.h"

class SeqList {
protected:
	int* list;
	int l_size;
public:
	SeqList();
	SeqList(int *arr, int n);
	SeqList(vector<int> &v);
	SeqList(const SeqList &l);
	~SeqList();

	int begin();
	int end();
	void sort(int start, int end);

	int& operator[](int i);
	SeqList& operator=(const SeqList &l);
	int size();
	void print();
};