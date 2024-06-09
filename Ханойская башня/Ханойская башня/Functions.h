#pragma once

int sum = 0;
bool f = false;

// вывод текущего положения диска
set <int> diskPosition(int n, set <int> number, char A)
{
	cout << "Диск " << n << " на " << A << " стержне" << endl;
	number.insert(n);
	return number;
}

// рекурсивное решение Ханойской башни
void hanoiTowerRec(bool print, int find, int n, char A, char B, char C)
{
	set <int> number;

	// конец дисков
	if (n == 0) return;

	// дошли до нужного шага
	if (sum == find && n == 1) f = true;

	// рекурсия берем диск меньшего размера
	if (!f) hanoiTowerRec(print, find, n - 1, A, C, B);

	// вывод текущего положения диска
	if (f && !number.count(n))
	{
		diskPosition(n, number, A);
		return;
	}

	// процесс перемещения дисков
	if (print) cout << "Диск " << n << " перемещен на " << B << " стержень" << endl;

	// номер шага
	sum++;

	// рекурсия берем диск меньшего размера
	if (!f) hanoiTowerRec(print, find, n - 1, C, B, A);

	// дошли до определенного шага
	if (sum == find) f = true;
	
	// вывод текущего положения диска
	if (f && !number.count(n))
	{
		diskPosition(n, number, B);
		return;
	}
}

// перемещение диска
void vectorMove(vector <string>& A, vector <string>& B)
{
	B.push_back(A.back());
	A.pop_back();
}

// перемещение векторов
vector <string> vectorHelp(vector <string> start, vector <string> finish)
{
	for (string s : start) finish.push_back(s);
	return finish;
}

// итерационное решение Ханойской башни
void hanoiTowerIter(int n, vector <string> &A, vector <string> &B, vector <string> &C)
{
	vector <string> help;

	for (int i = 1; i <= n; i++)
	{
		if (i % 2 == 1)
		{
			vectorMove(A, B);
			cout << "Диск 1 перемещен на " << B.front() << " стержень" << endl;
			help = vectorHelp(B, help);
			B.clear();
			B = vectorHelp(C, B);
			C.clear();
			C = vectorHelp(help, C);
			help.clear();
		}
		else
		{
			if (B.size() == 1)
			{
				vectorMove(A, B);
				cout << "Диск " << B.back() << " перемещен на " << B.front() << " стержень" << endl;
			}
			else if (A.size() == 1) 
			{
				vectorMove(B, A);
				cout << "Диск " << A.back() << " перемещен на " << A.front() << " стержень" << endl;
			}
			else if (A.back() < B.back())
			{
				vectorMove(A, B);
				cout << "Диск " << B.back() << " перемещен на " << B.front() << " стержень" << endl;
			}
			else 
			{
				vectorMove(B, A);
				cout << "Диск " << A.back() << " перемещен на " << A.front() << " стержень" << endl;
			}

			help = vectorHelp(A, help);
			A.clear();
			A = vectorHelp(C, A);
			C.clear();
			C = vectorHelp(help, C);
			help.clear();
		}
	}
}

void newPos(vector <string> &A, vector <string> &B)
{
	vector <string> help;
	help = vectorHelp(B, help);
	B.clear();
	B = vectorHelp(A, B);
	A.clear();
	A = vectorHelp(help, A);
}

void posaZam(vector <string>& A, vector <string>& B, vector <string>& C)
{
	if (A.front() == "B" || B.front() == "A") newPos(A, B);
	if (A.front() == "C") newPos(A, C);
	if (B.front() == "C") newPos(B, C);
}

void newPosition(bool f, int n, vector <string> A, vector <string> B, vector <string> C, vector <int> A_pos, vector <int> B_pos, vector <int> C_pos)
{
	bool ch;

	if (n % 2 == 1) ch = false;
	else ch = true;

	if ((find(begin(A_pos), end(A_pos), n) != end(A_pos) || A_pos.back() == n) && !f)
	{
		cout << "Диск " << n << " на стержне А" << endl;
		n--;
		newPosition(f, n, A, B, C, A_pos, B_pos, C_pos);
	}
	else
	{
		f = true;
		if (find(begin(B_pos), end(B_pos), n) != end(B_pos))
		{
			if (find(A.begin(), A.end(), to_string(n)) != A.end() || A.back() == to_string(n)) 
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), A, B, C);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), A, C, B);
					posaZam(A, B, C);
				}
			}
			else if (find(C.begin(), C.end(), to_string(n)) != C.end() || C.back() == to_string(n)) 
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), C, B, A);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), C, A, B);
					posaZam(A, B, C);
				}
			}
			//else cout << "Диск " << n << " на стержне B" << endl;
		}
		else if (find(begin(C_pos), end(C_pos), n) != end(C_pos))
		{
			if (find(A.begin(), A.end(), to_string(n)) != A.end() || A.back() == to_string(n))
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), A, C, B);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), A, B, C);
					posaZam(A, B, C);
				}
			}
			else if (find(B.begin(), B.end(), to_string(n)) != B.end() || B.back() == to_string(n))
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), B, C, A);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), B, A, C);
					posaZam(A, B, C);
				}
			}
			//else cout << "Диск " << n << " на стержне С" << endl;
		}
		else if (find(begin(A_pos), end(A_pos), n) != end(A_pos))
		{
			if (find(B.begin(), B.end(), to_string(n)) != B.end() || B.back() == to_string(n))
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), B, A, C);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), B, C, A);
					posaZam(A, B, C);
				}
			}
			else if (find(C.begin(), C.end(), to_string(n)) != C.end() || C.back() == to_string(n))
			{
				if (!ch)
				{
					hanoiTowerIter(pow(2, n - 1), C, A, B);
					posaZam(A, B, C);
				}
				else
				{
					hanoiTowerIter(pow(2, n - 1), C, B, A);
					posaZam(A, B, C);
				}
			}
			//else cout << "Диск " << n << " на стержне A" << endl;
		}

		n--;
		if (n <= 0) return;
		newPosition(f, n, A, B, C, A_pos, B_pos, C_pos);
	}
}

//void vectorMove(vector <int>& A, vector <int>& B)
//{
//	B.push_back(A.back());
//	A.pop_back();
//}
//
//int hanoiTower(int n, int rez, vector <int> A, vector <int> B, vector <int> C)
//{
//	if (n % 2 == 1)
//	{
//		vectorMove(A, B);
//		rez++;
//		if (n == 1) return rez;
//		hanoiTower(n - 1, rez, A, C, B);
//	}
//	else
//	{
//		if (B.size() == 0) vectorMove(A, B);
//		else if (A.size() == 0) vectorMove(B, A);
//		else if (A.back() < B.back()) vectorMove(A, B);
//		else vectorMove(B, A);
//
//		rez++;
//		hanoiTower(n - 1, rez, C, B, A);
//	}
//}