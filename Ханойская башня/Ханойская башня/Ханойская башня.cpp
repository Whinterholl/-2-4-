#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

#include "Functions.h"

int main()
{
    setlocale(LC_ALL, "ru");

    int number, find, position;
    vector <string> A{ "A" }, B{ "B" }, C{ "C" }; // вектора обозначающие кольца
    vector <int> A_pos, B_pos, C_pos;
    bool f = true, ch;

    cout << "Введите кол-во дисков: "; cin >> number;

    if (number % 2 == 1) f = false; // проверка на четность кол-ва колец

    for (int i = number; i >= 1; i--) A.push_back(to_string(i)); // заполнение стержня А кольцами

    // ------------------------- Рекурсивное решение---------------------- //
    hanoiTowerRec(true, pow(2, number), number, 'A', 'B', 'C');
    cout << endl;
    // ------------------------------------------------------------------- //

    // ------------------------- Итерационное решение---------------------- //
    if (!f) hanoiTowerIter(pow(2, number) - 1, A, B, C);
    else hanoiTowerIter(pow(2, number) - 1, A, C, B);
    // -------------------------------------------------------------------- //

    // ------------------------- Поиск колец по позиции --------------------------- //
    cout << endl << "Введите номер позиции для остановки: "; cin >> find;
    sum = 0;
    if (find <= pow(2, number) - 1 && find >= 0) hanoiTowerRec(false, find, number, 'A', 'B', 'C');
    else cout << "Данной позиции быть не может" << endl;
    // --------------------------------------------------------------------------- //

    A.clear(); A.push_back("A");
    B.clear(); B.push_back("B");
    C.clear(); C.push_back("C");
    
    for (int i = number; i >= 1; i--) A.push_back(to_string(i)); // заполнение стержня А кольцами

    cout << endl << "Введите расположение дисков (введите 0, если дисков на стержне нет): " << endl;

    cout << endl << "Стержень А: "; 
    while (cin >> position) 
    {
        if (position == 0) break;
        A_pos.push_back(position);
    }

    cout<< "Стержень B: ";
    while (cin >> position) 
    {
        if (position == 0) break;
        B_pos.push_back(position);
    }

    cout<< "Стержень C: ";
    while (cin >> position) 
    {
        if (position == 0) break;
        C_pos.push_back(position);
    }

    cout << endl;

    newPosition(false, number, A, B, C, A_pos, B_pos, C_pos);

    system("PAUSE");
    return 0;
}