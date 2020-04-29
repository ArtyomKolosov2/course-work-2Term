#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char path_in[100] = "C:\\Users\\User\\myfile.txt";
const char path_out[100] = "C:\\Users\\User\\outfile.txt";

const int nl = 10,
		  ns = 10,
		  nw = 30;


struct text_list {
	char str[nw]{};
	unsigned int count = 0;
	text_list* next = nullptr;

};

text_list* add_to_list(text_list*, int );

text_list* list_with_repetation(text_list*, int);

text_list* delete_last_element(text_list*);

char* fill_from_file(fstream&);

void print_list(text_list*);

void delete_list(text_list*);

void find_element_by_index(text_list*, int);

void count_each_word(text_list*);

void fill_list_from_str(text_list*, char[]);

void add_info_to_file(text_list*, fstream&, char *);

void add_info_to_file(text_list*, fstream&);

int count_element_rep(text_list*, char*);

int get_length(text_list*);

bool isalpha_mod(char);

bool ispunct_end(char);

bool find_list_element(text_list*, char*);

int main() {
	system("chcp 1251 > nul");
	bool flag = true;
	text_list* beg = new text_list;

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

	text_list* beg_rep = list_with_repetation(beg, word_num);

	print_list(beg_rep);

	fstream outfile(path_out, ios::out);

	outfile << word_num << endl;
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
text_list* add_to_list(text_list* beg, int k) {
	text_list* pnew = new text_list;
	text_list* point = beg;
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

text_list* list_with_repetation(text_list* beg, int word_num) {
	text_list *beg_rep = new text_list;
	text_list* point = beg;
	text_list* point_rep = beg_rep;
	while (point) {
		if (point->count == word_num && !find_list_element(beg_rep, point->str)) {
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

text_list* delete_last_element(text_list* beg) {
	text_list* point = beg;
	text_list* del;
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

void fill_list_from_str(text_list* beg, char text[]) {
	text_list *point = beg;
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

void add_info_to_file(text_list* beg, fstream& outfile, char *text) {
	text_list* point = beg;
	outfile << text << endl;
	while (point) {
		outfile << point->str << " " << point->count << endl;
		point = point->next;
	}
}

void add_info_to_file(text_list* beg, fstream& outfile) {
	text_list* point = beg;
	outfile << "\nСлова с повторением:\n";
	while (point) {
		outfile << point->str << " " << point->count << endl;
		point = point->next;
	}
}

void delete_list(text_list* beg) {
	text_list* point = beg;
	text_list* del;
	while (point) {
		del = point;
		point = point->next;
		delete del;
	}
	delete point;
}

int get_length(text_list* beg) {
	text_list* point = beg;
	int length = 0;
	while (point) {
		
		point = point->next;
		length++;
	}
	return length;
}

void count_each_word(text_list* beg) {
	text_list* point = beg;
	while (point) {
		point->count = count_element_rep(beg, point->str);
		point = point->next;
	}
}

void print_list(text_list* beg) {
	text_list* point = beg;
	cout << "Содержимое списка:\n";
	while (point) {
		cout << point->str <<" "<<point->count << endl;
		point = point->next;
	}
}

void find_element_by_index(text_list* beg, int index) {
	text_list* point = beg;
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

int count_element_rep(text_list* beg, char *str) {
	text_list* point = beg;
	int count = 0;
	while (point) {
		if (!strcmp(point->str, str)) {
			count++;
		}
		point = point->next;
	}
	return count;
}

bool find_list_element(text_list* beg, char* str) {
	text_list* point = beg;
	int count = 0;
	bool result = false;
	while (point) {
		if (!strcmp(point->str, str)) {
			result = true;
			break;
		}
		point = point->next;
	}
	return result;
}


bool isalpha_mod(char c) {
	return (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')
		|| c == 'ё' || c == 'Ё' || isalpha((unsigned char)c); 
}

bool ispunct_end(char c) {
	char check_symb[] = "!.?";
	bool result = false;
	for (int i = 0; check_symb[i]; i++) {
		if (check_symb[i] == (unsigned char)c) {
			result = true;
			break;
		}
	}
	return result;
}