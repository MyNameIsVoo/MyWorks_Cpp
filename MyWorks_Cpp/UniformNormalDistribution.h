#pragma once

void UniformDistribution(int N, int left, int right);
void NormalDistribution(int N, int left, int right);
void NormalDistributionWithGivenDensity(int N, int left, int right, double betta, double sigma);

void InitUniformNormalDistribution()
{
	cout << "\t\tМоделирование независимых случайных величин имеющих равномерное и нормальное распределение" << endl << endl;

	cout << "\t\tВыберете метод распределения: 1 - равномерное, 2 - нормальное (Гауссовское), 3 - нормальное (с заданной плотностью)" << endl << endl;
	int method = 1;
	do
	{
		cin >> method;
		if (method <= 0 || method > 3)
			cout << "\t\tВы ввели некорректное число\n\n";
		else
			break;

	} while (true);

	clock_t Time = clock();

	if (method == 1)
		UniformDistribution(100, 0, 1);
	else if (method == 2)
		NormalDistribution(1000, 0, 1);
	else if (method == 3)
		NormalDistributionWithGivenDensity(1000, 0, 1, 1, 1);

	double EndTime = (clock() - (double)Time) / CLOCKS_PER_SEC;
	cout << "\n\n\t\tВремя выполнения: " << EndTime << endl;
}

void UniformDistribution(int N, int left, int right)
{
	cout << "\t\tРавномерное распределение" << endl << endl;

	int k = 0, kol = 0;
	float* Ravn = new float[N];

	// Равномерное распределение
	for (int i = 0; i < N; i++)
		Ravn[i] = 1.0 * rand() / (RAND_MAX + 1); // от 0 до 1

	float l_border = 0, r_border = 0, h = 0, * Pi = new float[20], *Coord = new float[20], max = Ravn[0], min = Ravn[0];

	for (int i = 0; i < N; i++) 
	{
		if (max < Ravn[i]) 
			max = Ravn[i];
		if (min > Ravn[i]) 
			min = Ravn[i];
	}

	h = (max - min) * 0.1;
	cout << "\t\tШаг распределения: " << h << endl << endl;

	l_border = 0;
	r_border = h;
	do 
	{
		k = 0;
		for (int i = 0; i < N; i++)
		{
			if (Ravn[i] > l_border && Ravn[i] < r_border)
				k++;
		}

		Pi[kol] = k / (float)N;
		Coord[kol] = l_border;
		kol++;
		l_border = r_border; 
		r_border += h;
	} while (r_border < max);

	Rav(N, Ravn);

	delete[]Ravn; 
	delete[]Pi; 
	delete[]Coord;
}

void NormalDistribution(int N, int left, int right)
{
	cout << "\t\tНормальное распределение (Гауссовское)" << endl << endl;

	int k = 0, kol = 0;
	float* Norm = new float[N], summ = 0, MO = 0, sko = 0;
	float l_border = 0, r_border = 0, h = 0, * Pi = new float[N], * Coord = new float[N], max, min;

	MO = (left + right) / 2.0; sko = (MO - left) / 3.0;

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < 25; j++)
			summ += 1.0 * rand() / RAND_MAX;

		Norm[i] = (sqrt(2.0) * (sko) * (summ - 12.5)) / 1.99661 + MO;
		summ = 0;
	}

	max = Norm[0]; min = Norm[0];

	for (int i = 0; i < N; i++) 
	{
		if (max < Norm[i]) 
			max = Norm[i];
		if (min > Norm[i]) 
			min = Norm[i];
	}

	h = (max - min) * 0.1;
	cout << "\t\tШаг распределения: " << h << endl << endl;

	l_border = 0; 
	r_border = h;
	do 
	{
		k = 0;
		for (int i = 0; i < N; i++)
		{
			if (Norm[i] > l_border && Norm[i] < r_border)
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

void NormalDistributionWithGivenDensity(int N, int left, int right, double betta, double sigma)
{
	cout << "\t\tНормальное распределение (с заданной плотностью)" << endl << endl;

	int k = 0, kol = 0;
	float* Norm = new float[N], summ = 0, MO = 0, sko = 0;
	float l_border = 0, r_border = 0, h = 0, * Pi = new float[N], * Coord = new float[N], max, min;

	float vsp = 0, p = 0;

	MO = (left + right) / 2.0;
	sko = (MO - left) / 3.0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 25; j++)
			summ += 1.0 * rand() / (RAND_MAX + 1.0);

		Norm[i] = (sqrt(2.0) * (sko) * (summ - 12.5)) / 1.99661 + MO;
		Norm[i] = (Norm[i] + Norm[i]) / 2.0;

		// Равномерное распределение
		p = rand() % 2;

		if (p == 0)
			vsp = 1.0;
		if (p == 1)
			vsp = -1.0;

		Norm[i] = Norm[i] * sqrt(sigma) + betta * vsp;

		summ = 0;
	}

	max = Norm[0];
	min = Norm[0];

	for (int i = 0; i < N; i++)
	{
		if (max < Norm[i])
			max = Norm[i];
		if (min > Norm[i])
			min = Norm[i];
	}

	h = (max - min) / (40.0);
	cout << "\t\tШаг распределения: " << h << endl << endl;

	l_border = min;
	r_border = min + h;

	do
	{
		k = 0;
		for (int i = 0; i < N; i++)
		{
			if (Norm[i] > l_border && Norm[i] < r_border)
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