// Gospodi.cpp: определяет точку входа для консольного приложения.
//17. Для данной матрицы найдите транспонированную матрицу.
//Выполнил Теперик Дмитрий, 9 группа

#include "stdafx.h"
#include <iostream>
using namespace std;

//Создание динамического массива
float **Memory(const int s, const int c)
{
	float **matrix = new float *[s];
	for (int i = 0; i < s; i++)
		matrix[i] = new float[c];
	return matrix;
}

// Чтение матрицы с клавиатуры 
float **ReadMatrFromCon(int *s, int *c)
{
	cout << "кол-во строк в матрице ";
	cin >> *s;
	cout << "кол-во столбцов в матрице ";
	cin >> *c;
	float **matrix;
	if ((s <= 0) || (c <= 0))
	{
		cout << "Неверная размерность" << endl;
		matrix = NULL;
	}
	else
	{
		matrix = Memory(*s, *c);
		cout << "Введите матрицу построчно" << endl;
		for (int i = 0; i < *s; i++)
			for (int j = 0; j < *c; j++)
				cin >> matrix[i][j];			
	}
	return matrix;
}

//Перечень недопустимых символов
bool Symbol(char a)
{
	bool ok;
	switch (a)
	{
	case '?': ok = false; break;
	case '*': ok = false; break;
	case '|': ok = false; break;
	case ':': ok = false; break;
	default: ok = true; break;
	}
	return ok;
}

//Проверка правильности имени
bool NameCorr(char *name)
{
	int i = 1;
	bool ok;
	if (name[0] != '\0')
	{
		ok = Symbol(name[0]);
		//проверка строки
		while (name[i] != '\0' && ok) 
			ok = Symbol(name[i++]);
	}
	return ok;
}

//Ввод имени файла
bool InputFName(char *name)
{
	bool ok = false;
	cin >> name;
	if (NameCorr(name))
		ok = true;
	return ok;
}

//Чтение матрицы из файла
float **ReadMatrFromFile(char *fname, int *m, int *n)
{
	FILE *f = fopen(fname, "r");
	float **matr;
	if (f == NULL)
	{
		matr = NULL;
		cout << "Ошибка" << endl;
	}
	else
	{
		//Считываем размер матрицы и проверяем корректность
		if (fscanf(f, "%d %d\n", m, n) != 2)
		{
			matr = NULL;
			cout << "Ошибка" << endl;
		}
		else
		{
			matr = Memory(*m, *n);
			//Считываение матциры поэлементно
			for (int i = 0; i < *m; i++)
			{
				for (int j = 0; j < *n; j++)
					if (fscanf(f, "%f", &matr[i][j]) != 1) //Считываем элемент и проверяем корректность
					{
						matr = NULL;
						cout << "Ошибка" << endl;
						break;
					}
			}
		}
	}
	fclose(f);
	return matr;
}

//Удаление матрицы из памяти 
void Del(float **matr, const int m)
{
	for (int i = 0; i < m; i++)
		delete[] matr[i];
	delete[] matr;
	matr = NULL;
}

//Вывод матрицы на экран
void PrintMatr(float **matr, const int m, const int n)
{
	cout << "__________________" << endl;
	for (int i = 0; i < m; i++)
	{
		if (matr[i] != NULL) //Проверка указателя на пустоту
		{
			for (int j = 0; j < n; j++)
				cout << matr[i][j] << " ";
			cout << endl;
		}
	}
	cout << "__________________" << endl;
	cout << endl;
}

//Запись матрицы в файл
void WriteMatrInFile(char *fname, float **matr, const int m, const int n)
{
	FILE *f = fopen(fname, "w");
	if (f == NULL)
		cout << "Ошибка" << endl;
	else
	{
		int i;
		fprintf(f, "%d %d\n", m, n);
		for (i = 0; i < m; i++)
		{
			if (matr[i] != NULL)
			{
				for (int j = 0; j < n; j++)
					fprintf(f, "%1.2f ", matr[i][j]);

				fprintf(f, "\n");
			}
		}
	}
	fclose(f);
}

//Транспонирование матрицы. Элемент, стоящий на i, j позиции в исходной матрице становится на j, i позицию во второй матрице
float **Transposition(float **matr, const int m, const int n)
{
	float **matr2;
	matr2 = Memory(n, m);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			matr2[j][i] = matr[i][j];
	return matr2;	
}

//Интерфейс программы
void Menu(int *m, int *n)
{
	float **matr = NULL;
	float **matr2 = NULL;
	int a;
	const int N = 2;
	char filename[] = "";
	cout << "1 - Ввести матрицу самому" << endl;
	cout << "2 - Считать матрицу из файла" << endl;
	cout << "0 - Выйти из программы" << endl;
	cout << "Ваше решение:";
	do
	{
		cin >> a;
	} while ((a < 0) || (a > N)); //Пока команда не будет введена верно
	switch (a)
	{
	case 1:
		matr = ReadMatrFromCon(m, n); 
		break;

	case 2:
	{
		cout << "Введите имя файла" << endl;
		if (InputFName(filename))
			matr = ReadMatrFromFile(filename, m, n);
		else
		{
			cout << "Некорректное имя файла" << endl;
			matr = NULL;
		}
	cout << "Исходная матрица" << endl;
	PrintMatr(matr, *m, *n);
	}
	break;

	default:
		matr = NULL;
		break;
	}

	if (matr != NULL) //Если матрица не пуста
	{
		cout << "Транспонированная матрица" << endl;
		matr2 = Transposition(matr, *m, *n);
		PrintMatr(matr2, *n, *m);
		cout << "Выберите дальнейшее действие:" << endl;
		cout << "1 - Записать результат в файл" << endl;
		cout << "0 - Выход:" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
		{
			cout << "Введите имя файла" << endl;
			if (InputFName(filename))
			{
				WriteMatrInFile(filename, matr2, *n, *m);
				cout << "Данные записаны" << endl;
			}
			else
			{
				cout << "Некорректное имя файла" << endl;
				matr = NULL;
			}
			
		}
		break;
		}
		//Удаление обеих матриц для очистки памяти
		Del(matr, *m);
		Del(matr2, *n);
	}
}





int main()
{
	setlocale(LC_ALL, "Russian");
	int M, N;
	Menu(&M, &N);
	system("pause");
	return 0;
}

