#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

// процедура перевода заданного числа в прямой код
string codePK(string code)
{
    int ost = stoi(code);

    string codes; // строка содержащая прямой код

    ost = abs(ost); // модуль числа

    while (ost >= 2)
    {
        codes += to_string(ost % 2); // деление с остатком и занос остатка в строку
        ost /= 2;
    }

    codes += to_string(ost); // занос в строку последнего эл-та деления 
    codes += to_string(0); // 0 для переполнения

    return codes;
}

// процедура перевода заданного числа в обратный код
string codeOK(string code, string codeNumber)
{
    string code_ok; // строка хранящия обратный код

    if (stoi(code) < 0)// обратный код для отрицательного числа
        for (int i = 0; i < codeNumber.size(); ++i)
        {
            if (codeNumber[i] == '1') codeNumber[i] = '0';
            else codeNumber[i] = '1';
        }

    return codeNumber;
}

// процедура перевода заданного числа в дополнительный код
string codeDK(string code, string codeNumber)
{
    string code_dk; // строка хранящия дополнительный код

    code_dk = codeOK(code, codeNumber); // вызов процедуры перевода в обратный код

    if (stoi(code) < 0) // дополнительный код для отрицательного числа
    {
        for (int i = 0; i < code_dk.size(); ++i)
        {
            if (code_dk[i] == '1') code_dk[i] = '0'; // если встречает 1, меняет на 0
            else
            {
                code_dk[i] = '1'; // пока не встретит 0, после меняет его на единицу
                break;
            }
        }
    }

    return code_dk;
}

// определение знакового разряда и реверс кода
string reverseCode(string ost, string& codes)
{
    if (stoi(ost) >= 0) codes += ".00";
    else codes += ".11";

    reverse(codes.begin(), codes.end()); // переворот строки

    return codes;
}

// выполнение заданной операции
string codeOperation(string a, string b)
{
    string code;
    bool f = false;

    for (int i = size(a) - 1; i >= 0; --i)
    {
        if ((a[i] == '.') && (b[i] == '.'))
        {
            code += '.';
            --i;
        }

        if ((a[i] == '0') && (b[i] == '0') && !f) code += '0';
        if ((a[i] == '0') && (b[i] == '0') && f)
        {
            code += '1';
            f = false;
        }
        if ((a[i] == '1') && (b[i] == '0') && !f) code += '1';
        if ((a[i] == '1') && (b[i] == '0') && f) code += '0';
        if ((a[i] == '0') && (b[i] == '1') && !f) code += '1';
        if ((a[i] == '0') && (b[i] == '1') && f) code += '0';
        if ((a[i] == '1') && (b[i] == '1') && f) code += '1';
        if ((a[i] == '1') && (b[i] == '1') && !f)
        {
            code += '0';
            f = true;
        }
    }

    return code;
}

// проверка правильности ввода десятичного числа
bool Number(string a)
{
    bool f = true;

    if (size(a) > 1)
    {
        if ((a[0] == '-') || (isdigit(a[0]))) // проверка на первый знак
        {
            for (int i = 1; i < size(a); ++i)
            {
                if (!isdigit(a[i])) f = false;
            }
        }
    }
    else if (!isdigit(a[0])) f = false;

    return f;
}

