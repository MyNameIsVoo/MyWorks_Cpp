#pragma once

/// <summary>
/// 
/// </summary>
/// <param name="N">Количество моделируемых значений</param>
/// <param name="left">левая граница распределения Rav</param>
/// <param name="right">правая граница распределения Rav</param>
/// <param name="option">вариант</param>
/// <param name="time">время</param>
/// <param name="sigma">сигма</param>
/// <param name="h">шаг</param>
void FormationOfRandomProcessFromWhiteNoise(int N, int left, int right, int option, int time, float sigma, float H);
void ExperimentalMethodForObtainingRandomProcessesFromWhiteNoise(int N, int left, int right, int option, int time, float sigma, float H, float V, float l);

//
//
//

void InitFormationOfRandomProcessFromWhiteNoise()
{
	cout << "\t\tФормирование из белого шума случайного процесса с корреляционной функцией" << endl << endl;

	FormationOfRandomProcessFromWhiteNoise(100, 0, 1, 4, 50, 10, 0.1);
}

void FormationOfRandomProcessFromWhiteNoise(int N, int left, int right, int option, int time, float sigma, float H)
{
	float* Ravn = new float[N];
	for (int i = 0; i < N; i++)
		Ravn[i] = 1.0 * rand() / (RAND_MAX + 1); // от 0 до 1

	float max = Ravn[0], min = Ravn[0];
	for (int i = 0; i < N; i++)
	{
		if (max < Ravn[i])
			max = Ravn[i];
		if (min > Ravn[i])
			min = Ravn[i];
	}

	float h = (max - min) / (10.0);
	cout << "\t\tШаг распределения: " << h << endl << endl;

	float* Pi = new float[20], *Coord = new float[20];
	float l_border = 0;
	float r_border = h;
	int k = 0, kol = 0;
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

	cout << "\n\n";

	float k1, k2, k3, k4, dy = 0, y = 0, sum = 0, summ = 0;
	float mg = 0, Dg = 0, ky = 0;

	float alpha = (float)option * 0.5;
	float k11 = (sigma * sqrt(alpha * 2.0) / H);
	k11 += k11 * 0.25;

	cout << " \n\n\t\t k11 " << k11 << endl << endl;

	float* Y = new float[N];
	float* KY = new float[N];
	k = 0;
	do
	{
		k1 = k11 * Ravn[k] - alpha * y;
		k2 = k11 * Ravn[k] - alpha * (y + k1 * H * 0.5);
		k3 = k11 * Ravn[k] - alpha * (y + k2 * H * 0.5);
		k4 = k11 * Ravn[k] - alpha * (y + k3 * H * 0.5);

		dy = (H / 6) * (k1 + 2 * (k2 + k3) + k4);
		y += dy;

		cout << "y = " << y << endl;

		sum += y;
		Y[k] = y;

		if (k > 1)
		{
			mg = sum * (1.0 / (k));
			summ += pow((y - mg), 2.0);
			Dg = summ * (1.0 / (k - 1.0));
			ky = pow(sigma, 2.0) * exp(-alpha * (k * 0.1));
		}

		k++;
	} while (k < N);

	cout << "\n\n\n\t mx = " << mg;
	cout << "\n\t Dx = " << Dg;

	float SUMM = 0, kx = 0;
	for (int i = 2; i < N - 1; i++)
	{
		sum += Y[i];
		mg = sum * (1.0 / (i));
		SUMM = pow((Y[i + 1] - mg), 2.0);
		kx = KY[i] * SUMM * (-1.0);
	}

	delete[]Ravn;
	delete[]Pi;
	delete[]Coord;
	delete[]Y;
	delete[]KY;
}

//
//
//

void InitExperimentalMethodForObtainingRandomProcessesFromWhiteNoise()
{
	cout << "\t\tЭкспериментальный метод получения случайных процесса, описывающего вертикальную турбулентность атмосферы с заданными статистическими характеристиками путем пропускания белого шума через формирующий фильтр" << endl << endl;

	ExperimentalMethodForObtainingRandomProcessesFromWhiteNoise(100, 0, 1, 4, 50, 4, 0.01, 300, 700);
}

