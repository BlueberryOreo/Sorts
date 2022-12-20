#include "SeqList.h"

SeqList::SeqList()
{
	list = new int[N];
	l_size = 0;
}

SeqList::SeqList(int* arr, int n)
{
	list = new int[n];
	l_size = n;
	for (int i = 0; i < n; i ++) {
		list[i] = arr[i];
	}
}

SeqList::SeqList(vector<int>& v)
{
	l_size = v.size();
	list = new int[l_size];
	for (int i = 0; i < l_size; i ++) {
		list[i] = v[i];
	}
}

SeqList::SeqList(const SeqList& l)
{
	*this = l;
}

SeqList::~SeqList()
{
	delete[] list;
}

int SeqList::begin()
{
	return 0;
}

int SeqList::end()
{
	return l_size;
}

void SeqList::sort(int start, int end)
{
	if (start >= end) return;
	int last_small = start;
	for (int i = start + 1; i < end; i++) {
		if (list[i] < list[start]) {
			last_small++;
			swap(list[i], list[last_small]);
		}
	}
	swap(list[start], list[last_small]);
	sort(start, last_small);
	sort(last_small + 1, end);
}

int& SeqList::operator[](int i)
{
	return list[i];
}

SeqList& SeqList::operator=(const SeqList& l)
{
	l_size = l.l_size;
	if (list) delete[] list;
	list = new int[l_size];
	for (int i = 0; i < l_size; i ++) {
		list[i] = l.list[i];
	}
	return *this;
}

int SeqList::size()
{
	return l_size;
}

void SeqList::print()
{
	for (int i = 0; i < l_size; i ++) {
		cout << list[i] << " ";
	}
	cout << endl;
}
