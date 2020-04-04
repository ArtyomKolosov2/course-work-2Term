#include <iostream>
#include <fstream>

using namespace std;

const char path[100] = "C:\\Users\\User\\myfile.txt";

const int nl = 10;
const int ns = 10;
const int nw = 30;


struct list {
	char str[nw]{};
	unsigned int count;
	list* next;
};

list* add_to_list(list*, int k);

int get_length(list*);

void print_list(list*);

void delete_list(list*);

bool isalpha_mod(char);

bool ispunct_end(char);

int main() {
	system("chcp 1251 > nul");
	bool flag = true;
	char text[nl * ns * nw]{};

	list* beg = new list;
	beg->next = NULL;
	list* point = beg;

	fstream infile(path, ios::in);
	if (!infile) {
		cout << "Error: Файл не найден!\n";
		return 1;
	}
	int index = 0;
	while (!infile.eof()) {
		text[index] = infile.get();
		if (ispunct_end(text[index])) {
			break;
		}
		index++;
	}
	index = 0;
	for (int i = 0; text[i]; i++) {
		if (isalpha_mod((unsigned char)text[i])) {
			if (flag) {
				beg = add_to_list(beg, get_length(beg));
				flag = false;
			}
			point->str[index] = text[i];
			index++;
		}
		else if (!flag){
			flag = true;
			point->str[index] = '\0';
			index = 0;
			point = point->next;
		}
	}
	print_list(beg);
	delete_list(beg);
	infile.close();
	return 0;
}

list* add_to_list(list* beg, int k) {
	list* pnew = new list;
	list* point = beg;
	if (k == 0) {
		pnew->next = beg;
		beg = pnew;
		return beg;
	}
	for (int i = 0; i < k - 1 && point; i++) {
		point = point->next;
	}
	if (point) {
		if (!point->next) {
			pnew->next = NULL;
		}
		else {
			pnew->next = point->next;
		}
		point->next = pnew;
	}
	return beg;
}

void delete_list(list* beg) {
	list* point = beg;
	list* del;
	while (point) {
		del = point;
		point = point->next;
		delete del;
	}
	delete point;
}

int get_length(list* beg) {
	list* point = beg;
	int length = 0;
	while (point) {
		point = point->next;
		length++;
	}
	return length;
}

void print_list(list* beg) {
	list* point = beg;
	cout << "Содержимое списка:\n";
	while (point) {
		cout << point->str << endl;
		point = point->next;
	}
}

bool isalpha_mod(char c) {
	return c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я'
		|| c == 'ё' || c == 'Ё' || isalpha((unsigned char)c); 
}

bool ispunct_end(char c) {
	char check_symb[] = "!?.";
	for (int i = 0; check_symb[i]; i++) {
		if (check_symb[i] == (unsigned char)c) {
			return true;
		}
	}
	return false;
}