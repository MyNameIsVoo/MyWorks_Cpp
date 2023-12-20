#pragma once

#include "Includes.h"

void Example_1();
void Example_2();

void InitDynamicMethod()
{
	cout << "\t\tМетод динамического программирования для решения задач математического программирования" << endl << endl;

	cout << "\t\tВыберете пример 1 или 2" << endl << endl;
	int example = 1;
	do
	{
		cin >> example;
		if (example <= 0 || example > 2)
			cout << "\t\tВы ввели некорректное число\n\n";
		else
			break;

	} while (true);

	clock_t Time = clock();

	if (example == 1)
		Example_1();
	else
		Example_2();

	double EndTime = (clock() - (double)Time) / CLOCKS_PER_SEC;
	cout << "\n\n\t\tВремя выполнения: " << EndTime << endl;
}

void Example_1()
{
	bool paraller = false;

	cout << "\t\tВыберете каким способ решить задачу: 0 - последовательно, 1 - параллельно" << endl << endl;
	cin >> paraller;
	cout << "\t" << (paraller ? "Параллельное решение задачи" : "Последовательное решение задачи") << endl << endl;

	int sizegx = 5;
	int sizez = 5;

	float Gi[10][10], * Xi = new float[sizegx];

	for (int i = 0; i < sizegx; i++)
		Xi[i] = i;
	float mas[4][5] = { { 0, 0.2, 0.25, 0.4, 0.6 }, { 0, 0.15, 0.3, 0.45, 0.55 }, { 0, 0.1, 0.3, 0.55, 0.7 }, { 0, 0.22, 0.4, 0.5, 0.6 } };
	for (int i = 0; i < sizegx; i++)
		for (int j = 0; j < sizegx + 1; j++)
			Gi[i][j] = mas[i][j];

	int x1[5], x2[5], x3[5], x4[5], x[5];
	float V1[6], V2[6], V3[6], V4[6], maxIDs[2];
	int k = 0, z = sizez - 1, ID = 1;

	cout << "\t" << "Ограничения";
	for (int j = 0; j < sizegx; j++)
		cout << "\n\tg1[" << j << "] = " << Gi[0][j] << "\tg2[" << j << "] = " << Gi[1][j] << "\tg3[" << j << "] = " << Gi[2][j] << "\tg4[" << j << "] = " << Gi[3][j];
	cout << "\n\n";

	if (paraller)
	{
		V1[0] = Gi[0][0];
		V2[0] = Gi[1][0] + V1[0];
		V3[0] = Gi[2][0] + V2[0];
		V4[0] = Gi[3][0] + V3[0];

		x1[0] = Xi[0];
		x2[0] = 0;
		x3[0] = 0;
		x4[0] = 0;
		cout << "\tx1 = " << x1[0] << "\tx2 = " << x2[0] << "\tx3 = " << x3[0] << "\tx4 = " << x4[0] << endl;

		for (int i = 1; i < sizegx; i++)
		{
			// V1
			V1[i] = Max(Gi[0][i], V1[i - 1]);
			x1[i] = Xi[i];

			// V2
			m(Gi, V1, i, 1, maxIDs);
			V2[i] = maxIDs[0];
			ID = (int)maxIDs[1];
			x2[i] = (int)ID == 0 ? 0 : int(ID);

			// V3
			m(Gi, V2, i, 2, maxIDs);
			V3[i] = maxIDs[0];
			ID = (int)maxIDs[1];
			x3[i] = ID == 0 ? 0 : int(ID);

			// V4
			m(Gi, V3, i, 3, maxIDs);
			V4[i] = maxIDs[0];
			ID = (int)maxIDs[1];
			x4[i] = ID == 0 ? 0 : int(ID);

			// Xi
			cout << "\tx1 = " << x1[i] << "\tx2 = " << x2[i] << "\tx3 = " << x3[i] << "\tx4 = " << x4[i] << endl;
		}
		delete[]Xi;
	}
	else
	{
		V1[0] = Gi[0][0];
		x1[0] = Xi[0];
		cout << "\tx1 = " << x1[0];

		for (int i = 1; i < sizegx; i++)
		{
			x1[i] = Xi[i];
			V1[i] = Max(Gi[0][i], V1[i - 1]);
			cout << "\tx1 = " << x1[i];
		}
		delete[]Xi;

		cout << "\n";
		V2[0] = Gi[1][0] + V1[0];
		x2[0] = 0;
		cout << "\tx2 = " << x2[0];
		for (int i = 1; i < sizez; i++)
		{
			m(Gi, V1, i, 1, maxIDs);
			V2[i] = maxIDs[0];
			ID = (int)maxIDs[1];

			x2[i] = (int)ID == 0 ? 0 : int(ID);
			cout << "\tx2 = " << x2[i];
		}

		cout << "\n";
		V3[0] = Gi[2][0] + V2[0];
		x3[0] = 0;
		cout << "\tx3 = " << x3[0];
		for (int i = 1; i < sizez; i++)
		{
			m(Gi, V2, i, 2, maxIDs);
			V3[i] = maxIDs[0];
			ID = (int)maxIDs[1];

			x3[i] = ID == 0 ? 0 : int(ID);
			cout << "\tx3 = " << x3[i];
		}

		cout << "\n";
		V4[0] = Gi[3][0] + V3[0];
		x4[0] = 0;
		cout << "\tx4 = " << x4[0];
		for (int i = 1; i < sizez; i++)
		{
			m(Gi, V3, i, 3, maxIDs);
			V4[i] = maxIDs[0];
			ID = (int)maxIDs[1];

			x4[i] = ID == 0 ? 0 : int(ID);
			cout << "\tx4 = " << x4[i];
		}
		cout << "\n";
	}

	for (int j = 0; j < sizez; j++)
		cout << "\n\tV1[" << j << "] = " << V1[j] << "\tV2[" << j << "] = " << V2[j] << "\tV3[" << j << "] = " << V3[j] << "\tV4[" << j << "] = " << V4[j];
	cout << "\n\n";

	x[0] = x4[z];
	z = z - x[0];
	cout << "\n\tz = " << z << "\t x4 = " << x[0];

	x[1] = x3[z];
	z = z - x[1];
	cout << "\n\tz = " << z << "\t x3 = " << x[1];

	x[2] = x2[z];
	z = z - x[2];
	cout << "\n\tz = " << z << "\t x2 = " << x[2];

	x[3] = x1[z];
	z = z - x[3];
	cout << "\n\tz = " << z << "\t x1 = " << x[3];
}

