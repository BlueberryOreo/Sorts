#include "utility.h"
#include "SeqList.h"
#include "Sort.h"

string sorts[] = {"", "插入排序", "希尔排序", "冒泡排序", "选择排序",
"归并排序", "快速排序（枢轴在交换时不动）", "快速排序（枢轴在交换时移动）",
"堆排序"};
string dataSize[] = {"20", "200", "2000"};
string seqs[] = {"", "无序", "升序", "降序"};

bool choice() {
	char op;
	cin >> op;
	if (op == 'Y' || op - 32 == 'Y') return true;
	else return false;
}

int createData(int n, int sequence = 0) {
	// sequence = 0 无序； 1 正序； -1 逆序
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
	cout << "欢迎来到排序测试程序\n" 
		<< "在这里你可以比较各类排序算法的性能" << endl;
	cout << "是否自动全部比较？[Y/N]" << endl;
	if (choice()) {
		flag = true;
	}
	else {
		flag = false;
		cout << "请选择你想测试的排序算法：" << endl;
		cout << "1. 插入排序\n"
			<< "2. 希尔排序\n"
			<< "3. 冒泡排序\n"
			<< "4. 选择排序\n"
			<< "5. 归并排序\n"
			<< "6. 快速排序（枢轴在交换时不动）\n"
			<< "7. 快速排序（枢轴在交换时移动）\n"
			<< "8. 堆排序" << endl;
		cin >> type;
		while (type > 8 || type <= 0) {
			cout << "输入有误，请重新输入：";
			cin >> type;
		}

		cout << "请选择数据量大小：" << endl;
		cout << "1. 20\n"
			<< "2. 200\n"
			<< "3. 2000" << endl;
		cin >> n;
		while (n > 3 || n <= 0) {
			cout << "输入有误，请重新输入：";
			cin >> n;
		}
		n -= 1;
		cout << "请选择数据类型：" << endl;
		cout << "1. 无序\n"
			<< "2. 升序\n"
			<< "3. 降序" << endl;
		cin >> seq;
		while (seq > 3 || seq <= 0) {
			cout << "输入有误，请重新输入：";
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

	string title = "===========" + sorts[type] + "，数据量" + dataSize[n] + " " + seqs[seq] + "==========";
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
	cout << ">耗时" << (t2.time - t1.time) * 1000 + t2.millitm - t1.millitm << "ms" << endl;
	cout << "比较次数：" << Sort::getCmp() << endl;
	cout << "移动次数：" << Sort::getMove() << endl;
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