void ExperimentalMethodForObtainingRandomProcessesFromWhiteNoise(int N, int left, int right, int option, int time, float sigma, float H, float V, float l)
{
	int k = 0, kol = 0;
	float* Ravn = new float[N];
	for (int i = 0; i < N; i++)
		Ravn[i] = 1.0 * rand() / (RAND_MAX + 1); // от 0 до 1

	float *Pi = new float[20], *Coord = new float[20], max = Ravn[0], min = Ravn[0];

	for (int i = 0; i < N; i++)
	{
		if (max < Ravn[i])
			max = Ravn[i];
		if (min > Ravn[i])
			min = Ravn[i];
	}

	float h = (max - min) * 0.1;
	cout << "\t\tШаг распределения: " << h << endl << endl;

	float l_border = 0;
	float r_border = h;
	do
	{
		k = 0;
		for (int i = 0; i < N; i++)
			if (Ravn[i] > l_border && Ravn[i] < r_border)
				k++;
		Pi[kol] = k / (float)N;
		Coord[kol] = l_border;
		kol++;
		l_border = r_border;
		r_border += h;
	} while (r_border < max);

	Rav(N, Ravn);

	cout << "\n\n";

	float k1, k2, k3, k4, k11, k12, k13, k14, dy1 = 0, dy2 = 0, y = 0, sum = 0, summ = 0, SUMM = 0;
	float u = 0, u1 = 0, mg = 0, Dg = 0, ky = 0, kx = 0, c1, c2, c3, c4;
	int Num, Time;

	float *Y = new float[N];
	float *KY = new float[N];

	float alpha = 0.5;
	float betta = 0.6;

	k = 0;
	do
	{
		c1 = sigma * sqrt(3.0) * sqrt(V / l);
		c2 = 2 * V / l;
		c3 = pow(V, 2.0) / pow(l, 2.0);
		c4 = -abs(2.0 * sqrt(3.0) - 1.0) * sigma * (V / l) * sqrt(V / l);

		k1 = u1 + c1 * Ravn[k];
		k11 = -c2 * u1 - c3 * u + c4 * Ravn[k] / sqrt(h);

		k2 = (u1 + k11 * h * 0.5) + c1 * Ravn[k];
		k12 = -c2 * (u1 + k11 * h * 0.5) - c3 * (u + k1 * h * 0.5) + c4 * Ravn[k] / sqrt(h);

		k3 = (u1 + k12 * h * 0.5) + c1 * Ravn[k];
		k13 = -c2 * (u1 + k12 * h * 0.5) - c3 * (u + k2 * h * 0.5) + c4 * Ravn[k] / sqrt(h);

		k4 = (u1 + k13 * h * 0.5) + c1 * Ravn[k];
		k14 = -c2 * (u1 + k13 * h * 0.5) - c3 * (u + k3 * h * 0.5) + c4 * Ravn[k] / sqrt(h);

		dy1 = (h / 6.0) * (k1 + 2 * (k2 + k3) + k4);
		dy2 = (h / 6.0) * (k11 + 2 * (k12 + k13) + k14);

		u += dy1;
		u1 += dy2;

		sum += Ravn[k];
		Y[k] = u1;

		if (k > 1)
		{
			mg = sum * (1.0 / (k));
			summ += pow((Ravn[k] - mg), 2.0);
			Dg = summ * (1.0 / (k - 1.0));
			ky = pow(sigma, 2.0) * exp(-abs(k * 0.1) * V / l) * (1.0 - abs(k * 0.1) * V / (2.0 * l));
			KY[k] = ky;
		}

		k++;
	} while (k < N);

	cout << "\n\n\n\t mx = " << mg * 100;
	cout << "\n\t Dx = " << Dg * 1000;

	for (int i = 2; i < N - 1; i++)
	{
		sum += Y[i];
		mg = sum * (1.0 / (i));
		SUMM = pow((Y[i + 1] - mg), 2.0);
		kx = KY[i] * SUMM;
	}

	delete[]Ravn;
	delete[]Pi;
	delete[]Coord;
	delete[]Y;
	delete[]KY;
}