int main()
{
    setlocale(LC_ALL, "ru");

    int number = 1, code;
    string digit_code, digit_string, a, b, digit, code_a, code_b, result;
    char n_code, n_digit, n_diap, ex;
    bool f; // для обработки ошибки ввода

    do
    {
        switch (number)
        {
            // ввод границ
        case 1:
        {
            f = true; // если введены числа значение 0

            // ввод А
            cout << "Введите два целых десятичных числа:\n" << endl;
            cout << "a = "; cin >> a;

            if (!(Number(a))) f = false; // проврка на правильность ввода числа а

            // ввод Б
            cout << "b = "; cin >> b;

            if (!(Number(b))) f = false; // проврка на правильность ввода числа б

            // проверка на корректность ввода
            if (!f) cout << "Ошибка ввода исходных чисел" << endl;
            else number = 2;

            cout << endl;
            break;
        }

        // выбор операции
        case 2:
            cout << "Введите номер выполняемой операции М:\n1  a+b\n2  a-b\n3 -a+b\n4 -a-b\nM = ";
            cin >> digit; // ввод номера операции

            if (isdigit(digit[0])) // прверка на ввод первого элемента
            {
                if (digit[0] == '3')  // если выбрана реализованная операция
                {
                    if ((f) && ((a == "0") || (b == "-0")))
                    {
                        cout << "Число -0 не используется в МДК" << endl;
                        number = 4;
                    }
                    else number = 3;
                }
                else
                {
                    switch (digit[0]) // если выбрана не реализованная операция
                    {
                    case '1': cout << "Операция a+b не реализована\n" << endl; break;
                    case '2': cout << "Операция a-b не реализована\n" << endl; break;
                    case '4': cout << "Операция -a-b не реализована\n" << endl; break;
                    default: cout << "Ошибка ввода номера выполняемой операции\n" << endl; break;
                    }
                }
            }
            else cout << "Ошибка ввода номера выполняемой операции\n" << endl; // если введено не число

                break;

            // перевод в модифицированный дополнительный код
        case 3:
            cout << "\n-a+b\n" << endl;

            if (stoi(a) < 0) a = to_string(abs(stoi(a))); // замена знака, если число отрицательное
            else a = to_string(-stoi(a));

            if (size(code_a = codePK(a)) > (size(code_b = codePK(b)))) // если длина а больше длины б
            {
                int r = size(code_a) - size(code_b); // высчитываем разность длин
                for (int i = 0; i < r; ++i) code_b += "0"; // добавляем недостающее кол-во рязрядов
            }
            else
            {
                int r = size(code_b) - size(code_a); // высчитываем разность длин
                for (int i = 0; i < r; ++i) code_a += "0"; // добавляем недостающее кол-во рязрядов
            }

            code_a = codeDK(a, code_a); // получение МДК первого числа
            code_b = codeDK(b, code_b); // получение МДК второго числа

            cout << (code_a = reverseCode(a, code_a)) << endl; // вывод первого числа
            cout << (code_b = reverseCode(b, code_b)) << endl; // вывод второго числа

            for (int i = 1; i <= size(code_a); ++i) // строка из минусов
            {
                cout << "-";
            }

            result = codeOperation(code_a, code_b); // выполнение операции сложения
            reverse(result.begin(), result.end());
            cout << endl << result << endl; // вывод результата

            if (result[0] == '0') // действия в соответствии с знаковым разрядом
            {
                int sum = 0;

                for (int i = 0; i < size(result); ++i) result[i] = result[i + 1]; // перемещаем символы на 1 знак вправо
                    result.erase(size(result) - 1, 1); // убираем пустые разряды

                cout << "\nR(ОК) = " << result << endl; // вывод результата в ОК
                cout << "R(ПК) = " << result << endl; // вывод результата в ПК

                for (int i = 0; i < size(result) - 2; ++i) result[i] = result[i + 2]; // сдвиг на 2 символа влево
                result.erase(size(result) - 2, 2); // убираем пустые разряды

                for (int i = 0; i < size(result); ++i) // убираем ненужные 0
                {
                    if (result[i] == '0')
                    {
                        result.erase(0, 1);
                        i -= 1;
                    }
                    else break;
                }

                cout << "R(2) = " << result << endl; // вывод результата в двоичной системе

                reverse(result.begin(), result.end());
                for (int i = 0; i < size(result); ++i) // перевод результата в десятичную систему
                {
                    if (result[i] == '1') sum = sum + pow(2, i);
                }
                reverse(result.begin(), result.end());
                cout << "R(10) = " << sum << endl; // вывод результата в десятичной системе
            }
            else
            {
                int sum = 0; // сумма

                for (int i = 0; i < size(result); ++i) result[i] = result[i + 1]; // перемещаем символы на 1 знак вправо
                    result.erase(size(result) - 1, 1); // убираем пустые разряды

                for (int i = size(result) - 1; i > 2; --i) // вычитание 1
                {
                    if (result[i] == '0') result[i] = '1';
                    else
                    {
                        result[i] = '0';
                        cout << "\nR(ОК) = " << result << endl;
                        break;
                    }
                }

                for (int i = 2; i < size(result); ++i) // замена 0 на 1 и наоборот
                {
                    if (result[i] == '1') result[i] = '0';
                    else result[i] = '1';
                }
                cout << "R(ПК) = " << result << endl;

                for (int i = 0; i < size(result) - 2; ++i) result[i] = result[i + 2]; // сдвиг на 2 символа влево
                result.erase(size(result) - 2, 2); // убираем пустые разряды

                for (int i = 0; i < size(result); ++i) // убираем ненужные 0
                {
                    if (result[i] == '0')
                    {
                        result.erase(0, 1);
                        i -= 1;
                    }
                    else break;
                }

                cout << "R(2) = -" << result << endl; // вывод результата в двоичной системе

                reverse(result.begin(), result.end());
                for (int i = 0; i < size(result); ++i) // перевод в десятичную систему
                {
                    if (result[i] == '1') sum = sum + pow(2, i);
                }
                reverse(result.begin(), result.end());
                cout << "R(10) = -" << sum << endl;
            }

            cout << endl;
            number = 4;
            break;

            // повторный запрос ввода номера выполняемой операции
        case 4:
            cout << "Изменить номер выполняемой операци?\nY - да/N - нет:\n"; cin >> n_code;

            if ((n_code == 'Y') || (n_code == 'y')) number = 2; // если отвте ДА, то переход к 2 шагу
            else if ((n_code == 'N') || (n_code == 'n')) number = 5; // если ответ НЕТ, переход к 5 шагу
            else if (((n_code != 'Y') && (n_code != 'N')) || ((n_code != 'y') && (n_code != 'n'))) cout << "Ошибка запроса на повторный ввод номера операции" << endl;

            cout << endl;
            break;

            // повторный запрос ввода числа в диапазоне
        case 5:
            cout << "Ввести новое значение заданных чисел?\nY - да/N - нет:\n"; cin >> n_digit;

            if ((n_digit == 'Y') || (n_digit == 'y')) number = 1; // если отвте ДА, то переход ко 1 шагу
            else if ((n_digit == 'N') || (n_digit == 'n')) number = 6; // если ответ НЕТ, выход
            else if (((n_digit != 'Y') && (n_digit != 'N')) || ((n_digit != 'y') && (n_digit != 'n'))) cout << "Ошибка запроса на ввод новых заданных чисел" << endl;

                cout << endl;
            break;

        case 6:
            cout << "Завершить работу программы?\nY - да/N - нет?:\n"; cin >> ex;

            if ((ex == 'Y') || (ex == 'y')) number = 7; // если отвте ДА, то переход ко 5 шагу
            else if ((ex == 'N') || (ex == 'n')) number = 5; // если ответ НЕТ, выход
            else if (((ex != 'Y') && (ex != 'N')) || ((ex != 'y') && (ex != 'n'))) cout << "Ошибка ввода запроса на завершение программы" << endl;

                cout << endl;
            break;
        }
    } while (number != 7);

    cout << endl;

    system("PAUSE");
    return 0;
}