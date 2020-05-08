#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

enum menu_keys {
	menu_do_main_task = 1,
	menu_print_vector,
	menu_math_operations,
	menu_find_max,
	menu_create_new_file,
	menu_show_instruction,
	menu_end_program
};

enum menu_math_operations_keys {
	math_sum = 1,
	math_minus,
	math_divide,
	math_multiply
};

enum file_open_keys {
	file_create_new = 1,
	file_create_new_auto,
	file_existed,
	file_end_program
};

char path_double[] = "number_double.dat";

template <class T> void fill_vector_with_random(T [], int, int start = 0, int end = 100);

template <class T> void print_vector(T[], int, char sep = ' ');

template <class T> int find_index_element(T[], T, int);

template <class T> T find_max(T[], int);

template <class T, class V> void sum_vectors(T[], V[], int);

template <class T, class V> void minus_vectors(T[], V[], int);

template <class T, class V> void divide_vectors(T[], V[], int);

template <class T, class V> void multiply_vectors(T[], V[], int);

template <class T> void protected_cin(T&);

template <class T> void fill_vector_from_file(fstream&, T*);

double rnd_num(int start = 1, int end = 100);

void create_and_fill_file_auto(char*, int);

void create_and_fill_file_auto(char*, double*, int);

void create_and_fill_file(char*);

void change_nums_to_zero(double*, int, int);

void protected_getline(char*, int);

void initialize_new_vector(double[], int);

void show_instruction();

void print_splitter(char, int, bool flag = true);

void menu_math_func(void (*F)(double[], double[], int), double *, int);

int find_file_size(fstream&);

bool sub_find(char* main_str, char* find_str);

int main() {
	system("chcp 1251 > nul");
	
	srand(time(NULL));

	fstream infile;
	
	bool work_flag = true;
	int vector_size = 0;
	int new_size = 0;
	char str[] = ".dat";
	show_instruction();
	while (!infile.is_open()) {
		int command = 0;
		char path[100]{};
		cout << "�������� ����� ������ � ������:\n"
			<< file_create_new << " - ������� ���� � ��������� ��� �������\n"
			<< file_create_new_auto << " - ������� ���� � �������� ��� �������������\n"
			<< file_existed << " - ������������ ������������ ���� � ����������� �������\n"
			<< file_end_program << " - ��������� ��������� ��������\n";
		protected_cin(command);

		switch (command){
		case file_create_new:
			create_and_fill_file(path_double);
			infile.open(path_double, ios::in | ios::binary);
			break;

		case file_create_new_auto:
			cout << "������� ���-�� ��������� � ����� �����:\n";
			protected_cin(new_size);
			create_and_fill_file_auto(path_double, new_size);
			infile.open(path_double, ios::in | ios::binary);
			break;

		case file_existed:
			cout << "������� ���������� ���� � ������ ����� (���������� .dat):\n";
			cin.ignore();
			protected_getline(path, 100);
			infile.open(path, ios::in | ios::binary);
			if (!infile.is_open()) {
				cout << "Path Error: ������������ ����!\n";
			}
			else if (!sub_find(path, str)) {
				cout << "Path Error: ������������ ���������� �����!\n";
				infile.close();
			}
			break;

		case file_end_program:
			cout << "��������� ��������� ��������!\n";
			exit(1);
			break;

		case menu_show_instruction:
			show_instruction();
			break;

		default:
			cout << "Comand Error: �������� �������\n";
			break;
		}
	}
	vector_size = find_file_size(infile);
	double* vector,
			max;
	int max_index = 0,
		i = 0;
	bool vector_exist = true;
	vector = new double[vector_size];
	fill_vector_from_file(infile, vector);
	infile.close();

	void (*math_funcs[4])(double[], double[], int)
	{
			sum_vectors,
			minus_vectors,
			divide_vectors,
			multiply_vectors,
	};

	while (work_flag) {
		int command = 0;
		unsigned int math_command = 0;
		bool correct_path_flag = false;
		char path[50];
		cout << "�������� ��������\n"
			<< menu_do_main_task << " - ��������� ������ � ��������\n"
			<< menu_print_vector << " - ������� ������\n"
			<< menu_math_operations << " - ��������� �������������� �������� ����� ���������\n"
			<< menu_find_max << " - ����� � ������� ������������ ������� �������\n"
			<< menu_create_new_file << " - �������� ������ � ����� ����\n"
			<< menu_show_instruction << " - ������� �������� ���������\n"
			<< menu_end_program << " - ����� �� ���������\n";
		protected_cin(command);
		switch (command){
		case menu_do_main_task:
			if (vector_exist) {
				cout << "��������� ������ � ��������\n";
				max = find_max(vector, vector_size);

				max_index = find_index_element(vector, max, vector_size);
				print_splitter('-', 100);
				cout << "\n������ ������: ";
				print_vector(vector, vector_size);
				change_nums_to_zero(vector, max_index, vector_size);
				print_splitter('-', 100);
				cout << "\n����� ������: ";
				print_vector(vector, vector_size);
				print_splitter('-', 100);
			}
			else {
				cout << "Vector Error: ������ �� ����������!\n";
			}
			break;

		case menu_print_vector:
			print_splitter('=', 50);
			cout << "��� ������:\n";
			print_vector(vector, vector_size);
			print_splitter('=', 50);
			break;

		case menu_math_operations:
			cout << "�������� ��������\n"
				<< math_sum << " - ����� ��������\n"
				<< math_minus << " - ������� ��������\n"
				<< math_divide << " - ������� ��������\n"
				<< math_multiply << " - ��������� ��������\n";
			protected_cin(math_command);
			switch (math_command){
			case math_sum:
				menu_math_func(math_funcs[0], vector, vector_size);
				break;

			case math_minus:
				menu_math_func(math_funcs[1], vector, vector_size);
				break;

			case math_divide:
				menu_math_func(math_funcs[2], vector, vector_size);
				break;

			case math_multiply:
				menu_math_func(math_funcs[3], vector, vector_size);
				break;

			default:
				cout << "Comand Error: �������� �������!\n";
				break;
			}
			break;

		case menu_find_max:
			cout << "\n������������ ������� ������� = " << find_max(vector, vector_size) << endl;
			break;

		case menu_create_new_file:
			cin.ignore();
			while (!sub_find(path, str)) {
				cout << "������� �������� ������ ����� � ����������� .dat ��� exit ��� ������:\n";
				protected_getline(path, 50);
				correct_path_flag = true;
				if (!_strcmpi(path, "exit")) {
					correct_path_flag = false;
					break;
				}
			}
			if (correct_path_flag) {
				cout << "������ ������ �������!\n";
				create_and_fill_file_auto(path, vector, vector_size);
			}
			else {
				cout << "������ ������� �������� ��������������!\n";
			}
			break;

		case menu_show_instruction:
			show_instruction();
			break;

		case menu_end_program:
			cout << "�� �������!\n";
			work_flag = false;
			break;

		default:
			cout << "Comand Error: ����������� �������!\n";
			break;
		}
	}
	delete[] vector;
	system("pause");
	return 0;
}

