#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

enum menu_keys {
	menu_do_main_task = 1,
	menu_print_vector,
	menu_math_operations,
	menu_create_new_file,
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

template <class T, class V> void sum_vectors(T[], V[], int);

template <class T, class V> void minus_vectors(T[], V[], int);

template <class T, class V> void divide_vectors(T[], V[], int);

template <class T, class V> void multiply_vectors(T[], V[], int);

template <class T> void fool_protected_cin(T&);

template <class T> void fill_vector_from_file(fstream&, T*);

double rnd_num(int start = 1, int end = 100);

void create_and_fill_file_auto(char*, int);

void create_and_fill_file_auto(char*, double*, int);

void create_and_fill_file(char*);

void change_nums_to_zero(double*, int, int);

void fool_protected_getline(char*, int);

void initialize_new_vector(double[], int);

int find_file_size(fstream&);

bool sub_find(char* main_str, char* find_str);

int main() {
	system("chcp 1251 > nul");
	
	srand(time(NULL));

	fstream infile;
	
	bool work_flag = true;
	int file_size = 0;
	int new_size = 0;
	char str[] = ".dat";
	while (!infile.is_open()) {
		int command = 0;
		char path[100]{};
		cout << "Выберите режим работы с файлом:\n"
			<< file_create_new << " - Создать файл и заполнить его вручную\n"
			<< file_create_new_auto << " - Создать файл и запонить его автоматически\n"
			<< file_existed << " - Использовать существующий файл с корректными данными\n";
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
			cout << "Введите корректный путь к вашему файлу (расширение .dat):\n";
			cin.ignore();
			fool_protected_getline(path, 100);
			infile.open(path, ios::in | ios::binary);
			if (!infile.is_open()) {
				cout << "Path Error: Неправильный путь!\n";
			}
			else if (!sub_find(path, str)) {
				cout << "Path Error: Неправильное расширение файла!\n";
				infile.close();
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
		unsigned int math_command = 0;
		bool correct_path_flag = false;
		char path[50];
		cout << "Выберите комманду\n"
			<< menu_do_main_task << " - Выполнить работу с вектором\n"
			<< menu_print_vector << " - Вывести вектор\n"
			<< menu_math_operations << " - Выполнить математическую операцию между векторами\n"
			<< menu_create_new_file << " - Записать вектор в новый файл\n"
			<< menu_end_program << " - Выйти из программы\n";
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
			cout << math_sum << " - Сумма нового вектора\n";
			fool_protected_cin(math_command);
			if (math_command == math_sum) {
				cout << "Введите размер нового вектора\n";
				int size = 0;
				fool_protected_cin(size);
				double* new_vector = new double[size];
				initialize_new_vector(new_vector, size);
				int size_to_func = 0;
				file_size < size ? size_to_func = file_size : size_to_func = size;
				sum_vectors(vector, new_vector, size_to_func);
				delete[] new_vector;
			}
			break;

		case menu_end_program:
			work_flag = false;
			break;
		case menu_create_new_file:
			cout << "Введите название нового файла с расширением .dat\n";
			while (!sub_find(path, str)) {
				fool_protected_getline(path, 50);
				correct_path_flag = true;
				if (!_strcmpi(path, "exit")) {
					correct_path_flag = false;
					break;
				}
			}
			if (correct_path_flag) {
				cout << "Запись прошла успешно!\n";
				create_and_fill_file_auto(path, vector, file_size);
			}
			else {
				cout << "Запись вектора прервана!\n";
			}
			break;
		
		default:
			cout << "Comand Error: Неизвестная команда!\n";
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

void create_and_fill_file_auto(char* path, double* vector, int n) {
	fstream outfile(path, ios::binary | ios::out);
	if (outfile.is_open()) {
		for (int i = 0; i < n; i++) {
			outfile.write((char*)&vector[i], sizeof(double));
		}
		outfile.close();
	}
	else {
		cout << "FileCreate Error: Не получилось создать файл!\n";
	}
}

void initialize_new_vector(double new_vector[], int size) {
	double num = 0;
	for (int i = 0; i < size; i++) {
		fool_protected_cin(num);
		new_vector[i] = num;
	}
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

template <class T, class V> double* minus_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		first[i] = first[i] - second[i];
	}
}

template <class T, class V> double* divide_vectors(T first[], V second[], int n) {
	for (int i = 0; i < n; i++) {
		first[i] = first[i] / second[i];
	}
}

template <class T, class V> double* multiply_vectors(T first[], V second[], int n) {
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