#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cstdlib>

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
    // codes += to_string(0); // 0 для переполнения

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
string reverseCode(string codes, bool f, string ost)
{
    if (!f)
    {
        // определение знакового разряда
        if (stoi(ost) >= 0) codes += ".0";
        else codes += ".1";
    }
    else // если выбран модифицированный код
    {
        if (stoi(ost) >= 0) codes += ".00";
        else codes += ".11";
    }

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

// выполнение операции деления СОВО
string codeDel(string a, string b, int s, string result, string R)
{
    int k = 1;

    for (int i = 1; i <= size(a); ++i) // строка из минусов
    {
        cout << "-";
    }

    result = codeOperation(a, b); // выполнение операции сложения
    reverse(result.begin(), result.end());
    cout << endl << result; // вывод результата

    cout << "  <0\n";

    cout << a << "  ВО\n";

    for (int i = 0; i <= size(a) - 1; ++i)
    {
        if (a[i + 1] == '.') a[i] = a[i + 2];
        else if (a[i] == '.')
        {
            a[i + 1] = a[i + 2];
            ++i;
        }
        else a[i] = a[i + 1];
    }

    reverse(a.begin(), a.end());
    a[0] = '0';
    reverse(a.begin(), a.end());

    cout << a << "  <-" << endl;
    cout << b << endl;

    // пока не закончил пользователь или пока длина результата != числу разрядов после точки
    while ((k <= size(result) - 2) && (k < s))
    {
        for (int i = 1; i <= size(a); ++i) // строка из минусов
        {
            cout << "-";
        }

        result = codeOperation(a, b); // выполнение операции сложения
        reverse(result.begin(), result.end());
        cout << endl << result; // вывод результата

        if (result[0] == '1') // если результат минусовой
        {
            R += "0";
            cout << "  <0\n";

            if (s > (k + 1))
            {
                cout << a << "  ВО\n";

                for (int i = 0; i <= size(a) - 1; ++i)
                {
                    if (a[i + 1] == '.') a[i] = a[i + 2];
                    else if (a[i] == '.')
                    {
                        a[i + 1] = a[i + 2];
                        ++i;
                    }
                    else a[i] = a[i + 1];
                }

                reverse(a.begin(), a.end());
                a[0] = '0';
                reverse(a.begin(), a.end());

                cout << a << "  <-" << endl;
                cout << b << endl;
            }
        }
        else
        {
            R += "1";
            cout << "  >0\n";

            if (s > (k + 1))
            {
                a = result;

                for (int i = 0; i <= size(a) - 1; ++i)
                {
                    if (a[i + 1] == '.') a[i] = a[i + 2];
                    else if (a[i] == '.')
                    {
                        a[i + 1] = a[i + 2];
                        ++i;
                    }
                    else a[i] = a[i + 1];
                }

                reverse(a.begin(), a.end());
                a[0] = '0';
                reverse(a.begin(), a.end());

                cout << a << "  <-" << endl;
                cout << b << endl;
            }
        }

        ++k;
    }

    return R;
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

    int number = 1, s, znak = 0, zf = 0;
    double sum = 0;
    string digit_code, digit_string, a, b, digit, code_a, code_b, result, R, zR;
    char n_code, n_digit, ex;
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
            cout << "Введите два целых десятичных числа A < B:\n" << endl;
            cout << "A = "; cin >> a;

            if (!(Number(a))) f = false; // проврка на правильность ввода числа а

            // ввод Б
            cout << "B = "; cin >> b;

            if (!(Number(b))) f = false; // проврка на правильность ввода числа б

            // проверка на корректность ввода
            if (!f) cout << "Ошибка ввода исходных чисел" << endl;
            else if ((abs(stoi(a)) > (abs(stoi(b))))) // проверка A < B
            {
                cout << "A должно быть меньше B\n" << endl;
                break;
            }
            else number = 2;

            cout << endl;
            break;
        }

        // выбор операции
        case 2:
            cout << "Введите номер выполняемой операции М:\n1 СОВО\n2 СОСД\n3 БОСО\n4 БОСД\nM = ";
            cin >> digit; // ввод номера операции

            if (isdigit(digit[0])) // прверка на ввод первого элемента
            {
                switch (digit[0]) // если выбрана не реализованная операция
                {
                case '1':
                {
                    if (b == "0")
                    {
                        cout << "Число -0 не используется в МДК" << endl;
                        number = 4;
                    }
                    else if (b == "-0")
                    {
                        cout << "Деление на 0 невозможно" << endl;
                        number = 4;
                    }
                    else number = 3;

                    break;
                }
                case '2': cout << "Операция деления не реализована\n" << endl; break;
                case '3': cout << "Операция деления не реализована\n" << endl; break;
                case '4': cout << "Операция деления не реализована\n" << endl; break;
                default: cout << "Ошибка ввода номера способа деления\n" << endl; break;
                }
            }
            else cout << "Ошибка ввода номера способа деления\n" << endl; // если введено не число

            s = 1;
            R = "0,";
            sum = 0;

            break;

            // перевод в модифицированный дополнительный код
        case 3:
            zR = "zR = zA (+) zB = ";

            // поиск знака
            if (stoi(a) > 0)
            {
                znak++;
                zR += "+ (+) ";
            }
            else
            {
                znak--;
                zR += "- (+) ";
            }

            if (stoi(b) > 0)
            {
                znak++;
                zR += "+ = ";
            }
            else
            {
                znak--;
                zR += "- = ";
            }

            if (znak == 0) zR += " R < 0";
            else zR += " R > 0";

            a = to_string(abs(stoi(a))); // модуль числа а
            b = to_string(-abs(stoi(b))); // минусовое значение числа б

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

            cout << "\nВОСО\n" << endl;

            cout << setw(12) << "|A|" << setw(12) << "-B\n";
            cout << "МПК" << setw(4) << " " << (reverseCode(code_a, true, a)) << setw(4) << " " << (reverseCode(code_b, true, b)) << endl; // МПК
            cout << "МОК" << setw(4) << " " << (reverseCode(codeOK(a, code_a), true, a)) << setw(4) << " " << (reverseCode(codeOK(b, code_b), true, b)) << endl; // МОК
            cout << "МДК" << setw(4) << " " << (code_a = (reverseCode(codeDK(a, code_a), true, a))) << setw(4) << " " << (code_b = (reverseCode(codeDK(b, code_b), true, b))) << endl << endl; // МДК

            number = 4;
            break;

        case 4:
            cout << code_a << endl;
            cout << code_b << endl;

            if (s == 1)
            {
                for (int i = 1; i <= size(code_a); ++i) // строка из минусов
                {
                    cout << "-";
                }

                result = codeOperation(code_a, code_b); // выполнение операции сложения
                reverse(result.begin(), result.end());
                cout << endl << result; // вывод результата

                if (result[0] == '1') // проверка знака
                {
                    cout << "  <0\n" << "R = " << R << endl << endl;
                }
                else cout << "  >0\n" << "R = " << R << endl << endl;
            }
            else
            {
                R = codeDel(code_a, code_b, s, result, "0,");
                cout << "R = " << R << endl << endl;
            }

            if (size(R) == size(code_a)) number = 6;
            else number = 5;

            break;

        case 5:
            cout << "Продолжить деление?\nY - да/N - нет:\n"; cin >> n_code;

            if ((n_code == 'Y') || (n_code == 'y'))
            {
                number = 4; // если отвте ДА, то переход к 4 шагу
                ++s;
            }
            else if ((n_code == 'N') || (n_code == 'n')) number = 6; // если ответ НЕТ, переход к 5 шагу
            else if (((n_code != 'Y') && (n_code != 'N')) || ((n_code != 'y') && (n_code != 'n'))) cout << "Ошибка ввода запроса на продолжение деления" << endl;

            cout << endl;
            break;


        case 6:
            // просмотр числа для округления
            if ((R[size(R) - 1] == '1') && ((R[size(R) - 2] == '1'))) R[size(R) - 2] = '0';
            if ((R[size(R) - 1] == '1') && ((R[size(R) - 2] == '0'))) R[size(R) - 2] = '1';
            if ((R[size(R) - 1] == '0') && ((R[size(R) - 2] == '1'))) R[size(R) - 2] = '1';

            R.erase(size(R) - 1, 1); // удаление числа для округления

            cout << zR << endl;

            if (znak == 0) cout << "R(2) = " << "-" << R << endl; // вывод двоичного значения
            else cout << "R(2) = " << "+" << R << endl;

            // расчет десятичного числа
            for (int i = 0; i <= size(R); ++i)
            {
                if (zf == 1)
                {
                    if (R[i] == '1')
                    {
                        sum = sum + (1 / pow(2, i - 1));
                    }
                }
                if (R[i] == ',') zf = 1; // если встречена запятая, то начать вычисление
            }

            cout << "R(10) = ";
            if (znak == 0) cout << "-";
            cout << sum << endl << endl;

            number = 7;
            break;

            /*  // повторный запрос ввода номера выполняемой операции
          case 6:
              cout << "Изменить способ деления?\nY - да/N - нет:\n"; cin >> n_code;

              if ((n_code == 'Y') || (n_code == 'y')) number = 2; // если отвте ДА, то переход к 2 шагу
              else if ((n_code == 'N') || (n_code == 'n')) number = 8; // если ответ НЕТ, переход к 8 шагу
              else if (((n_code != 'Y') && (n_code != 'N')) || ((n_code != 'y') && (n_code != 'n'))) cout << "Ошибка запроса на повторный ввод номера операции" << endl;

              cout << endl;
              break;
              */
              // повторный запрос ввода числа в диапазоне
        case 7:
            cout << "Ввести новое значение исходных данных?\nY - да/N - нет:\n"; cin >> n_digit;

            if ((n_digit == 'Y') || (n_digit == 'y')) number = 1; // если отвте ДА, то переход ко 1 шагу
            else if ((n_digit == 'N') || (n_digit == 'n')) number = 8; // если ответ НЕТ, то переход к шагу 9
            else if (((n_digit != 'Y') && (n_digit != 'N')) || ((n_digit != 'y') && (n_digit != 'n'))) cout << "Ошибка запроса на ввод новых заданных чисел" << endl;

            cout << endl;
            break;

        case 8:
            cout << "Завершить работу?\nY - да/N - нет?:\n"; cin >> ex;

            if ((ex == 'Y') || (ex == 'y')) number = 9; // если отвте ДА, ВЫХОД
            else if ((ex == 'N') || (ex == 'n')) number = 7; // если ответ НЕТ, то переход ко 8 шагу
            else if (((ex != 'Y') && (ex != 'N')) || ((ex != 'y') && (ex != 'n'))) cout << "Ошибка ввода запроса на завершение программы" << endl;

            cout << endl;
            break;
        }
    } while (number != 9);

    cout << endl;

    system("PAUSE");
    return 0;
}