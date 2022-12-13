#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

struct products //объявляем шаблон структуры
{
	string product_name; //Наименование товара
	string category; //Категория товара
	string product_code; //Шестизначный код товара
	char production_date[30]; //Дата производства товара
	int product_price; //Цена товара
};

struct products mas[30]; //Объвляем глобальный массив структур
struct tmp; //Объявляем временую переменную структурного типа
int sch = 0; //Счетчик полных записей
int sw; //Переключатель

int menu();
void enter_new();
void out();
void find();

void clearBD() {
	ofstream ofs;
	ofs.open("C:\\Users\\nik85\\source\\repos\\ConsoleApplication5\\ConsoleApplication5\\db.txt", ofstream::out | ofstream::trunc);
	ofs.close();
}

int main()
{
	SetConsoleOutputCP(1251); // Эти две функции для того чтобы русские буквы норм отображались
	SetConsoleCP(1251);
	ifstream fs;
	fs.open("C:\\Users\\nik85\\source\\repos\\ConsoleApplication5\\ConsoleApplication5\\db.txt");
	int elem = 0;
	if (!fs) {
		cout << "File error - can't open to read data!";
		cin.sync(); cin.get(); return 2;
	}
	while (1){
			fs >> mas[elem].product_name;
			fs >> mas[elem].category;
			fs >> mas[elem].product_code;
			fs >> mas[elem].production_date;
			fs >> mas[elem].product_price;
			if (fs.eof()) break;
			elem += 1;
			sch += 1;
	}
	
	while (1)
	{
		switch (menu())
		{
		case 1:enter_new(); break;
		case 2:find(); break;
		case 3:out(); break;
		case 4:clearBD(); break;
		case 5: return 0;
		default: cout << "Не верный выбор/n";
		}
	}
	fs.close();
}

int menu()
{
	system("cls");
	setlocale(LC_ALL, "Russian");
	int sw;
	cout << "-----ДОБРО ПОЖАЛОВАТЬ------\n";
	cout << "\n";
	cout << "-----МЕНЮ СКЛАДА ТОВАРОВ------\n";
	cout << "\n";
	cout << "Для выбора действия введите:" << endl;
	cout << "\n";
	cout << "[1]-Для создания записи нового товара\n";
	cout << "[2]-Для поиска записи товаров по параметрам (пока не работает)\n";
	cout << "[3]-Для вывода записей \n";
	cout << "[4]-Очистить базу данных\n";
	cout << "[5]-Для выхода из программы\n";
	cin >> sw;
	return sw;
}

void enter_new() //Функция ввода новой товара
{
	system("cls");
	if (sch < 30) //Вводим новую запись только, если счетчик полных записей меньше максимального количества записей
	{
		cout << "Запись номер" << sch + 1; //Выводим номер записи
		cout << "\n(Всё вводить без пробелов)\n";
		cout << "Наименование товара: \n";
		cin >> mas[sch].product_name;
		fstream fs;
		fs.open("C:\\Users\\nik85\\source\\repos\\ConsoleApplication5\\ConsoleApplication5\\db.txt", ios::app);
		fs << mas[sch].product_name << "\n";
		cout << "Категория товара: \n";
		cin >> mas[sch].category;
		fs << mas[sch].category << "\n";
		cout << "Код товара (шестизначное число):\n";
		cin >> mas[sch].product_code;
		fs << mas[sch].product_code << "\n";
		cout << "Дата производства товара:\n";
		cin >> mas[sch].production_date;
		fs << mas[sch].production_date << "\n";
		cout << "Цена товара в рублях:\n";
		cin >> mas[sch].product_price;
		fs << mas[sch].product_price << "\n";
		cout << "Товар успешно добавлен" << endl;

		sch++; //увеличиваем счетчик полных записей на единицу
		fs.close();
	}
	else cout << "Введено максимальное кол-во записей";
}




void out() //Функция вывода записей
{
	setlocale(LC_ALL, "Russian");
	int sw; //Переключатель для выбора выводить все записи или одну
	int n; //Номер структуры, которую надо вывести
	if (sch == 0) { //Если счетчик количества структур равен 0, то выводим что нет записей
		system("cls");
		cout << "\nНет записей: \n";
		system("pause");
	}
	else
	{
		system("cls");
		cout << "\nВведите: \n";
		cout << "[1]-Поиск записи товара по его номеру \n";
		cout << "[2]-Вывод всех имеющихся записей\n";
		cin >> sw;
		if (sw == 1)
		{
			system("cls");
			cout << "Введите номер записи товара, запись которой вы хотите вывести\n";
			cin >> n;
			cout << endl;
			cout << "Наименование товара: " << mas[n - 1].product_name << endl;
			cout << "Категория товара:" << mas[n - 1].category << endl;
			cout << "Код товара:" << mas[n - 1].product_code << endl;
			cout << "Дата производства товара:" << mas[n - 1].production_date << endl;
			cout << "Цена товара в рублях:" << mas[n - 1].product_price << endl;
			cout << "____________" << endl;
			cout << "Для обратного перехода в меню введите 1" << endl;
		}
		if (sw == 2)
		{
			system("cls");
			for (int i = 0; i < sch; i++) //Вывод в цикле всех записей
			{
				cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
				cout << "Категория товара:" << mas[i].category << endl;
				cout << "Код товара:" << mas[i].product_code << endl;
				cout << "Дата производства товара:" << mas[i].production_date << endl;
				cout << "Цена товара в рублях:" << mas[i].product_price << endl;
				cout << "____________" << endl;
			}
			system("pause");
		}
		if (sw != 1 && sw != 2) {
			cout << "Такого пункта не существует";
			system("pause");
		}
	}
}


void find() //Функция поиска записей
{

	setlocale(LC_ALL, "Russian");
	int sw;
	if (sch == 0) {
		cout << "\nНет записей: \n";
	}
	else
	{
		cout << "\nВведите: \n";
		cout << "1 - Найти по цене до n \n";
		cout << "2 - Найти по цене выше n \n";
		cout << "3 - Найти по имени товара \n";
		cout << "4 - Найти по коду товара \n";
		cout << "5 - Найти по категории товара \n";
		cin >> sw;
		if (sw == 1) {
			bool flag = false;
			cout << "Введите n - ";
			int price;
			cin >> price;
			for (int i = 0; i < sch; i++) {
				if (mas[i].product_price < price) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					flag = true;
				}
			}
			if (!flag) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 2) {
			bool flag = false;
			cout << "Введите n - ";
			int price;
			cin >> price;
			for (int i = 0; i < sch; i++) {
				if (mas[i].product_price > price) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
				}
			}
			if (!flag) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 3) {
			bool flag = false;
			cout << "Введите Название - ";
			string name;
			cin >> name;
			for (int i = 0; i < sch; i++) {
				if (mas[i].product_name == name) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
				}
			}
			if (!flag) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 4) {
			bool flag = false;
			cout << "Введите код товара - ";
			string cod;
			cin >> cod;
			for (int i = 0; i < sch; i++) {
				if (mas[i].product_code == cod) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
				}
			}
			if (!flag) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 5) {
			bool flag = false;
			cout << "Введите категорию товара - ";
			string category;
			cin >> category;
			for (int i = 0; i < sch; i++) {
				if (mas[i].category == category) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
				}
			}
			if (!flag) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw != 1 && sw != 2 && sw != 3 && sw != 4 && sw != 5) {
			cout << "Такого пункта нет\n";
		}
		system("pause");
	}
}