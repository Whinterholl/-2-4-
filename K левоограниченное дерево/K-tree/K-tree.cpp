#include <iostream>

using namespace std;

#include "Menu.h"
#include "KTree.h"

int main()
{
	setlocale(LC_ALL, "ru");

	int n, k, menuNumb = 1;
	bool fTree = false; // возможность вывода
	Node* root = nullptr;

	while (menuNumb != 5)
	{
		menuNumb = menu();

		switch (menuNumb)
		{
		case 1:
		{
			// заполнение дерева возможностей
			cout << endl << "Введите количество этажей: "; cin >> n;
			cout << "Введите количество орехов: "; cin >> k;
			cout << endl;

			maxN = n;
			root = newNode(root, k); // создание корня

			// обработка ошибок
			if (k == 0 && n >= 1)
			{
				cout << "Нет орехов, есть этажи" << endl << endl;
			}
			else if (k == 0 && n == 0)
			{
				cout << "Ничего нет" << endl << endl;
				break;
			}
			else if (k > 0 && n == 0)
			{
				cout << "Есть орехи, но нет этажей" << endl << endl;
				root->data = 0;
				fTree = true;
				break;
			}
			else
			{
				while (number != n) kLeftTree(k, root);
				fTree = true;
			}

			kLeftTreeRez(root); // заполнение результатов
			treeLeaves(root); // заполнение путей

			break;
		}

		case 2:
		{
			// вывод дерева
			if (!fTree) cout << endl << "Для отображения введите данные" << endl;
			else inOrderTraversal(root, 0);

			cout << endl;

			break;
		}

		case 3:
		{
			if (k > 1)
			{
				cout << endl << "Определить прочность ореха:" << endl << endl;
				game(root);
			}
			else cout << endl << "Недостаточно орехов для проверки." << endl << endl;

			break;
		}

		case 4:
		{
			// удаление дерева
			fTree = deleteTree(root);
			Node* root = nullptr;
			cout << endl;

			break;
		}

		case 5: break; // выход

		default: // ввод неверной команды
			cout << endl << "Ошибка ввода" << endl << endl;
			menuNumb = 0;
		}
	}

	return 0;
}





