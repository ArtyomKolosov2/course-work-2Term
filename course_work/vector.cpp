#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

enum menu_keys {
	menu_do_main_task = 1,
	menu_print_vector,
	menu_math_operations,
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

template <class T> void fill_vector(T [], int, int start = 0, int end = 100);

template <class T> void print_vector(T[], int, char sep = ' ');

template <class T> int find_index_element(T[], T, int);

template <class T> T find_max(T[], int);

template <class T, class V> double* sum_vectors(T[], V[], int);

template <class T, class V> double* minus_vectors(T[], V[], int);

template <class T, class V> double* divide_vectors(T[], V[], int);

template <class T, class V> double* multiply_vectors(T[], V[], int);

template <class T> void fool_protected_cin(T&);

template <class T> void fill_vector_from_file(fstream&, T*);

double rnd_num(int start = 1, int end = 100);

void create_and_fill_file_auto(char*, int);

void create_and_fill_file(char*);

void change_nums_to_zero(double*, int, int);

void fool_protected_getline(char*, int);

int find_file_size(fstream&);


int main() {
	system("chcp 1251 > nul");
	
	srand(time(NULL));

	fstream infile;
	
	bool work_flag = true;
	int file_size = 0;
	int new_size = 0;
	
	while (!infile.is_open()) {
		int command = 0;
		char path[100]{};
		cout << "Выберите режим работы с файлом:\n";
		fool_protected_cin(command);
		switch (command)
		{
		case file_create_new:
			create_and_fill_file(path_double);
			infile.open(path_double, ios::in | ios::binary);
			break;
		case file_create_new_auto:
			cout << "Введите кол-во элементов в новом файле:\n";
			fool_protected_cin(new_size);
			create_and_fill_file_auto(path_double, new_size);
			infile.open(path_double, ios::in | ios::binary);
			break;
		case file_existed:
			cout << "Введите корректный путь к вашему файлу или exit для выхода:\n";
			cin.ignore();
			fool_protected_getline(path, 100);
			infile.open(path, ios::in | ios::binary);
			if (!infile.is_open()) {
				cout << "Path Error: Неправильный путь!\n";
			}
			break;
		case file_end_program:
			cout << "Программа завершена досрочно!\n";
			exit(1);
			break;
		default:
			cout << "Comand Error: Неверная команда\n";
			break;
		}
	}
	file_size = find_file_size(infile);
	double* vector,
			max;
	int max_index = 0,
		i = 0;
	bool vector_exist = true;
	vector = new double[file_size];
	fill_vector_from_file(infile, vector);
	infile.close();
	while (work_flag) {
		int command = 0;
		fool_protected_cin(command);
		switch (command){

		case menu_do_main_task:
			if (vector_exist) {
				cout << "Do the thing\n";
				max = find_max(vector, file_size);

				max_index = find_index_element(vector, max, file_size);

				print_vector(vector, file_size);

				change_nums_to_zero(vector, max_index, file_size);

				print_vector(vector, file_size);
			}
			else {
				cout << "Vector Error: Вектор не существует!\n";
			}
			break;
		case menu_print_vector:
			print_vector(vector, file_size);
			break;

		case menu_math_operations:
			break;

		case menu_end_program:
			work_flag = false;
			break;

		default:
			break;
		}
		
		/*fill_vector_from_file(infile, vector);

		infile.close();

		max = find_max(vector, file_size);

		max_index = find_index_element(vector, max, file_size);

		print_vector(vector, file_size);

		change_nums_to_zero(vector, max_index, file_size);

		print_vector(vector, file_size);
		double x[5] = { 1,2,3,4,5 };
		double* (*F[4])(double[], double[], int)
		{
				sum_vectors,
				minus_vectors,
				multiply_vectors,
				divide_vectors,
		};
		for (int i = 0; i < 4; i++) {
			double* sum = F[i](vector, x, 5);
			print_vector(sum, 5);
			delete[] sum;
		}*/
		
	}
	delete[] vector;
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
void create_and_fill_file(char *path) {
	cout << "Введите данные или exit для выхода:\n";
	fstream outfile(path, ios::binary | ios::out);
	bool work_flag = true;
	char data[64];
	while (work_flag) {
		fool_protected_getline(data, 64);
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

template <class T> void fill_vector_from_file(fstream& infile, T* vector) {
	int i = 0;
	while (!infile.read((char*)&vector[i], sizeof(T)).eof()) { i++; }
}

void change_nums_to_zero(double* vector, int index, int n) {
	int i = 0;
	for (i = index+1; i < n; i++) {
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

void fool_protected_getline(char* string, int size) {
	bool correct_flag = true;
	while (correct_flag)
	{
		cin.getline(string, size);
		if (cin.fail())
		{
			cout << "Input Error: Ошибка ввода! Повторите ввод снова!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			correct_flag = true;
		}
		else {
			correct_flag = false;
		}
	}
}

int find_file_size(fstream& infile) {
	infile.seekg(0, ios::end);
	int n = infile.tellg() / sizeof(double);
	infile.seekg(0);
	return n;
}

template <class T> void fill_vector (T vector[], int n, int start, int end) {
	for (int i = 0; i < n; i++) {
		vector[i] = ((T)start + rand() % end) / ((T)1 + rand() % (end / 4));
	}
}

double rnd_num(int start, int end) {
	return ((double)start + rand() % end) / ((double)1 + rand() % (end / 4));
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
template <class T, class V> double*  sum_vectors(T first[], V second[], int n) {
	double* sum = new double[n] {};
	for (int i = 0; i < n; i++) {
		sum[i] = first[i] + second[i];
	}
	return sum;
}

template <class T, class V> double* minus_vectors(T first[], V second[], int n) {
	double* minus = new double[n] {};
	for (int i = 0; i < n; i++) {
		minus[i] = first[i] - second[i];
	}
	return minus;
}

template <class T, class V> double* divide_vectors(T first[], V second[], int n) {
	double* division = new double[n] {};
	for (int i = 0; i < n; i++) {
		division[i] = first[i] / second[i];
	}
	return division;
}

template <class T, class V> double* multiply_vectors(T first[], V second[], int n) {
	double* multi = new double[n] {};
	for (int i = 0; i < n; i++) {
		multi[i] = first[i] * second[i];
	}
	return multi;
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

template <class T> void fool_protected_cin(T& var) {
	bool correct_flag = true;
	while (correct_flag)
	{
		cin >> var;
		if (cin.fail())
		{
			cout << "Input Error: Ошибка ввода! Повторите ввод снова!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			correct_flag = true;
		}
		else {
			correct_flag = false;
		}
	}
}