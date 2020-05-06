#include <iostream>
#include <fstream>

using namespace std;

char path_in[] = "myfile.txt", // Пути к файлам ввода и вывода
	 path_out[] = "C:\\Users\\User\\outfile.txt";

enum menu_keys {
	menu_file_mod = 1,
	menu_change_main_nums,
	menu_do_main_action,
	menu_show_inst,
	menu_end
};

struct text_list { // Реализация структуры, которая хранит слово и кол-во его повторов
	int size = 10;
	char *str;
	unsigned int count = 0;
	text_list* next = nullptr; // Указатель на след. структуру 
};

text_list* add_to_list(text_list*, int ); // Объявление прототипов функций

text_list* list_with_repetation(text_list*, int);

text_list* delete_last_element(text_list*);

text_list* initialize_list_object(int);

char* fill_string_from_file(fstream&, int);

void delete_element(text_list*);

void print_list(text_list*);

void show_instruction();

void delete_list(text_list*);

void find_element_by_index(text_list*, int);

void count_each_word(text_list*);

void fill_list_from_str(text_list*, char[]);

void print_splitter(char, int, bool flag = true);

void add_info_to_outfile(text_list*, fstream&, char *);

void add_info_to_outfile(text_list*, fstream&);

void add_info_to_infile(char*, int, int, int);

void fool_protected_cin(int&);

int count_element_rep(text_list*, char*);

int get_length(text_list*);

bool isalpha_modifed(char);

bool ispunct_end(char);

bool find_list_element(text_list*, char*);

int main() {
	system("chcp 1251 > nul"); // Изменение кодировки консоли
	show_instruction();
	int nl = 0,
		ns = 0,
		nw = 0,
		max_size = 0;
	bool work_flag = true;
	
	cout << "Введите кол-во предложений:\n";
	fool_protected_cin(nl);
	cout << "Введите кол-во слов в предложении:\n";
	fool_protected_cin(ns);
	cout << "Введите кол-во символов в слове:\n";
	fool_protected_cin(nw);
	max_size = nl * ns * nw;
	cout << "Максимальное кол-во символов в тексте = " << max_size << endl;
	fstream infile;
	while (work_flag) {
		int command = 0;
		cout << "Введите комманду:\n"
			<< menu_file_mod << " - Выбрать режим работы с файлом\n"
			<< menu_change_main_nums << " - Изменить кол-во предложений, слов и максимальный размер слова\n"
			<< menu_do_main_action << " - Произвести работу с текстом\n"
			<< menu_show_inst << " - Вывести в консоль описание программы\n"
			<< menu_end << " - Выйти из программы\n";

		fool_protected_cin(command);
		switch (command) {
		case menu_file_mod :
			cout << "Выберите режим работы с файлом:\n";
			cout << "1 - Подготовленный файл\n";
			cout << "2 - Создать новый файл\n";
			fool_protected_cin(command);
			if (command == 1) {
				char path[100]{};
				infile.open(path, ios::in);
				cin.ignore();
				while (!infile.is_open()) {
					infile.close();
					cout << "Введите корректный путь к вашему файлу:\n";
					cin.getline(path, 100);
					infile.open(path, ios::in);
				}
			}
			else if (command == 2) {
				add_info_to_infile(path_in, nl, ns, nw);
				infile.open(path_in, ios::in);
			}
			break;
			
		case menu_change_main_nums:
			cout << "Введите кол-во предложений:\n";
			fool_protected_cin(nl);
			cout << "Введите кол-во слов в предложении:\n";
			fool_protected_cin(ns);
			cout << "Введите кол-во символов в слове:\n";
			fool_protected_cin(nw);
			max_size = nl * ns * nw;
			cout << "Максимальное кол-во символов в тексте = " << max_size << endl;
			break;
			
			//fstream infile(path_in, ios::in); // Открытие файлового потока
		case menu_do_main_action:
			if (infile.is_open()) {
				text_list* beg = initialize_list_object(nw); // Создание односвязного списка
				char* num = new char[nw];
				infile.getline(num, nw);
				int word_num = atoi(num) ? word_num = atoi(num) : word_num = 1;
				cout << word_num << endl;
				char* text = fill_string_from_file(infile, max_size);


				fill_list_from_str(beg, text);

				count_each_word(beg);

				print_list(beg);

				text_list* beg_rep = list_with_repetation(beg, word_num);

				print_list(beg_rep);

				fstream outfile(path_out, ios::out);

				outfile << "Кол-во повторений слов:" << word_num << endl;
				add_info_to_outfile(beg, outfile, text);
				add_info_to_outfile(beg_rep, outfile);

				infile.close();
				outfile.close();
				delete_list(beg);
				delete_list(beg_rep);
				delete[] num;
				delete[] text;
			}
			else {
				cout << "File Error: Файл с текстом не найден!\n";
			}
			break;
		case menu_show_inst:
			show_instruction();
			break;
		case menu_end:
			work_flag = false;
			infile.close();
			break;
		default:
			cout << "Command Error: Неизветсная комманда!\n";
			break;
		}
	}
	return 0;
}
char* fill_string_from_file(fstream& infile, int max_size) { // Функция чтения текста из файла
	char* text = new char[max_size]{};
	int index = 0;
	infile.clear();
	infile.flush();
	while (!infile.eof()) {
		text[index] = infile.get();
		if (ispunct_end(text[index])) { // Поиск символа прекращения чтения из файла (.!?)
			text[index] = '\0'; // Добавляем нуль-символ в конец проч. строки
			infile.clear();
			break;
		}
		index++;
	}
	infile.seekg(0, ios::beg);
	return text; // Возврат строку с текстом из файла
}

