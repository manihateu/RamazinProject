#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
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
vector <products> mas; //Объвляем глобальный массив структур
struct tmp; //Объявляем временую переменную структурного типа
int sch = 0; //Счетчик полных записей
int sw; //Переключатель

int menu();
void enter_new();
void out();
void find();

void clearBD() {
	cout << "\nБаза данных очищена\n\n";
	ofstream ofs;
	ofs.open("..\\db.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	mas.clear();
	system("pause");
}

int main()
{
	SetConsoleOutputCP(1251); // Эти две функции для того чтобы русские буквы норм отображались
	SetConsoleCP(1251);
	ifstream fs;
	fs.open("..\\db.txt");
	if (!fs) {
		cout << "File error - can't open to read data!";
		cin.sync(); cin.get(); return 2;
	}
	while (1){
		if (!fs.eof()) {
			products mymas;
			fs >> mymas.product_name;
			fs >> mymas.category;
			fs >> mymas.product_code;
			fs >> mymas.production_date;
			fs >> mymas.product_price;
			if (mymas.category != "") { mas.push_back(mymas); }
		}
		if (fs.eof()) break;
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
	if (1) //Вводим новую запись только, если счетчик полных записей меньше максимального количества записей
	{
		products mymas;
		cout << "Запись номер" << sch + 1; //Выводим номер записи
		cout << "\n(Всё вводить без пробелов)\n";
		cout << "Наименование товара: \n";
		cin >> mymas.product_name;
		fstream fs;
		fs.open("..\\db.txt", ios::app);
			fs << mymas.product_name << "\n";
			cout << "Категория товара: \n";
			cin >> mymas.category;
			fs << mymas.category << "\n";
			cout << "Код товара (шестизначное число):\n";
			cin >> mymas.product_code;
			fs << mymas.product_code << "\n";
			cout << "Дата производства товара:\n";
			cin >> mymas.production_date;
			fs << mymas.production_date << "\n";
			cout << "Цена товара в рублях:\n";
			cin >> mymas.product_price;
			fs << mymas.product_price << "\n";
			cout << "Товар успешно добавлен" << endl;
			mas.push_back(mymas);
			sch++;
		//увеличиваем счетчик полных записей на единицу
		fs.close();
	}
	else cout << "Введено максимальное кол-во записей";
	mas.clear();
	ifstream fs;
	fs.open("..\\db.txt");
	bool flag = false;
	if (!fs) {
		cout << "File error - can't open to read data!";
		cin.sync(); cin.get(); flag = true;
	}
	while (!flag) {
		if (!fs.eof()) {
			products mymas;
			fs >> mymas.product_name;
			fs >> mymas.category;
			fs >> mymas.product_code;
			fs >> mymas.production_date;
			fs >> mymas.product_price;
			if (mymas.category != ""){mas.push_back(mymas);}
			
		}
		if (fs.eof()) break;
		sch += 1;
	}
}




void out() //Функция вывода записей
{
	setlocale(LC_ALL, "Russian");
	if (mas.size() == 0) { //Если счетчик количества структур равен 0, то выводим что нет записей
		system("cls");
		cout << "\nНет записей \n";
		system("pause");
	}
	else
	{
		system("cls");
		for (int i = 0; i < mas.size(); i++) //Вывод в цикле всех записей
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
			int count = 0;
			cout << "Введите n - ";
			int price;
			cin >> price;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].product_price < price) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					count += 1;
				}
			}
			if (count == 0) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 2) {
			int count = 0;
			cout << "Введите n - ";
			int price;
			cin >> price;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].product_price > price) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					count += 1;
				}
			}
			if (count == 0) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 3) {
			int count = 0;
			cout << "Введите Название - ";
			string name;
			cin >> name;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].product_name == name) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					count += 1;
				}
			}
			if (count == 0) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 4) {
			int count = 0;
			cout << "Введите код товара - ";
			string cod;
			cin >> cod;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].product_code == cod) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					count += 1;
				}
			}
			if (count == 0) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw == 5) {
			int count = 0;
			cout << "Введите категорию товара - ";
			string category;
			cin >> category;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].category == category) {
					cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
					cout << "Категория товара:" << mas[i].category << endl;
					cout << "Код товара:" << mas[i].product_code << endl;
					cout << "Дата производства товара:" << mas[i].production_date << endl;
					cout << "Цена товара в рублях:" << mas[i].product_price << endl;
					cout << "____________" << endl;
					count += 1;
				}
			}
			if (count == 0) {
				cout << "\nТовары не найдены!\n";
			}
		}
		if (sw != 1 && sw != 2 && sw != 3 && sw != 4 && sw != 5) {
			cout << "Такого пункта нет\n";
		}
		system("pause");
	}
}