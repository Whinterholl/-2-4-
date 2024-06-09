#pragma once

int number = 1; // нынешнее кол-во узлов
int maxN; // максимальное кол-во узлов
int rez = 0; // результаты от 0 до n

// Структура дерева
struct Node
{
	Node* left;
	Node* right;
	int data;
};

// Создание узла
Node* newNode(Node* root, int k)
{
	Node* nodeNew = new Node();

	nodeNew->data = k; // кол-во оставшихся попыток
	nodeNew->left = nullptr;
	nodeNew->right = nullptr;

	return nodeNew;
}

// Построение К-лево ограниченного дерева
Node* kLeftTree(int k, Node* root)
{
	// идем вправо, пока след элемент еще существует
	if (root->right == nullptr)
	{
		root->right = newNode(root->right, root->data);
		number++;
	}
	else kLeftTree(root->data, root->right);

	if (number == maxN) return root; // если построили все возможные узлы

	// идем влево пока след элемент существует и кол-во левых поворотов больше 1
	if (root->left == nullptr && root->data != 1)
	{
		root->left = newNode(root->left, root->data - 1);
		number++;
	}
	else if (root->data == 1) return root; // если кол-во левых поворотов 1, то возвращаемся
	else kLeftTree(root->data, root->left);

	if (number == maxN) return root;

	return root;
}

// Заполнение результатов
void kLeftTreeRez(Node* root)
{
	if (root->left == nullptr)
	{
		root->left = newNode(root->left, rez);
		rez++;
	}
	else kLeftTreeRez(root->left);

	if (root->right == nullptr)
	{
		root->right = newNode(root->right, rez);
		rez++;
	}
	else kLeftTreeRez(root->right);
}

// Поиск минимального элемента в правом поддереве
int minLeaves(Node* root)
{
	if (root->left == nullptr) return root->data;
	else minLeaves(root->left);
}

// Заполнение листьев дерева
void treeLeaves(Node* root)
{
	// заполняем минимумом из правого поддерева
	if (root->left->left == nullptr)
	{
		root->data = minLeaves(root->right);
	}
	else treeLeaves(root->left);

	root->data = minLeaves(root->right);

	if (root->right->right == nullptr)
	{
		root->data = minLeaves(root->right);
	}
	else treeLeaves(root->right);
}


void game(Node* root)
{
	char answer;

	if (root->left == nullptr)
	{
		cout << endl << "Прочность ореха равна " << root->data << endl << endl;
		return;
	}

	cout << "Орех разбился с " << root->data << " этажа " << " y/n: "; cin >> answer;

	if (answer == 'y') game(root->left); // разбился, идем налево
	else if (answer == 'n') game(root->right); // цел, идем направо
	else
	{
		cout << "Некорректный ввод" << endl;
		game(root);
	}
}

// вывод с уступами
void inOrderTraversal(Node* root, int space)
{
	if (root == nullptr) return;

	space += 4;

	inOrderTraversal(root->right, space);

	cout << endl;
	for (int i = 2; i < space; i++) cout << " ";
	cout << root->data << endl;

	inOrderTraversal(root->left, space);
}

// удаление дерева
bool deleteTree(Node* root)
{
	if (root != nullptr)
	{
		deleteTree(root->left);
		deleteTree(root->right);

		delete root;
	}
	rez = 0;
	number = 1;

	return false;
}
