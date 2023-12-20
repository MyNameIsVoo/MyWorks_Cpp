#pragma once

void XiSquareDistributionMethod(int N, int left, int right, int step);

void InitXiSquareDistributionMethod()
{
	cout << "\t\tМоделирование распределения Хи-квадрат" << endl << endl;

	XiSquareDistributionMethod(100, 0, 1, 6);
}

void XiSquareDistributionMethod(int N, int left, int right, int step)
{
	cout << "\t\tКоличество моделируемых значений: " << N << endl << endl;
	cout << "\t\tПараметры распределения: Norm[" << left << "," << right << "]" << endl << endl;
	cout << "\t\tСтепень свободы: " << step << endl << endl;

	int k, kol, j;
	float* Norm = new float[N], summ = 0, MO = 0, sko = 0, *Xi = new float[N];
	float l_border = 0, r_border = 0, h = 0, *Pi = new float[N], *Coord = new float[N], max, min;

	// Равномерное распределение
	MO = (left + right) * 0.5; 
	sko = (MO - left) / 3.0;

	// Закон нормального распределения
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < 25; j++)
			summ += 1.0 * rand() / RAND_MAX;

		Norm[i] = (sqrt(2.0) * (sko) * (summ - 12.5)) / 1.99661 + MO; 
		summ = 0;
	}

	// Заполняем массив Хи квадрата ( в зависимости от степени свободы )
	summ = kol = k = 0;
	do 
	{
		summ = 0; 
		j = 0;

		for (int i = k; i < N; i++) 
		{
			if (j > 5) 
				break;

			summ += pow(Norm[i], 2.0); 
			j++;
		}

		Xi[kol] = summ; 
		kol++; 
		k += step;
	} while (k < N);

	// Ищим екстремумы массива Хи квадрат
	max = min = Xi[0];
	for (int i = 0; i < kol; i++) 
	{
		if (max < Xi[i]) 
			max = Xi[i];
		if (min > Xi[i]) 
			min = Xi[i];
	}

	// Ищим вхождения в каждый интервал
	h = (max - min) * 0.1;
	l_border = kol = 0; 
	r_border = h;
	do 
	{
		k = 0;
		for (int i = 0; i < N; i++)
		{
			if (Xi[i] > l_border && Xi[i] < r_border)
				k++;
		}

		Pi[kol] = k / (float)N; 
		Coord[kol] = l_border; 
		kol++; 
		l_border = r_border;
		r_border += h;
	} while (r_border < max);

	Rav(N, Norm);

	delete[]Norm; 
	delete[]Pi; 
	delete[]Coord;
}