void create_and_fill_file_auto(char* path, int n) {
	fstream outfile(path, ios::binary | ios::out);
	for (int i = 0; i < n; i++) {
		double random = rnd_num();
		outfile.write((char*)&random, sizeof(random));
	}
	outfile.close();
}

void create_and_fill_file_auto(char* path, double* vector, int n) {
	fstream outfile(path, ios::binary | ios::out);
	if (outfile.is_open()) {
		for (int i = 0; i < n; i++) {
			outfile.write((char*)&vector[i], sizeof(double));
		}
		outfile.close();
	}
	else {
		cout << "FileCreate Error: �� ���������� ������� ����!\n";
	}
}

void initialize_new_vector(double new_vector[], int size) {
	double num = 0;
	cout << "������� ������ � ������:\n";
	for (int i = 0; i < size; i++) {
		protected_cin(num);
		new_vector[i] = num;
	}
}

void menu_math_func(void (*Func)(double[], double[], int), double* vector, int vector_size) {
	cout << "������� ������ ������ �������\n";
	int size = 0;
	double* new_vector;
	protected_cin(size);
	if (size > 0) {
		new_vector = new double[size];
		initialize_new_vector(new_vector, size);
		int size_to_func = 0;
		vector_size < size ? size_to_func = vector_size : size_to_func = size;
		Func(vector, new_vector, size_to_func);
		delete[] new_vector;
	}
	else {
		cout << "Size Error: ����������� ����� ������!\n";
	}
}

void create_and_fill_file(char *path) {
	cout << "������� ������ ��� exit ��� ������:\n";
	fstream outfile(path, ios::binary | ios::out);
	bool work_flag = true;
	const int size = 64;
	char data[size];
	while (work_flag) {
		protected_getline(data, size);
		if (atof(data)) {
			double num = atof(data);
			outfile.write((char*)&num, sizeof(double));
		}
		else if (!_strcmpi(data, "exit")) {
			work_flag = false;
		}
	}
	outfile.close();
}

