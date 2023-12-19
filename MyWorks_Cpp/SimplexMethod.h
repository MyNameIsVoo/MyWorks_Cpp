#pragma once

#include "iostream"

using namespace std;

void MethodMax(int size1, int size2, float* L, float** mas);

void InitSimplexMethod()
{
	cout << "\t\tСимплекс-метод линейного программирования (поиск максимума)" << endl << endl;

	int size1 = 2;
	int size2 = 2;

	float* L = new float[size1]; // Целевая функция f(x)
	L[0] = 150;
	L[1] = 35;

	float** mas = new float* [size2]; // Ограничения
	for (int i = 0; i < size2; i++)
		mas[i] = new float[size1 + 3];
	mas[0][0] = 150;	// x1
	mas[0][1] = 200;	// x2
	mas[0][2] = -1;		// x3
	mas[0][3] = 0;		// x4
	mas[0][4] = 200;	// b

	mas[1][0] = 14;
	mas[1][1] = 4;
	mas[1][2] = 0;
	mas[1][3] = 1;
	mas[1][4] = 4;

	cout << "x = " << mas[0][size1 + 2] / (float)mas[0][0];
	cout << "\ty = " << mas[0][size1 + 2] / (float)mas[0][1] << endl;
	cout << "x = " << mas[1][size1 + 2] / (float)mas[1][0];
	cout << "\ty = " << mas[1][size1 + 2] / (float)mas[1][1] << endl << endl;

	MethodMax(size1, size2, L, mas);

	for (int i = 0; i < size2; i++)
		delete[] mas[i];
	delete[] L;
}

void MethodMax(int size1, int size2, float* L, float** mas) 
{
	float* fx = new float[size2 + 2]; float* fxnull = new float[size2 + 2];

	float** Null = new float* [size2];
	for (int i = 0; i < size2; i++)
		Null[i] = new float[size1 + 3];

	// Заполняем вспомогательные массивы
	for (int i = 0; i < size2; i++) 
	{
		for (int j = 0; j < size1 + 3; j++) 
		{
			Null[i][j] = mas[i][j]; 
			cout << "\t" << mas[i][j];
		}
		cout << "\n";
	}

	cout << "\n\n";

	for (int i = 0; i < size1 + 2; i++) 
	{
		fx[i] = i < size1 ? L[i] : 0;
		fxnull[i] = fx[i];

		cout << "\t" << fx[i];
	}

	float max = 0, *vsp = new float[size2]; // vsp - для вычисления отношений
	int k1 = 0, k2 = 0, k = 1, sign = 0; 
	bool flag = false;
	do 
	{
		cout << "\n\n\t\t Итерация - " << k << endl << endl;

		max = fx[0];
		for (int i = 0; i < size1 + 3; i++)
		{
			if (max <= fx[i])
			{
				max = fx[i];
				k1 = i; // Запоминаем индекс
			}
		}
		cout << "\t\t max = " << max << endl << endl;

		cout << "\t\t\t Отношение \n\n ";
		for (int i = 0; i < size2; i++) 
		{
			vsp[i] = mas[i][size2 + 2] / mas[i][k1];
			cout << "\tvsp = " << vsp[i];
		}

		max = vsp[0];
		for (int i = 0; i < size2; i++)
		{
			if (max <= vsp[i])
			{
				max = vsp[i];
				k2 = i; // Запоминаем индекс
			}
		}
		cout << "\t\t max = " << max << "\n\n";

		if (mas[k2][k1] != 1)
			for (int j = 0; j < size1 + 3; j++)
				mas[k2][j] = Null[k2][j] / Null[k2][k1];
		for (int i = 0; i < size2; i++)
			for (int j = 0; j < size1 + 3; j++)
				Null[i][j] = mas[i][j];
		for (int i = 0; i < size2; i++)
		{
			if (Null[i][k1] > 0) 
				sign = -1;
			else if (Null[i][k1] < 0) 
				sign = 1;

			if (i == k2) 
				continue;

			for (int j = 0; j < size1 + 3; j++)
				mas[i][j] = (Null[k2][j] * (sign * Null[i][k1])) + (-sign) * Null[i][j];
		}

		cout << "\n\n";
		for (int i = 0; i < size2; i++) 
		{
			for (int j = 0; j < size1 + 3; j++) 
			{
				Null[i][j] = mas[i][j];
				cout << "\t" << Null[i][j];
			}
			cout << "\n";
		}

		for (int i = 0; i < size1 + 2; i++)
			fx[i] = (fxnull[k1] * (Null[k2][i])) - fxnull[i];
		for (int i = 0; i < size1 + 2; i++) 
		{
			fxnull[i] = fx[i]; 
			cout << "\t" << fx[i];
		}

		flag = false;
		for (int i = 0; i < size1 + 2; i++)
		{
			if (fxnull[i] > 0)
			{
				flag = true; //Если есть положительные элементы в целевой функции, то продолжаем работу
				break;
			}
		}
		k++;
	} while (flag != false);

	cout << "\n\n\t\tОтвет\n\n";
	cout << "\tx1 = " << mas[0][size2 + 2];
	cout << "\tx2 = " << mas[1][size2 + 2];
	cout << "\tx3 = " << 0;
	cout << "\tx4 = " << 0;
	cout << "\tf(x) = " << L[0] * mas[0][size2 + 2] + L[1] * mas[1][size2 + 2];

	for (int i = 0; i < size2; i++)
		delete[] Null[i];
	delete[] vsp; 
	delete[] fx; 
	delete[] fxnull;
}