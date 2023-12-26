#pragma once

#include "Includes.h"

void CalculateMathematicalModelOfAnUnguidedRocket(struct DataSettings data);
double GetRandomWindSpeed(struct DataSettings data);

struct DataSettings
{
	// �������� ���������
	double d; // ������ (�������)
	double mn; // ������ ��� (��)
	double w; // ��� ������� (��)
	double t; // ����� ������� ������� (�)
	double S; // ����� ������������ (�)
	double i; // ����������� �����
	double Tetta; // ���� ������� ������������ (���)
	double Ue; // ����������� �������� ��������� (�����)
	double h; // ��� ��������������

	// �����
	bool UseWind;
	double WindSpeed; // �������� �����
	bool RandomWindSpeed;

	// ������ ��������� �����������
	double Va; // �������� �� �� �������� �������
	double Q; // ��������� �������� ������ (��\�)
	double R; // ���������� ���� (�)
	double Sm; // ������� ������ (�2)
	double CxEt; // ����������� �������� ������������� ���������� ��
	double Cx; // ������� �������� ����� �������� �������������
	double g; // ���������� ���������� �����
	double ftr; // ����������� ������ �� �� ��� ������������ (��� �����)

	// ���������� �������������
	int N; // ����� ��������
	int left; // ������ ������������� (�� ��������� = - WindSpeed)
	int right; // ������ ������������� (�� ��������� = WindSpeed) 
};

void InitMathematicalModelOfAnUnguidedRocket()
{
	cout << "\t\t���������� �������������� ������ �������������� ����������� ������� (��)" << endl << endl;

	clock_t Time = clock();

	struct DataSettings data;

	// ��������
	data.d = 0.12;
	data.mn = 40;
	data.w = 6.5;
	data.t = 0.65;
	data.S = 4;
	data.i = 1.4;
	data.Tetta = 45 * M_PI / 180.0;
	data.Ue = 2000;
	data.h = 0.1;

	// �����
	data.UseWind = false;
	data.WindSpeed = 15;
	data.RandomWindSpeed = true;

	// ������ ��������� �����������
	data.Va = data.Ue * data.w / data.mn;
	data.Q = data.w / data.t;
	data.R = data.Ue * data.Q;
	data.Sm = M_PI * pow(data.d, 2.0) / 4.0;
	data.CxEt = 0.157;
	data.Cx = data.CxEt * data.i;
	data.g = 9.81;
	data.ftr = 0.15;
	
	// ���������� �������������
	data.N = 100;
	data.left = -data.WindSpeed;
	data.right = data.WindSpeed;

	CalculateMathematicalModelOfAnUnguidedRocket(data);

	double EndTime = (clock() - (double)Time) / CLOCKS_PER_SEC;
	cout << "\n\n\t\t����� ����������: " << EndTime << endl;
}

