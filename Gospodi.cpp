// Gospodi.cpp: ���������� ����� ����� ��� ����������� ����������.
//17. ��� ������ ������� ������� ����������������� �������.
//�������� ������� �������, 9 ������

#include "stdafx.h"
#include <iostream>
using namespace std;

//�������� ������������� �������
float **Memory(const int s, const int c)
{
	float **matrix = new float *[s];
	for (int i = 0; i < s; i++)
		matrix[i] = new float[c];
	return matrix;
}

// ������ ������� � ���������� 
float **ReadMatrFromCon(int *s, int *c)
{
	cout << "���-�� ����� � ������� ";
	cin >> *s;
	cout << "���-�� �������� � ������� ";
	cin >> *c;
	float **matrix;
	if ((s <= 0) || (c <= 0))
	{
		cout << "�������� �����������" << endl;
		matrix = NULL;
	}
	else
	{
		matrix = Memory(*s, *c);
		cout << "������� ������� ���������" << endl;
		for (int i = 0; i < *s; i++)
			for (int j = 0; j < *c; j++)
				cin >> matrix[i][j];			
	}
	return matrix;
}

//�������� ������������ ��������
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

//�������� ������������ �����
bool NameCorr(char *name)
{
	int i = 1;
	bool ok;
	if (name[0] != '\0')
	{
		ok = Symbol(name[0]);
		//�������� ������
		while (name[i] != '\0' && ok) 
			ok = Symbol(name[i++]);
	}
	return ok;
}

//���� ����� �����
bool InputFName(char *name)
{
	bool ok = false;
	cin >> name;
	if (NameCorr(name))
		ok = true;
	return ok;
}

//������ ������� �� �����
float **ReadMatrFromFile(char *fname, int *m, int *n)
{
	FILE *f = fopen(fname, "r");
	float **matr;
	if (f == NULL)
	{
		matr = NULL;
		cout << "������" << endl;
	}
	else
	{
		//��������� ������ ������� � ��������� ������������
		if (fscanf(f, "%d %d\n", m, n) != 2)
		{
			matr = NULL;
			cout << "������" << endl;
		}
		else
		{
			matr = Memory(*m, *n);
			//����������� ������� �����������
			for (int i = 0; i < *m; i++)
			{
				for (int j = 0; j < *n; j++)
					if (fscanf(f, "%f", &matr[i][j]) != 1) //��������� ������� � ��������� ������������
					{
						matr = NULL;
						cout << "������" << endl;
						break;
					}
			}
		}
	}
	fclose(f);
	return matr;
}

//�������� ������� �� ������ 
void Del(float **matr, const int m)
{
	for (int i = 0; i < m; i++)
		delete[] matr[i];
	delete[] matr;
	matr = NULL;
}

//����� ������� �� �����
void PrintMatr(float **matr, const int m, const int n)
{
	cout << "__________________" << endl;
	for (int i = 0; i < m; i++)
	{
		if (matr[i] != NULL) //�������� ��������� �� �������
		{
			for (int j = 0; j < n; j++)
				cout << matr[i][j] << " ";
			cout << endl;
		}
	}
	cout << "__________________" << endl;
	cout << endl;
}

//������ ������� � ����
void WriteMatrInFile(char *fname, float **matr, const int m, const int n)
{
	FILE *f = fopen(fname, "w");
	if (f == NULL)
		cout << "������" << endl;
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

//���������������� �������. �������, ������� �� i, j ������� � �������� ������� ���������� �� j, i ������� �� ������ �������
float **Transposition(float **matr, const int m, const int n)
{
	float **matr2;
	matr2 = Memory(n, m);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			matr2[j][i] = matr[i][j];
	return matr2;	
}

//��������� ���������
void Menu(int *m, int *n)
{
	float **matr = NULL;
	float **matr2 = NULL;
	int a;
	const int N = 2;
	char filename[] = "";
	cout << "1 - ������ ������� ������" << endl;
	cout << "2 - ������� ������� �� �����" << endl;
	cout << "0 - ����� �� ���������" << endl;
	cout << "���� �������:";
	do
	{
		cin >> a;
	} while ((a < 0) || (a > N)); //���� ������� �� ����� ������� �����
	switch (a)
	{
	case 1:
		matr = ReadMatrFromCon(m, n); 
		break;

	case 2:
	{
		cout << "������� ��� �����" << endl;
		if (InputFName(filename))
			matr = ReadMatrFromFile(filename, m, n);
		else
		{
			cout << "������������ ��� �����" << endl;
			matr = NULL;
		}
	cout << "�������� �������" << endl;
	PrintMatr(matr, *m, *n);
	}
	break;

	default:
		matr = NULL;
		break;
	}

	if (matr != NULL) //���� ������� �� �����
	{
		cout << "����������������� �������" << endl;
		matr2 = Transposition(matr, *m, *n);
		PrintMatr(matr2, *n, *m);
		cout << "�������� ���������� ��������:" << endl;
		cout << "1 - �������� ��������� � ����" << endl;
		cout << "0 - �����:" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
		{
			cout << "������� ��� �����" << endl;
			if (InputFName(filename))
			{
				WriteMatrInFile(filename, matr2, *n, *m);
				cout << "������ ��������" << endl;
			}
			else
			{
				cout << "������������ ��� �����" << endl;
				matr = NULL;
			}
			
		}
		break;
		}
		//�������� ����� ������ ��� ������� ������
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

