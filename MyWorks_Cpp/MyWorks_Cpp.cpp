#include "SimplexMethod.h"
#include "DynamicMethod.h"

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
			cin >> index;
			if (index < 0)
				cout << "\t\tВы ввели некорректное число\n\n";
			else
				break;
		} while (true);

		cout << "\t\tВы выбрали метод под номером: " << index << endl << endl;

		clock_t Time = clock();

		if (index == 0)
			InitSimplexMethod();
		else if (index == 1)
			InitDynamicMethod();

		double EndTime = (clock() - (double)Time) / CLOCKS_PER_SEC;
		cout << "\n\n\t\tВремя выполнения: " << EndTime << endl;

		cout << "\n\n\n\t\tПродолжить? 0 - Да, 1 - Нет" << endl << endl;
		cin >> canExit;
		if (canExit != 0)
			break;

	} while (true);

	return 0;
}