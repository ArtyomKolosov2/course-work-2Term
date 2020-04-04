#include <iostream>
#include <fstream>

using namespace std;

const char path[100] = "C:\\Users\\User\\myfile.txt";

const int nl = 10;
const int ns = 10;
const int nw = 30;


struct list {
	char str[nw];
	unsigned int count;
	list* next;
};

int main() {
	system("chcp 1251 > nul");
	bool flag = false;
	char text[nl * ns * nw]{};
	char buf;
	fstream infile(path, ios::in);
	if (!infile) {
		cout << "Error: Файл не найден!\n";
		return 1;
	}
	int index = 0;
	while (!infile.eof()) {
		text[index] = infile.get();
		if (text[index] == '.') {
			break;
		}
		index++;
	}

	text[index] = '\0';
	cout << text << endl;
	infile.close();
	return 0;
}