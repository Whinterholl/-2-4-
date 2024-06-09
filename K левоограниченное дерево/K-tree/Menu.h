#pragma once

int menu()
{
	int menuN;

	cout << "1) Создать варианты исхода событий" << endl;
	cout << "2) Отобразить имеющиеся варианты" << endl;
	cout << "3) Проверка прочности" << endl;
	cout << "4) Удалить дерево" << endl;
	cout << "5) Выход" << endl;

	cout << endl << "Введите номер выбранного действия: "; cin >> menuN;

	return menuN;
}