void Example_2()
{
	int sizegx = 3;
	int sizez = 3;
	int z = 10;

	float Gi[10][10];

	float mas2[2][3] = { { 2, 3, 4 }, { 10, 20, 30 } };
	for (int i = 0; i < sizegx; i++)
		for (int j = 0; j < sizegx; j++)
			Gi[i][j] = mas2[i][j];

	float V1[11], V2[11], V3[11];
	int k = 0, kol = 0, alpha = 0, j = 1, X[3][11], x[11];

	cout << "\t\tИсходные данные" << endl;
	for (int j = 0; j < sizegx; j++)
		cout << "\n\tn = " << j + 1 << "\tw[" << j << "] = " << Gi[0][j] << "\tc[" << j << "] = " << Gi[1][j];
	cout << "\n\nz = " << z << endl;

	do
	{
		if (kol == z + 1)
		{
			kol = 0;
			j++;
			cout << "\n\n";
		}

		if (j == 1)
		{
			alpha = kol / Gi[0][0];
			X[0][kol] = alpha;
			if (kol == 0 || kol == 1)
				V1[kol] = Max(0, Gi[1][0] * alpha);
			else
				V1[kol] = Max3(Gi[1][0], alpha);

			cout << "\n\tz = " << kol << "\t alpha[" << kol << "] = " << alpha << "\tV1 = " << V1[kol] << "\tx1[" << kol << "] = " << X[0][kol];
		}

		if (j == 2)
		{
			alpha = kol / Gi[0][1];
			X[1][kol] = alpha;
			V2[kol] = Max4(Gi[1][1], Gi[0][1], V1, alpha, kol);

			cout << "\n\tz = " << kol << "\t alpha[" << kol << "] = " << alpha << "\tV2 = " << V2[kol] << "\tx2[" << kol << "] = " << X[1][kol];
		}

		if (j == 3)
		{
			alpha = kol / Gi[0][2];
			X[2][kol] = alpha;
			V3[kol] = Max4(Gi[1][2], Gi[0][2], V2, alpha, kol);

			cout << "\n\tz = " << kol << "\t alpha[" << kol << "] = " << alpha << "\tV3 = " << V3[kol] << "\tx3[" << kol << "] = " << X[2][kol];
		}

		kol++;
	} while (j < 4);

	z = 10;
	for (int i = 0, j = sizez - 1; i < sizez; i++, j--)
	{
		x[i] = X[j][z];
		z = z - Gi[0][2] * x[i];
		cout << "\n\tx = " << x[i] << "\tz = " << z;
	}
}