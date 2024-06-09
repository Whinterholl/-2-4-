#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

// процедура перевода заданного числа в прямой код
string codePK(int code)
{
    int ost = code; // сохранение числа для определения знака
    string codes; // строка содержащая прямой код

    code = abs(code); // модуль числа

    while (code >= 2)
    {
        codes += to_string(code % 2); // деление с остатком и занос остатка в строку
        code /= 2;
    };


    codes += to_string(code); // занос в строку последнего эл-та деления 
    //codes += to_string(0); // 0 для переполнения

    return codes;
}

// процедура перевода заданного числа в обратный код
string codeOK(int code)
{
    string code_ok; // строка хранящия обратный код

    code_ok = codePK(code); // вызов процедуры перевода в прямой код

    if (code < 0)// обратный код для отрицательного числа
        for (int i = 0; i < code_ok.size(); ++i)
        {
            if (code_ok[i] == '1') code_ok[i] = '0';
            else code_ok[i] = '1';
        }

    return code_ok;
}

// процедура перевода заданного числа в дополнительный код
string codeDK(int code)
{
    string code_dk; // строка хранящия дополнительный код

    code_dk = codeOK(code); // вызов процедуры перевода в обратный код

    if (code < 0) // дополнительный код для отрицательного числа
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
string reverseCode(int i, int ost, string codes)
{
    if (i != 4)
    {
        // определение знакового разряда
        if (ost >= 0) codes += ".0";
        else codes += ".1";
    }
    else // если выбран модифицированный код
    {
        if (ost >= 0) codes += ".00";
        else codes += ".11";
    }

    reverse(codes.begin(), codes.end()); // переворот строки

    return codes;
}

int main()
{
    setlocale(LC_ALL, "ru");

    int a, b, number = 1, digit, code;
    string digit_code, digit_string;
    char n_code, n_digit, n_diap;
    bool f; // для обработки ошибки ввода

    do
    {
        switch (number)
        {
            // ввод границ
            case 1:
            {
                f = true; // если введены числа значение 0

                cout << "Введите границы диапазна A < B: \n" << endl;
                cout << "A = "; cin >> a; // левая граница

                // проврка на правильность ввода 
                if (cin.fail()) // проверка на ввод буквы
                {
                    cin.clear(); // очистка потока ввода от символа
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    f = false; // если буква, то 1
                }

                cout << "B = "; cin >> b; // правая граница

                if (cin.fail()) // проверка на ввод буквы
                {
                    cin.clear(); // очистка потока ввода от символа
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    f = false; // если буква, то 1
                }

                // проверка на корректность ввода
                if ((a > b) || (!f)) cout << "Ошибка ввода границ диапазона" << endl;
                else number = 2;

                cout << endl;
                break;
            }

            // ввод числа в заданных границах
            case 2:
                cout << "Введите C принадлежащее заданному диапазону: " << endl;
                cout << "C = "; cin >> digit_string; //  ввод числа С

                // проверка наличия числа в заданных границах
                try
                {
                    digit = stoi(digit_string); // перевод строки в число
                    if ((digit >= a) && (digit <= b))
                    {
                        number = 3;
                        cout << endl;
                    }
                    else cout << "Ошибка ввода С \n" << endl;
                }
                catch (...)
                {
                    cout << "Ошибка ввода С \n" << endl;
                }

                break;

            // выбор кода
            case 3:
                cout << "Введите номер вида кода\n1 - прямой код \n2 - обратный код \n3 - дополнительный код \n4 - модифицированный дополнительный код\n"; 
                 cout << "M = "; cin >> code;

                // если введена буква
                if (cin.fail()) // проверка на ввод буквы
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if ((code >= 1) && (code <= 4)) number = 4;

                // перевод числа в выбранный код
                switch (code)
                {
                    // прямой код
                    case 1:
                        if (digit_string == "-0")
                            cout << "Прямой код\nC = " << (digit_code = "1.0") << endl; // перевод числа в обратный код
                        else if (digit_string == "+0")
                            cout << "Прямой код\nC = " << (digit_code = "0.0") << endl; // перевод числа в обратный код
                        else
                            cout << "Прямой код:\nC = " << (digit_code = reverseCode(code, digit, codePK(digit))) << endl; // перевод числа в прямой код

                        break;

                    // обратный код
                    case 2:
                        if (digit_string == "-0")
                            cout << "Обратный код\nC = " << (digit_code = "1.1") << endl; // перевод числа в обратный код
                        else if (digit_string == "+0")
                            cout << "Обратный код\nC = " << (digit_code = "0.1") << endl; // перевод числа в обратный код
                        else
                            cout << "Обратный код\nC = " << (digit_code = reverseCode(code, digit, codeOK(digit))) << endl; // перевод числа в обратный код

                        break;

                    // дополнительный код
                    case 3:
                    {
                        if (digit_string == "-0") cout << "Дополнительный код\nC = не используется" << endl; // если число = -0
                        else
                        {
                            cout << "Дополнительный код\nC = " << (digit_code = reverseCode(code, digit, codeDK(digit))) << endl; // перевод числа в дополнительный код
                        }
                        break;
                    }

                    // модифицированный дополнительный код
                    case 4:
                    {
                        if (digit_string == "-0") cout << "Модифицированный дополнительный код\nC = не используется"<< endl; // если число = -0
                        else
                        {
                            cout << "Модифицированный дополнительный код\nC = " << (digit_code = reverseCode(code, digit, codeDK(digit))) << endl; // перевод числа в модифицированный код
                        }
                        break;
                    }

                    // если введено любое другое число
                    default:
                        cout << "\nОшибка ввода номера вида кода" << endl;
                        break;
                }

                cout << endl;
                break;

            // повторный запрос ввода номера кода
            case 4:
                cout << "Повторить ввод номера вида кода? (Y - да/N - нет): "; cin >> n_code;

                if ((n_code == 'Y') || (n_code == 'y')) number = 3; // если отвте ДА, то переход к 3 шагу
                else if ((n_code == 'N') || (n_code == 'n')) number = 5; // если ответ НЕТ, переход к 5 шагу
                else if (((n_code != 'Y') && (n_code != 'N')) || ((n_code != 'y') && (n_code != 'n'))) cout <<"Ошибка продолжения выбора номера вида кода" << endl;

                cout << endl;
                break;

            // повторный запрос ввода числа в диапазоне
            case 5:
                cout << "Ввести новое значение числа С? (Y - да/N - нет): "; cin >> n_digit;

                if ((n_digit == 'Y') || (n_digit == 'y')) number = 2; // если отвте ДА, то переход ко 2 шагу
                else if ((n_digit == 'N') || (n_digit == 'n')) number = 6; // если ответ НЕТ, переход к 6 шагу
                else if (((n_digit != 'Y') && (n_digit != 'N')) || ((n_digit != 'y') && (n_digit != 'n'))) cout << "Ошибка запроса нового значения числа С" << endl;

                cout << endl;
                break;

            // повторный запрос ввода границ
            case 6:
                cout << "Ввести новое значение границ диапазона? (Y - да/N - нет): "; cin >> n_diap;

                if ((n_diap == 'Y') || (n_diap == 'y')) number = 1; // если отвте ДА, то переход к 1 шагу
                else if ((n_diap == 'N') || (n_diap == 'n')) number = 7; // если ответ НЕТ, выход
                else if (((n_diap != 'Y') && (n_diap != 'N')) || ((n_diap != 'y') && (n_diap != 'n'))) cout << "Ошибка запроса ввода границ диапазона\n" << endl;
        }
    } while (number != 7);

    cout << endl;

    system("PAUSE");
    return 0;
}