void CalculateMathematicalModelOfAnUnguidedRocket(struct DataSettings data)
{
	double Vd, Td, Tetta_a, ya, xa, Vp, Tetta_p, yp, xp;
	float m = 0, k0 = 0, ln = 0, T0 = 0, t0 = 0;

	cout << setprecision(5) << "\n\n\td = " << data.d << "\n\tm0 = " 
		<< data.mn << "\n\tw = " << data. w << "\n\tt = " << data.t << "\n\tS = "
		<< data.S << "\n\ti = " << data.i << "\n\tTetta = " << data.Tetta << "\n\tUe = " 
		<< data.Ue << "\n\tVa = Ue * w / m0 = " << data.Va << "\n\tQ = w / t = " << data.Q << "\n\tR = Ue * Q = " 
		<< data.R << "\n\tSm = Pi * d^2 / 4 = " << data.Sm << "\n\tCx = CxEtalon * i = " << data.Cx << endl << endl;
	
	if (data.UseWind || data.RandomWindSpeed)
	{
		// ��������� �������� ����� (����������� �������������)
		if (data.RandomWindSpeed)
			data.WindSpeed = GetRandomWindSpeed(data);
		cout << "\t\t�������� ����� = " << data.WindSpeed << endl;
	}

	cout << "\n\t\t�������� �� ������������" << endl;
	k0 = (((data.R) / data.mn) - data.g * sin(data.Tetta) - data.ftr * data.g * cos(data.Tetta));
	t0 = sqrt(2 * data.S / k0);
	T0 = t0;
	Vd = sqrt(2 * data.R * data.S / data.mn);
	cout << "\n\t\t�������� ����� � ������������ [Vd] = " << Vd << "\n\t\t����� ����� � ������������ [td] = " << t0;
	cout << "\n\t\t�������� ����� � ������������ [Vd] = " << data.Ue * log(data.mn / (data.mn - data.w)) << " (�� ������� ������������)";

	float k11 = 0, k12 = 0, k13 = 0, k14 = 0, k21 = 0, k22 = 0, k23 = 0, k24 = 0, k31 = 0, k32 = 0, k33 = 0, k34 = 0, k41 = 0, k42 = 0, k43 = 0, k44 = 0, dy1 = 0, dy2 = 0, dy3 = 0, dy4 = 0;
	int k = 1;

	// ������ ���������� � ��������� ��������

	// 0-�� �������� ��� ����� (���� �� ������)
	int amountIterations = (data.UseWind || data.RandomWindSpeed) ? 3 : 1;
	for (int i = 0; i < amountIterations; i++)
	{
		k = 0;
		data.Va = Vd;
		Tetta_a = data.Tetta;
		ya = xa = 0;
		t0 = T0;
		m = data.mn - data.Q * t0;
		if (i == 2)
			data.WindSpeed = -data.WindSpeed;

		cout << "\n\n\t\t������ ��������� �������" << endl;
		if (data.UseWind || data.RandomWindSpeed)
			cout << "\t\t� ������ " << (i == 1 ? "��������������" : "��������������") << " �����" << endl;
		do
		{
			cout << "\n\tk = " << k << "\tVa = " << data.Va << "\tTetta_a = " << Tetta_a << "\tya = " << ya << "\txa = " << xa;

			double windSpeedComponent = ((data.UseWind || data.RandomWindSpeed) && i != 0) ? (data.WindSpeed * cos(Tetta_a)) : 0;

			/*Va*/ k11 = -((0.5 * data.Cx * exp(-ya / 7800) * data.Sm * pow(data.Va + windSpeedComponent, 2.0)) / m) - (data.g * sin(Tetta_a)) + data.R / m;
			/*Ta*/ k12 = -data.g * cos(Tetta_a) / data.Va;
			/*ya*/ k13 = data.Va * sin(Tetta_a);
			/*xa*/ k14 = data.Va * cos(Tetta_a);

			k21 = -((0.5 * data.Cx * exp(-(ya + k13 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va + windSpeedComponent, 2.0) + k11 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0)) + data.R / m;
			k22 = -data.g * cos(Tetta_a + k12 * data.h / 2.0) / (data.Va + k11 * data.h / 2.0);
			k23 = (data.Va + k11 * data.h / 2.0) * sin(Tetta_a + k12 * data.h / 2.0);
			k24 = (data.Va + k11 * data.h / 2.0) * cos(Tetta_a + k12 * data.h / 2.0);

			k31 = -((0.5 * data.Cx * exp(-(ya + k23 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va + windSpeedComponent, 2.0) + k21 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0)) + data.R / m;
			k32 = -data.g * cos(Tetta_a + k22 * data.h / 2.0) / (data.Va + k21 * data.h / 2.0);
			k33 = (data.Va + k21 * data.h / 2.0) * sin(Tetta_a + k22 * data.h / 2.0);
			k34 = (data.Va + k21 * data.h / 2.0) * cos(Tetta_a + k22 * data.h / 2.0);

			k41 = -((0.5 * data.Cx * exp(-(ya + k33 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va + windSpeedComponent, 2.0) + k31 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0)) + data.R / m;
			k42 = -data.g * cos(Tetta_a + k32 * data.h / 2.0) / (data.Va + k31 * data.h / 2.0);
			k43 = (data.Va + k31 * data.h / 2.0) * sin(Tetta_a + k32 * data.h / 2.0);
			k44 = (data.Va + k31 * data.h / 2.0) * cos(Tetta_a + k32 * data.h / 2.0);

			dy1 = (data.h / 6) * (k11 + 2 * (k21 + k31) + k41);
			dy2 = (data.h / 6) * (k12 + 2 * (k22 + k32) + k42);
			dy3 = (data.h / 6) * (k13 + 2 * (k23 + k33) + k43);
			dy4 = (data.h / 6) * (k14 + 2 * (k24 + k34) + k44);

			data.Va += dy1;
			Tetta_a += dy2;
			ya += dy3;
			xa += dy4;

			t0 += data.h;
			m = data.mn - data.Q * t0;
			k++;
		} while (data.t >= t0);

		cout << "\n\n\t\t������ ���������� �������" << endl;
		if (data.UseWind || data.RandomWindSpeed)
			cout << "\t\t� ������ " << (i == 1 ? "��������������" : "��������������") << " �����" << endl;
		do
		{
			cout << "\n\tk = " << k << "\tVa = " << data.Va << "\tTetta_a = " << Tetta_a << "\tya = " << ya << "\txa = " << xa;

			double windSpeedComponent = ((data.UseWind || data.RandomWindSpeed) && i != 0) ? (data.WindSpeed * cos(Tetta_a)) : 0;

			/*Va*/ k11 = -((0.5 * data.Cx * exp(-ya / 7800) * data.Sm * pow(data.Va - windSpeedComponent, 2.0)) / m) - (data.g * sin(Tetta_a));
			/*Ta*/ k12 = -data.g * cos(Tetta_a) / data.Va;
			/*ya*/ k13 = data.Va * sin(Tetta_a);
			/*xa*/ k14 = data.Va * cos(Tetta_a);

			k21 = -((0.5 * data.Cx * exp(-(ya + k13 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va - windSpeedComponent, 2.0) + k11 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0));
			k22 = -data.g * cos(Tetta_a + k12 * data.h / 2.0) / (data.Va + k11 * data.h / 2.0);
			k23 = (data.Va + k11 * data.h / 2.0) * sin(Tetta_a + k12 * data.h / 2.0);
			k24 = (data.Va + k11 * data.h / 2.0) * cos(Tetta_a + k12 * data.h / 2.0);

			k31 = -((0.5 * data.Cx * exp(-(ya + k23 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va - windSpeedComponent, 2.0) + k21 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0));
			k32 = -data.g * cos(Tetta_a + k22 * data.h / 2.0) / (data.Va + k21 * data.h / 2.0);
			k33 = (data.Va + k21 * data.h / 2.0) * sin(Tetta_a + k22 * data.h / 2.0);
			k34 = (data.Va + k21 * data.h / 2.0) * cos(Tetta_a + k22 * data.h / 2.0);

			k41 = -((0.5 * data.Cx * exp(-(ya + k33 * data.h / 2.0) / 7800) * data.Sm * (pow(data.Va - windSpeedComponent, 2.0) + k31 * data.h / 2.0)) / m) - (data.g * sin(Tetta_a + k12 * data.h / 2.0));
			k42 = -data.g * cos(Tetta_a + k32 * data.h / 2.0) / (data.Va + k31 * data.h / 2.0);
			k43 = (data.Va + k31 * data.h / 2.0) * sin(Tetta_a + k32 * data.h / 2.0);
			k44 = (data.Va + k31 * data.h / 2.0) * cos(Tetta_a + k32 * data.h / 2.0);

			dy1 = (data.h / 6) * (k11 + 2 * (k21 + k31) + k41);
			dy2 = (data.h / 6) * (k12 + 2 * (k22 + k32) + k42);
			dy3 = (data.h / 6) * (k13 + 2 * (k23 + k33) + k43);
			dy4 = (data.h / 6) * (k14 + 2 * (k24 + k34) + k44);

			data.Va += dy1;
			Tetta_a += dy2;
			ya += dy3;
			xa += dy4;

			t0 += data.h;
			k++;
		} while (ya > 0);
	}
}

double GetRandomWindSpeed(struct DataSettings data)
{
	int kol = 0, vsp = 0;
	float* Norm = new float[data.N], summ = 0;
	float max, min, * Pi = new float[100], * Coord = new float[100];
	double windSpeed;

	float MO = (data.left + data.right) / 2.0;
	float sko = (MO - data.left) / 3.0;

	for (int i = 0; i < data.N; i++)
	{
		for (int j = 0; j < 25; j++)
			summ += 1.0 * rand() / RAND_MAX;
		Norm[i] = (sqrt(2.0) * (sko) * (summ - 12.5)) / 1.99661 + MO;
		summ = 0;
	}

	max = Norm[0];
	min = Norm[0];

	for (int i = 0; i < data.N; i++)
	{
		if (max < Norm[i])
			max = Norm[i];
		if (min > Norm[i])
			min = Norm[i];
	}

	windSpeed = (max - min) / (10.0);

	delete[]Norm;

	return windSpeed;
}