#include <iostream>
#include <fstream>

using namespace std;

const char path_in[100] = "C:\\Users\\User\\myfile.txt", // Пути к файлам ввода и вывода
		   path_out[100] = "C:\\Users\\User\\outfile.txt";

const int nl = 10, // Константные переменные, содержащие данные о размере входного файла
		  ns = 10,
		  nw = 30;


struct text_list { // Реализация структуры, которая хранит слово и кол-во его повторов
	char str[nw]{};
	unsigned int count = 0;
	text_list* next = nullptr; // Указатель на след. структуру 
};

text_list* add_to_list(text_list*, int ); // Объявление прототипов функций

text_list* list_with_repetation(text_list*, int);

text_list* delete_last_element(text_list*);

char* fill_string_from_file(fstream&);

void print_list(text_list*);

void delete_list(text_list*);

void find_element_by_index(text_list*, int);

void count_each_word(text_list*);

void fill_list_from_str(text_list*, char[]);

void add_info_to_outfile(text_list*, fstream&, char *);

void add_info_to_outfile(text_list*, fstream&);

int count_element_rep(text_list*, char*);

int get_length(text_list*);

bool isalpha_modifed(char);

bool ispunct_end(char);

bool find_list_element(text_list*, char*);

int main() {
	system("chcp 1251 > nul"); // Изменение кодировки консоли
	
	text_list* beg = new text_list; // Создание односвязного списка

	fstream infile(path_in, ios::in); // Открытие файлового потока
	if (!infile) {
		cout << "Error: Файл не найден!\n";
		return 1;
	}
	char num[nw];
	infile.getline(num, nw);
	int word_num = atoi(num);
	cout << word_num << endl;
	char *text = fill_string_from_file(infile);
	infile.close();

	fill_list_from_str(beg, text);

	count_each_word(beg);

	print_list(beg);

	text_list* beg_rep = list_with_repetation(beg, word_num);

	print_list(beg_rep);

	fstream outfile(path_out, ios::out);

	outfile << word_num << endl;
	add_info_to_outfile(beg, outfile, text);
	add_info_to_outfile(beg_rep, outfile);

	outfile.close();

	delete_list(beg);
	delete_list(beg_rep);
	delete[] text;
	return 0;
}
char* fill_string_from_file(fstream& infile) { // Функция чтения текста из файла
	char* text = new char[nw * ns * nl]{};
	int index = 0;
	while (!infile.eof()) {
		text[index] = infile.get();
		if (ispunct_end(text[index])) { // Поиск символа прекращения чтения из файла (.!?)
			text[index] = '\0'; // Добовляем нуль-символ в конец проч. строки
			break;
		}
		index++;
	}
	return text; // Возврат строку с текстом из файла
}
text_list* add_to_list(text_list* beg, int k) { // Функция добавления нового элемента в односвязный список
	text_list* pnew = new text_list;
	text_list* point = beg;
	if (k == 0) {
		pnew->next = beg;
		beg = pnew;
		return beg;
	}
	for (int i = 0; i < k - 1 && point; i++) { // Идём до указанной позиции в списке
		point = point->next;
	}
	if (point) { // Проверка элем. в списке
		pnew->next = point->next;
		point->next = pnew;
	}
	else {
		delete pnew; // Высвобождение незадейств. памяти
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

text_list* delete_last_element(text_list* beg) { // Функция удаления последнего элемента из списка
	text_list* point = beg;
	text_list* del;
	int k = get_length(beg) - 1;
	int len = 0;
	while (point) {
		if (len + 1 == k) {
			delete point->next;
			point->next = nullptr;
			break;
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
		if (isalpha_modifed((unsigned char)text[i])) {
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

void add_info_to_outfile(text_list* beg, fstream& outfile, char *text) { // Функция добавления информации в выходной файл (эхо-печать)
	text_list* point = beg;
	outfile << text << endl;
	while (point) {
		outfile << point->str << " " << point->count << endl;
		point = point->next;
	}
}

void add_info_to_outfile(text_list* beg, fstream& outfile) { // Функция добавления информации в выходной файл (эхо-печать)
	text_list* point = beg;
	outfile << "\nСлова с повторением:\n";
	if (get_length(beg) == 1) { // Если список пуст, то записываем, что данных нет
		outfile << "Н/Д\n";
	}
	else {
		while (point) {
			outfile << point->str << " " << point->count << endl;
			point = point->next;
		}
	}
}

void delete_list(text_list* beg) { // Функция удаления списка
	text_list* point = beg;
	text_list* del;
	while (point) {
		del = point; // Запоминаем пред. элемент списка
		point = point->next; // Идём вперёд на след. элемент списка
		delete del; // Удаляем прошлый элемент
	}
	delete point;
}

void count_each_word(text_list* beg) { // Функция заносит кол-во повторений слов в список
	text_list* point = beg;
	while (point) {
		point->count = count_element_rep(beg, point->str); // Вызов функции, возврощающей кол-во повторений
		point = point->next;
	}
}

void print_list(text_list* beg) { // Функция, выводящая список в консоль
	text_list* point = beg;
	cout << "Содержимое списка:\n";
	while (point) {
		cout << point->str << " " << point->count << endl; // Вывод слова и кол-ва его повторений
		point = point->next;
	}
}

void find_element_by_index(text_list* beg, int index) {
	text_list* point = beg;
	int length = 0;
	while (point) {
		if (!(length == index)) {
			length++;
			point = point->next;

		}
		else {
			cout << "Ваш элемент: " << point->str << endl;
		}
	}
	cout << "Элемент не найден!\n";
}


int get_length(text_list* beg) { // Функция, возвращающая длинну списка
	text_list* point = beg;
	int length = 0;
	while (point) {
		point = point->next;
		length++; // Добавление 1 к длинне 
	}
	return length;
}


int count_element_rep(text_list* beg, char *str) { // Функция, возвращающая кол-во повторений слова в списке
	text_list* point = beg;
	int count = 0;
	while (point) {
		if (!strcmp(point->str, str)) { // Сравнение строк
			count++;
		}
		point = point->next;
	}
	return count;
}

bool find_list_element(text_list* beg, char* str) { // Функция, возвращающая результат поиска слова в списке
	text_list* point = beg;
	bool result = false;
	while (point) {
		if (!strcmp(point->str, str)) { // Сравнение строк
			result = true;
			break; 
		}
		point = point->next;
	}
	return result;
}


bool isalpha_modifed(char c) { // Модифицированная функция isalpha() работающая с русскими символами
	return (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')
		|| c == 'ё' || c == 'Ё' || isalpha((unsigned char)c); 
}

bool ispunct_end(char c) { // Функция, сравнивает полученный символ с сиволами конца строки
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