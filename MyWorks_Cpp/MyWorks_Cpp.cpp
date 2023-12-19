#include "SimplexMethod.h"

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
			cout << "\t\t0 - Симплекс-метод линейного программирования (поиск максимума)\n\n";
			cin >> index;
			if (index < 0 || index > 0)
				cout << "\t\tВы ввели некорректное число\n\n";
			else
				break;
		} while (true);

		cout << "\t\tВы выбрали метод под номером" << index << endl << endl;

		if (index == 0)
			InitSimplexMethod();

		cout << "\n\n\n\t\tПродолжить? 0 - Да, 1 - Нет" << endl << endl;
		cin >> canExit;
		if (canExit != 0)
			break;

	} while (true);

	return 0;
}