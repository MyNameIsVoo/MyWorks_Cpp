#pragma once

#include "iostream"
#include <iomanip> /* setprecision */

#include <math.h>
#include<corecrt_math_defines.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

void Rav(int N, float* Rav);
float Max(float g, float V);
float* m(float g[10][10], float* V, int i, int p, float* Max_Id);
float m2(float g[10][10], float* V, int i, int p, int ID);
float Max3(float Gi, int a);
float Max4(float Gi, float w, float* V, int a, int z);

float Max(float g, float V)
{
	int k = 0;
	float max = 0;

	if (max < g)
		max = g;

	if (max < V)
		max = V;

	return max;
}

float* m(float g[10][10], float* V, int i, int p, float* Max_Id)
{
	Max_Id[0] = g[p][0] + V[i];
	Max_Id[1] = 0;

	for (int k = 0; k <= i; k++)
	{
		if (Max_Id[0] < g[p][k] + V[i - k])
		{
			Max_Id[0] = g[p][k] + V[i - k];
			Max_Id[1] = k;
		}
	}

	return Max_Id;
}

float m2(float g[10][10], float* V, int i, int p, int ID)
{
	float max = g[p][0] + V[i];

	for (int k = 0; k <= i; k++)
	{
		if (max < g[p][k] + V[i - k])
		{
			max = g[p][k] + V[i - k];
			ID = i;
		}
	}

	return ID;
}

float Max3(float Gi, int a)
{
	float max = Gi * 0;

	for (int i = 0; i <= a; i++)
	{
		if (max < Gi * i)
			max = Gi * i;
	}

	return max;
}
float Max4(float Gi, float w, float* V, int a, int z)
{
	float max = Gi * 0 + V[z - int(w) * 0];

	for (int i = 0; i <= a; i++)
	{
		if (max < Gi * i + V[z - int(w) * i])
			max = Gi * i + V[z - int(w) * i];
	}

	return max;
}

void Rav(int N, float* Rav)
{
	cout << setprecision(3) << "\n\t\tРаспределение\n\n";
	for (int i = 0; i < N; i++)
		cout << "\t " << Rav[i];
	
	cout << "\n\n\t\t\n\n";
	float mx = 0;
	for (int i = 0; i < N; i++)
		mx += Rav[i];
	mx = mx * (1.0 / (float)N);
	cout << "\t\tМатематическое ожидание [mx] = " << mx << endl;

	float D = 0;
	for (int i = 0; i < N; i++)
		D += pow((Rav[i] - mx), 2.0);
	D = D * (1.0 / ((float)N - 1.0));
	cout << "\t\tДисперция [D] = " << D << endl;

	float sigma = sqrt(D);
	cout << "\t\tПлотность [sigma] = " << sigma << endl;

	float sigma_m = sigma / (pow(N, 0.5));
	cout << "\t\tsigma_m = " << sigma_m << endl;

	float sigma_D = (D * sqrt(2)) / sqrt(N - 1.0);
	cout << "\t\tsigma_D = " << sigma_D << endl;
}