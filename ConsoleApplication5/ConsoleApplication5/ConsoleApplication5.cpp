#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

struct products //объявляем шаблон структуры
{
	string product_name; //Наименование товара
	char category[30]; //Категория товара
	char product_code[30]; //Шестизначный код товара
	char production_date[30]; //Дата производства товара
	char product_price[30]; //Цена товара
};

struct products mas[30]; //Объвляем глобальный массив структур
struct tmp; //Объявляем временую переменную структурного типа
int sch = 0; //Счетчик полных записей
int sw; //Переключатель

int menu();
void enter_new();
void out();
void find();

int main()
{
	ifstream fs;
	fs.open("C:\\Users\\nik85\\source\\repos\\ConsoleApplication5\\ConsoleApplication5\\db.txt");
	int elem = 0;
	while (fs.is_open()) {
		if (!fs.eof()) {
			fs >> mas[elem].product_name;
			fs >> mas[elem].category;
			fs >> mas[elem].product_code;
			fs >> mas[elem].production_date;
			fs >> mas[elem].product_price;
			elem += 1;
			sch += 1;
		}
		else {
			break;
		}
	}
	setlocale(LC_ALL, "Russian");
	while (1)
	{
		switch (menu())
		{
		case 1:enter_new(); break;
		case 2:find(); break;
		case 3:out(); break;
		case 4: return 0;
		default: cout << "Не верный выбор/n";
		}
	}
}

int menu()
{
	
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
	cout << "[4]-Для выхода из программы\n";
	cin >> sw;
	return sw;
}

void enter_new() //Функция ввода новой товара
{
	if (sch < 30) //Вводим новую запись только, если счетчик полных записей меньше максимального количества записей
	{
		cout << "Запись номер" << sch + 1; //Выводим номер записи
		cout << "\nНаименование товара: \n";
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
		fs << mas[sch].product_price << "/n";
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
	if (sch == 0) //Если счетчик количества структур равен 0, то выводим что нет записей
		cout << "\nНет записей: \n";
	else
	{
		cout << "\nВведите: \n";
		cout << "[1]-Поиск записи товара по его номеру \n";
		cout << "[2]-Вывод всех имеющихся записей\n";
		cin >> sw;
		if (sw == 1)
		{
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
			for (int i = 0; i < sch; i++) //Вывод в цикле всех записей
			{
				cout << "Наименование товара: " << mas[i].product_name << endl;//Вывод на экран значений name i-ой структуры из массива структур mas
				cout << "Категория товара:" << mas[i].category << endl;
				cout << "Код товара:" << mas[i].product_code << endl;
				cout << "Дата производства товара:" << mas[i].production_date << endl;
				cout << "Цена товара в рублях:" << mas[i].product_price << endl;
				cout << "____________" << endl;
			}
		}
	}
}

void find() //Функция поиска записей
{
	setlocale(LC_ALL, "Russian");
	int sw;
	if (sch == 0)
		cout << "\nНет записей: \n";
	else
	{
		cout << "\nВведите: \n";
		cout << "1-один из всех\n";
		cout << "2-все работы\n";
		cin >> sw;
		for (int i = 0; i < sch; i++) //В цикле просматриваем все структуры из массива структур
			if (i == sw)
			{
				if (i == 0)
					cout << "Ремонт" << endl;
				else

					cout << "Наименование товара:" << mas[i].product_name << endl;
				cout << "Категория товара:" << mas[i].category << endl;
					
				cout << "Код товара:" << mas[i].product_code << endl;
				cout << "Дата производства товара:" << mas[i].production_date << endl;
				cout << "Цена товара в рублях:" << mas[i].product_price << endl;
				cout << "____________" << endl;
			}
	}
}