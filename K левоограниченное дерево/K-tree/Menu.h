#pragma once

int menu()
{
	int menuN;

	cout << "1) ������� �������� ������ �������" << endl;
	cout << "2) ���������� ��������� ��������" << endl;
	cout << "3) �������� ���������" << endl;
	cout << "4) ������� ������" << endl;
	cout << "5) �����" << endl;

	cout << endl << "������� ����� ���������� ��������: "; cin >> menuN;

	return menuN;
}