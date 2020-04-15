#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char path_in[100] = "C:\\Users\\User\\myfile.txt";
const char path_out[100] = "C:\\Users\\User\\outfile.txt";

const int nl = 10,
		  ns = 10,
		  nw = 30;


struct list {
	char str[nw]{};
	unsigned int count = 0;
	list* next = nullptr;
};

list* add_to_list(list*, int );

list* list_with_repetation(list*, int);

list* delete_last_element(list*);

char* fill_from_file(fstream&);

void print_list(list*);

void delete_list(list*);

void find_element_by_index(list*, int);

void count_each_word(list*);

void fill_list_from_str(list*, char[]);

void add_info_to_file(list*, fstream&, char *);

void add_info_to_file(list*, fstream&);

int find_list_element(list*, char*);

int get_length(list*);

bool isalpha_mod(char);

bool ispunct_end(char);

int main() {
	system("chcp 1251 > nul");
	bool flag = true;
	list* beg = new list;

	fstream infile(path_in, ios::in);
	if (!infile) {
		cout << "Error: Файл не найден!\n";
		return 1;
	}
	char num[10];
	infile.getline(num, 10);
	int word_num = atoi(num);
	cout << word_num << endl;
	char *text = fill_from_file(infile);

	fill_list_from_str(beg, text);

	count_each_word(beg);

	print_list(beg);

	list* beg_rep = list_with_repetation(beg, word_num);

	print_list(beg_rep);

	fstream outfile(path_out, ios::out);

	add_info_to_file(beg, outfile, text);
	add_info_to_file(beg_rep, outfile);
	outfile.close();

	delete_list(beg);
	delete_list(beg_rep);
	delete[] text;
	return 0;
}
char* fill_from_file(fstream& infile) {
	char* text = new char[nw * ns * nl]{};
	int index = 0;
	while (!infile.eof()) {
		text[index] = infile.get();
		if (ispunct_end(text[index])) {
			text[index] = '\0';
			break;
		}
		index++;
	}
	infile.close();
	return text;
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

list* list_with_repetation(list* beg, int word_num) {
	list *beg_rep = new list;
	list* point = beg;
	list* point_rep = beg_rep;
	while (point) {
		if (point->count == word_num) {
			strcpy_s(point_rep->str, point->str);
			point_rep->count = point->count;
			beg_rep = add_to_list(beg_rep, get_length(beg_rep));
			point_rep = point_rep->next;
		}
		point = point->next;
	}
	if (!point_rep->count) {
		beg_rep = delete_last_element(beg_rep);
	}
	return beg_rep;
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

void fill_list_from_str(list* beg, char text[]) {
	list *point = beg;
	bool flag = true;
	int index = 0;
	for (int i = 0; text[i]; i++) {
		if (isalpha_mod((unsigned char)text[i])) {
			flag = false;
			point->str[index] = text[i];
			index++;
		}
		else if (!flag) {
			beg = add_to_list(beg, get_length(beg));
			flag = true;
			point->str[index] = '\0';
			index = 0;
			point = point->next;

		}
	}
	point->str[index] = '\0';
}

void add_info_to_file(list* beg, fstream& outfile, char *text) {
	list* point = beg;
	outfile << text << endl;
	while (point) {
		outfile << point->str << " " << point->count << endl;
		point = point->next;
	}
}

void add_info_to_file(list* beg, fstream& outfile) {
	list* point = beg;
	outfile << "\nСлова с повторением:\n";
	while (point) {
		outfile << point->str << " " << point->count << endl;
		point = point->next;
	}
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