#include <iostream>
#include <fstream>

using namespace std;

const char path[100] = "C:\\Users\\User\\myfile.txt";

const int nl = 10,
		  ns = 10,
		  nw = 30;


struct list {
	char str[nw];
	unsigned int count = 0;
	list* next;
};

list* add_to_list(list*, int k);

list* delete_last_element(list*);

int get_length(list*);

void print_list(list*);

void delete_list(list*);

void find_element_by_index(list*, int);

void count_each_word(list*);

int find_list_element(list*, char*);

bool isalpha_mod(char);

bool ispunct_end(char);

int main() {
	system("chcp 1251 > nul");
	bool flag = true;
	char text[nl * ns * nw]{};

	list* beg = new list;
	beg->next = nullptr;
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
			text[index] = '\0';
			break;
		}
		index++;
	}
	cout << text << endl;
	index = 0;
	int c = 0;
	print_list(beg);
	for (int i = 0; i < strlen(text)+1; i++) {
		if (isalpha_mod((unsigned char)text[i])) {
			if (flag){
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
	beg = delete_last_element(beg);
	count_each_word(beg);
	print_list(beg);
	find_element_by_index(beg, get_length(beg)-1);
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
		pnew->next = point->next;
		point->next = pnew;
	}
	return beg;
}

list* delete_last_element(list* beg) {
	list* point = beg;
	list* del;
	int k = get_length(beg) - 1;
	int len = 0;
	while (point) {
		if (len + 1 == k) {
			delete point->next;
			point->next = nullptr;
			return beg;
		}
		len++;
		point = point->next;
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

void count_each_word(list* beg) {
	list* point = beg;
	while (point) {
		point->count = find_list_element(beg, point->str);
		point = point->next;
	}
}

void print_list(list* beg) {
	list* point = beg;
	cout << "Содержимое списка:\n";
	while (point) {
		cout << point->str <<" "<<point->count << endl;
		point = point->next;
	}
}

void find_element_by_index(list* beg, int index) {
	list* point = beg;
	int length = 0;
	while (point) {
		if (length == index) {
			cout << "Ваш элемент: " << point->str << endl;
			return;
		}
		length++;
		point = point->next;
		
	}
	cout << "Элемент не найден!\n";
}

int find_list_element(list* beg, char *str) {
	list* point = beg;
	int count = 0;
	while (point) {
		if (!strcmp(point->str, str)) {
			count++;
		}
		point = point->next;
	}
	return count;
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