text_list* initialize_list_object(int size) {
	text_list* object = new text_list;
	object->size = size;
	object->str = new char[size] {};
	return object;
}

text_list* add_to_list(text_list* beg, int k) { // Функция добавления нового элемента в односвязный список
	text_list* pnew = initialize_list_object(beg->size);
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
		delete_element(pnew); // Высвобождение незадейств. памяти
	}
	return beg;
}

text_list* list_with_repetation(text_list* beg, int word_num) {
	text_list *beg_rep = initialize_list_object(beg->size);
	text_list* point = beg;
	text_list* point_rep = beg_rep;
	while (point) {
		if (point->count == word_num && !find_list_element(beg_rep, point->str)) {
			strcpy_s(point_rep->str, point->size, point->str);
			point_rep->count = point->count;
			point_rep->size = point->size;
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
	int k = get_length(beg) - 1;
	int len = 0;
	while (point) {
		if (len + 1 == k) {
			delete_element(point->next);
			point->next = nullptr;
			break;
		}
		len++;
		point = point->next;
	}
	return beg;
}
void delete_element(text_list* beg) {
	delete beg->str;
	delete beg;
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
	print_splitter('=', 100);
	cout << "Описание программы Text Quick Analytics\n"
		<<"Программа используется для анализа текста, введённого пользователем\n"
		<<"Пользователь вводит кол-во предложений, слов и размер этих слов в тексте\n"
		<<"После получения текста происходит подсчёт каждого слова в тексте\n"
		<<"Программа выводит слова, кол-во повторений которых в тексте равняется числу, ранее введённым пользователем\n"
		<<"Результат работы выводится на экран консоли и записывается в отдельный файл\n";
	print_splitter('=', 100);
}

void fool_protected_cin(int& var) {
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

void add_info_to_infile(char*, int nl, int ns, int nw) {
	fstream infile(path_in, ios::out);
	int num = 0;
	cout << "Введите искомое кол-во повторений слов:\n";
	fool_protected_cin(num);
	infile << num << "\n";
	int size = ns * nw;
	char* data = new char[size]{};
	cout << "В конце ввода поставьте символ конца предложения(.?!)\n";
	cin.ignore();
	for (int i = 0; i < nl; i++) {
		cout << "Введите " << i + 1 << "-ое предложение:\n";
		cin.getline(data, (size_t)ns * nw);
		infile << data << "\n";
	}
	infile.close();
	delete[] data;
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
	if (get_length(beg) <= 1) { // Если список пуст, то записываем, что данных нет
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
		delete_element(del); // Удаляем прошлый элемент
	}
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
		if (point->count != 0) {
			cout << point->str << " - " << point->count << endl; // Вывод слова и кол-ва его повторений
		}
		point = point->next;
	}
}

void find_element_by_index(text_list* beg, int index) {
	text_list* point = beg;
	int length = 0;
	while (point) {
		if (length != index) {
			length++;
			point = point->next;

		}
		else {
			cout << "Ваш элемент: " << point->str << endl;
		}
	}
	cout << "Find Error: Элемент не найден!\n";
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
		if (!_strcmpi(point->str, str)) { // Сравнение строк
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
		if (!_strcmpi(point->str, str)) { // Сравнение строк
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
	char check_symb[] = "?.!";
	bool result = false;
	for (int i = 0; check_symb[i]; i++) {
		if (check_symb[i] == (unsigned char)c) {
			result = true;
			break;
		}
	}
	return result;
}