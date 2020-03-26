#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

void fill_vector(double [], int, int start = 0, int end = 100);

void print_vector(double[], int);

int find_index_element(double[], double, int);

double find_max(double[], int);

double rnd_num(int, int);


int main() {
	system("chcp 1251 > nul");
	
	srand(time(NULL));
	
	double random = 0;
	ofstream outfile("number.dat", ios::binary | ios::out);
	for (int i = 0; i < 10; i++) {
		random = rnd_num(1, 100);
		outfile.write((char*)&random, sizeof(double));
	}
	outfile.close();

	ifstream infile("number.dat", ios::binary | ios::in);
	infile.seekg(0, ios::end);
	int n = infile.tellg() / sizeof(double);
	infile.seekg(0);

	double* vector;
	double max;
	int index, i = 0;
	
	vector = new double[n];
	while (!infile.read((char*)&vector[i], sizeof(double)).eof()) {
		i++;
	}
	infile.close();

	max = find_max(vector, n);

	index = find_index_element(vector, max, n);

	print_vector(vector, n);

	cout << endl;
	for (int i = index+1; i < n; i++) {
		vector[i] = 0;
	}
	print_vector(vector, n);
	delete[] vector;
	return 0;
}

void fill_vector(double vector[], int n, int start, int end) {
	for (int i = 0; i < n; i++) {
		vector[i] = (double)(start + rand() % end) / (1 + rand() % (end/4));
	}
}

double rnd_num(int start, int end) {
	return (double)(start + rand() % end) / (1 + rand() % (end / 4));
}

void print_vector(double vector[], int n) {
	for (int i = 0; i < n; i++) {
		cout << fixed << setprecision(2) << vector[i] << " ";
	}
	cout << "\n\n";
}

int find_index_element(double vector[], double element, int n) {
	for (int i = 0; i < n; i++) {
		if (vector[i] == element) {
			return i;
		}
	}
}

double find_max(double vector[], int n) {
	double max = 0.0;
	for (int i = 0; i < n; i++) {
		if (vector[i] > max) {
			max = vector[i];
		}
	}
	return max;
}