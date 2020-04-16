#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

char path_double[] = "number_double.dat";

template <class T> void fill_vector(T [], int, int start = 0, int end = 100);

template <class T> void print_vector(T[], int, char sep = ' ');

template <class T> int find_index_element(T[], T, int);

template <class T> T find_max(T[], int);

template <class T, class V> double* sum_vectors(T[], V[], int);

template <class T, class V> double* minus_vectors(T[], V[], int);

template <class T, class V> double* divide_vectors(T[], V[], int);

template <class T, class V> double* multiply_vectors(T[], V[], int);

double rnd_num(int start = 1, int end = 100);

void create_and_fill_file(char*, int);

void fill_vector_from_file(fstream&, double*);

void change_nums_to_zero(double*, int, int);

int find_file_size(fstream&);


int main() {
	system("chcp 1251 > nul");
	
	srand(time(NULL));
	
	create_and_fill_file(path_double, 10);

	fstream infile(path_double, ios::binary | ios::in);

	int n = find_file_size(infile);
	double* vector, 
		max;
	
	int max_index = 0, 
		i = 0;
	
	vector = new double[n];
	
	fill_vector_from_file(infile, vector);

	infile.close();

	max = find_max(vector, n);

	max_index = find_index_element(vector, max, n);

	print_vector(vector, n);

	change_nums_to_zero(vector, max_index, n);

	print_vector(vector, n);
	double x[5] = { 1,2,3,4,5 };
	double *sum = sum_vectors(vector, x, 5);
	print_vector(sum, 5);

	delete[] sum;
	delete[] vector;
	return 0;
}

void create_and_fill_file(char* path, int n) {
	fstream outfile(path, ios::binary | ios::out);
	for (int i = 0; i < n; i++) {
		double random = rnd_num();
		outfile.write((char*)&random, sizeof(random));
	}
	outfile.close();
}

void fill_vector_from_file(fstream& infile, double* vector) {
	int i = 0;
	while (!infile.read((char*)&vector[i], sizeof(double)).eof()) { i++; }
}

void change_nums_to_zero(double* vector, int index, int n) {
	int i = 0,
		st = index;
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
	for (int i = 0; i < n; i++) {
		if (vector[i] == element) {
			return i;
		}
	}
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