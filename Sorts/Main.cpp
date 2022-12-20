#include "utility.h"
#include "SeqList.h"
#include "Sort.h"

string sorts[] = {"", "��������", "ϣ������", "ð������", "ѡ������",
"�鲢����", "�������������ڽ���ʱ������", "�������������ڽ���ʱ�ƶ���",
"������"};
string dataSize[] = {"20", "200", "2000"};
string seqs[] = {"", "����", "����", "����"};

bool choice() {
	char op;
	cin >> op;
	if (op == 'Y' || op - 32 == 'Y') return true;
	else return false;
}

int createData(int n, int sequence = 0) {
	// sequence = 0 ���� 1 ���� -1 ����
	srand((unsigned)time(NULL));
	vector<int> data;
	for (int i = 0; i < n; i++) {
		data.push_back(rand() % 8000 - 4000);
	}
	string inseq = "inseq.txt";
	string rnd = "rnd.txt";
	string seq = "seq.txt";
	string path = "./data_";
	if (sequence > 0) {
		sort(data.begin(), data.end());
		path.append(seq);
	}
	else if (sequence < 0) {
		sort(data.begin(), data.end(), greater<int>());
		path.append(inseq);
	}
	else {
		path.append(rnd);
	}

	ofstream ofs;
	ofs.open(path.c_str(), ios::app);
	ofs.seekp(0, ios::end);
	if (!ofs) return 0;
	for (int i = 0; i < data.size(); i++) {
		ofs << data[i] << " ";
	}
	ofs << endl;
	return 1;
}

void instructor(bool &flag, int &type, int &n, int &seq) {
	cout << "��ӭ����������Գ���\n" 
		<< "����������ԱȽϸ��������㷨������" << endl;
	cout << "�Ƿ��Զ�ȫ���Ƚϣ�[Y/N]" << endl;
	if (choice()) {
		flag = true;
	}
	else {
		flag = false;
		cout << "��ѡ��������Ե������㷨��" << endl;
		cout << "1. ��������\n"
			<< "2. ϣ������\n"
			<< "3. ð������\n"
			<< "4. ѡ������\n"
			<< "5. �鲢����\n"
			<< "6. �������������ڽ���ʱ������\n"
			<< "7. �������������ڽ���ʱ�ƶ���\n"
			<< "8. ������" << endl;
		cin >> type;
		while (type > 8 || type <= 0) {
			cout << "�����������������룺";
			cin >> type;
		}

		cout << "��ѡ����������С��" << endl;
		cout << "1. 20\n"
			<< "2. 200\n"
			<< "3. 2000" << endl;
		cin >> n;
		while (n > 3 || n <= 0) {
			cout << "�����������������룺";
			cin >> n;
		}
		n -= 1;
		cout << "��ѡ���������ͣ�" << endl;
		cout << "1. ����\n"
			<< "2. ����\n"
			<< "3. ����" << endl;
		cin >> seq;
		while (seq > 3 || seq <= 0) {
			cout << "�����������������룺";
			cin >> seq;
		}
	}
}

int readData(string &path, vector<int> &v, int n) {
	// n = 0: 20, n = 1: 200, n = 2: 2000
	ifstream ifs;
	ifs.open(path.c_str());
	if (!ifs) {
		return 0;
	}
	int nn = n;
	while (nn --) {
		string str;
		getline(ifs, str);
	}
	int tmp;
	for (int i = 0; i < 20 * pow(10, n); i ++) {
		ifs >> tmp;
		v.push_back(tmp);
	}
	return 1;
}

void getTime(timeb& t) {
	ftime(&t);
}

int run(int type, int n, int seq) {
	timeb t1, t2;
	vector<int> data;
	string path;
	if (seq == 1) path = "./data_rnd.txt";
	else if (seq == 2) path = "./data_seq.txt";
	else path = "./data_inseq.txt";
	if (!readData(path, data, n)) {
		cout << "read in error" << endl;
		return 0;
	}
	SeqList l(data);

	string title = "===========" + sorts[type] + "��������" + dataSize[n] + " " + seqs[seq] + "==========";
	cout << title << endl;
	Sort::reset();
	getTime(t1);
	switch (type)
	{
	case 1:
		Sort::insertionSort(l);
		break;
	case 2:
		Sort::shellSort(l);
		break;
	case 3:
		Sort::bubbleSort(l);
		break;
	case 4:
		Sort::selectionSort(l);
		break;
	case 5:
		Sort::mergeSort(l, l.begin(), l.end());
		break;
	case 6:
		Sort::quickSort(l, l.begin(), l.end());
		break;
	case 7:
		Sort::quickSort2(l, l.begin(), l.end());
		break;
	case 8:
		Sort::heapSort(l);
		break;
	}
	getTime(t2);
	cout << ">��ʱ" << (t2.time - t1.time) * 1000 + t2.millitm - t1.millitm << "ms" << endl;
	cout << "�Ƚϴ�����" << Sort::getCmp() << endl;
	cout << "�ƶ�������" << Sort::getMove() << endl;
	cout << string(title.size(), '=') << endl;
	//l.print();
	return 1;
}

int main() {
	
	//if (createData(2000, 0)) {
	//	cout << "success" << endl;
	//}

	bool flag;
	int type, n, seq;
	instructor(flag, type, n, seq);

	if (flag) {
		for (int i = 0; i < 3; i ++) {
			for (int t = 1; t <= 8; t ++) {
				for (int s = 1; s <= 3; s ++) {
					if (run(t, i, s) == 0) {
						system("pause");
						return 0;
					}
				}
			}
		}
	}
	else {
		if (run(type, n, seq) == 0) {
			system("pause");
			return 0;
		}
	}

	//vector<int> data;
	//string path = "./data_rnd.txt";
	//if (!readData(path, data, 2)) {
	//	cout << "read in error" << endl;
	//	return 0;
	//}

	//int arr[] = {53, 7, 52, 1, 98, 10, 87, 25, 63, 46};

	//SeqList l(data);
	//cout << l.size() << endl;
	//l.print();
	//Sort::insertionSort(l);
	//Sort::shellSort(l);
	//Sort::bubbleSort(l);
	//Sort::selectionSort(l);
	//Sort::mergeSort(l, l.begin(), l.end());
	//Sort::quickSort(l, l.begin(), l.end());
	//cout << "here" << endl;
	//Sort::quickSort2(l, l.begin(), l.end());
	//Sort::heapSort(l);
	//l.print();
	system("pause");

	return 0;
}