void change_nums_to_zero(double* vector, int index, int n) {
	
	for (int i = index+1; i < n; i++) {
		vector[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (vector[i] && !vector[j]) {
				swap(vector[i], vector[j]);
			}
		}
	}
}

void protected_getline(char* string, int size) {
	bool correct_flag = true;
	while (correct_flag)
	{
		cin.getline(string, size);
		if (cin.fail())
		{
			cout << "Input Error: ������ �����! ��������� ���� �����!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			correct_flag = true;
		}
		else {
			correct_flag = false;
		}
	}
}

void print_splitter(char c, int n, bool flag) {
	for (int i = 0; i < n; i++) {
		cout << c;
	}
	if (flag) {
		cout << endl;
	}
}

void show_instruction() {
	char split = '=';
	int wide = 100;
	print_splitter(split, wide);
	cout << "����� ���������� � ��������� VectorMath!\n"
		<< "��������� ����������� ��� ������ � ���������.\n"
		<< "��� ������������ �������� �������������� �������� ����� ���������.\n"
		<< "� ������: ��������(+), ���������(-), ���������(*), �������(/).\n"
		<< "��������� ����� �������� ������������ ������� �������.\n"
		<< "��� ����� ����� ������������� �������� ��������� �������� �� ����(0)"
		<< "� ������������ ���� � ������ �������.\n"
		<< "��������� ������������ �������� ����� (����� � �������).\n"
		<< "������������ ����� ������� ��� ������ ��������� ����� �������� ����\n"
		<< "��� �� ������������ ��� ������� �������� ���� � ����������� .dat\n";
	print_splitter(split, wide);
}

int find_file_size(fstream& infile) {
	infile.seekg(0, ios::end);
	int n = infile.tellg() / sizeof(double);
	infile.seekg(0);
	return n;
}

template <class T> void fill_vector_with_random (T vector[], int n, int start, int end) {
	for (int i = 0; i < n; i++) {
		vector[i] = ((T)start + rand() % end) / ((T)1 + rand() % (end / 4));
	}
}

template <class T> void print_vector(T vector[], int n, char sep){
	for (int i = 0; i < n; i++) {
		cout << fixed << setprecision(2) << vector[i] << sep;
	}
	cout << "\n\n";
}

template <class T> int find_index_element(T vector[], T element, int n) {
	int result = -1;
	for (int i = 0; i < n; i++) {
		if (vector[i] == element) {
			result = i;
			break;
		}
	}
	return result;
}
template <class T, class V> void  sum_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		first[i] = first[i] + second[i];
	}
}

template <class T, class V> void minus_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		first[i] = first[i] - second[i];
	}
}

template <class T, class V> void divide_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		if (second[i] == 0) {
			first[i] = 0;
		}
		else {
			first[i] = first[i] / second[i];
		}
	}
}

template <class T, class V> void multiply_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		first[i] = first[i] * second[i];
	}
}

template <class T> T find_max(T vector[], int n) {
	T max = 0.0;
	for (int i = 0; i < n; i++) {
		if (vector[i] > max) {
			max = vector[i];
		}
	}
	return max;
}

template <class T> void protected_cin(T& var) {
	bool correct_flag = true;
	while (correct_flag)
	{
		cin >> var;
		if (cin.fail())
		{
			cout << "Input Error: ������ �����! ��������� ���� �����!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			correct_flag = true;
		}
		else {
			correct_flag = false;
		}
	}
}

template <class T> void fill_vector_from_file(fstream& infile, T* vector) {
	int i = 0;
	while (!infile.read((char*)&vector[i], sizeof(T)).eof()) { i++; }
}

double rnd_num(int start, int end) {
	return ((double)start + rand() % end) / ((double)1 + rand() % (end / 4));
}

bool sub_find(char* main_str, char* find_str) {
	if (strlen(find_str) > strlen(main_str)) {
		return false;
	}
	for (int i = 0; i <= strlen(main_str) - strlen(find_str); i++) {
		char* save_str = new char[128]{};
		for (int j = 0; j < strlen(find_str); j++) {
			save_str[j] = main_str[i + j];
		}

		if (!strcmp(save_str, find_str)) {
			return true;
		}
		delete[] save_str;
	}

	return false;
}