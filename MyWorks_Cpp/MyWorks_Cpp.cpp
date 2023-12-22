#include "SimplexMethod.h"
#include "DynamicMethod.h"
#include "UniformNormalDistribution.h"
#include "XiSquareDistributionModeling.h"
#include "WhiteNoise.h"

int main() 
{
	setlocale(LC_ALL, "Russian");

	int canExit = 0;
	do
	{
		int index = -1;
		do
		{
			cout << "\t\tВведите желаемый метод\n\n";

			cout << "\t\t0 - Симплекс-метод линейного программирования (поиск максимума)\n";
			cout << "\t\t1 - Метод динамического программирования для решения задач математического программирования\n";
			cout << "\t\t2 - Моделирование независимых случайных величин имеющих равномерное и нормальное распределение (Гауссовское)\n";
			cout << "\t\t3 - Моделирование распределения Хи-квадрат\n";
			cout << "\t\t4 - Формирование из белого шума случайного процесса\n";
			cout << "\t\t5 - Экспериментальный метод получения случайных процесса, описывающего вертикальную турбулентность атмосферы с заданными статистическими характеристиками путем пропускания белого шума через формирующий фильтр\n";

			cin >> index;
			if (index < 0)
				cout << "\t\tВы ввели некорректное число\n\n";
			else
				break;
		} while (true);

		clock_t Time = clock();

		switch (index)
		{
		case 0:
			InitSimplexMethod();
			break;
		case 1:
			InitDynamicMethod();
			break;
		case 2:
			InitUniformNormalDistribution();
			break;
		case 3:
			InitXiSquareDistributionMethod();
			break;
		case 4:
			InitFormationOfRandomProcessFromWhiteNoise();
			break;
		case 5:
			InitExperimentalMethodForObtainingRandomProcessesFromWhiteNoise();
			break;
		}

		double EndTime = (clock() - (double)Time) / CLOCKS_PER_SEC;
		cout << "\n\n\t\tОбщее время выполнения: " << EndTime << endl;

		cout << "\n\n\n\t\tПродолжить? 0 - Да, 1 - Нет" << endl << endl;
		cin >> canExit;
		if (canExit != 0)
			break;

	} while (true);

	return 0;
}