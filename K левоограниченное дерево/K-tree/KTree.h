#pragma once

int number = 1; // �������� ���-�� �����
int maxN; // ������������ ���-�� �����
int rez = 0; // ���������� �� 0 �� n

// ��������� ������
struct Node
{
	Node* left;
	Node* right;
	int data;
};

// �������� ����
Node* newNode(Node* root, int k)
{
	Node* nodeNew = new Node();

	nodeNew->data = k; // ���-�� ���������� �������
	nodeNew->left = nullptr;
	nodeNew->right = nullptr;

	return nodeNew;
}

// ���������� �-���� ������������� ������
Node* kLeftTree(int k, Node* root)
{
	// ���� ������, ���� ���� ������� ��� ����������
	if (root->right == nullptr)
	{
		root->right = newNode(root->right, root->data);
		number++;
	}
	else kLeftTree(root->data, root->right);

	if (number == maxN) return root; // ���� ��������� ��� ��������� ����

	// ���� ����� ���� ���� ������� ���������� � ���-�� ����� ��������� ������ 1
	if (root->left == nullptr && root->data != 1)
	{
		root->left = newNode(root->left, root->data - 1);
		number++;
	}
	else if (root->data == 1) return root; // ���� ���-�� ����� ��������� 1, �� ������������
	else kLeftTree(root->data, root->left);

	if (number == maxN) return root;

	return root;
}

// ���������� �����������
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

// ����� ������������ �������� � ������ ���������
int minLeaves(Node* root)
{
	if (root->left == nullptr) return root->data;
	else minLeaves(root->left);
}

// ���������� ������� ������
void treeLeaves(Node* root)
{
	// ��������� ��������� �� ������� ���������
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
		cout << endl << "��������� ����� ����� " << root->data << endl << endl;
		return;
	}

	cout << "���� �������� � " << root->data << " ����� " << " y/n: "; cin >> answer;

	if (answer == 'y') game(root->left); // ��������, ���� ������
	else if (answer == 'n') game(root->right); // ���, ���� �������
	else
	{
		cout << "������������ ����" << endl;
		game(root);
	}
}

// ����� � ��������
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

// �������� ������
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
