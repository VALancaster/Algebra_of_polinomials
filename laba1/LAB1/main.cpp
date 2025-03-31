#include <iostream>
#include <cstdlib>
#include <string>
#include "polinom.h"

using namespace std;

void printMenu() {
    setlocale(LC_ALL, "Russian");
    cout << "\n=== Аналитические преобразования полиномов ===\n";
    cout << "  + : Сложение двух полиномов\n";
    cout << "  - : Вычитание двух полиномов\n";
    cout << "  * : Умножение двух полиномов или умножение полинома на число\n";
    cout << "  = : Вычислить значение полинома в точке\n";
    cout << "  d : Взять производную от полинома\n";
    cout << "  q : Выйти из программы\n";
    cout << "=============================================\n";
    cout << "Выберите операцию: ";
}

bool isPolynomValid(const string& str) {
    return !str.empty();
}

int main() 
{
    cout << "Welcome to interactive data structure!  What you want to do ? " << std::endl;
    cout << "1 -- show table" << std::endl;
    cout << "2 -- set active table" << std::endl;
    cout << "3 -- add polinom" << std::endl;
    cout << "4 -- evaluate polinom" << std::endl;
    setlocale(LC_ALL, "Russian");
    char operation;
    Polinom polynom1, polynom2, result;

    cout << "Введите первый полином: ";
    string input1;
    cin >> input1;

    if (!isPolynomValid(input1)) {
        cout << "Некорректный полином!\n";
        return 1;
    }
    polynom1 = Polinom(input1);

    while (true) {
        printMenu();
        cin >> operation;

        switch (operation) {
        case '+':
            cout << "Введите второй полином для сложения: ";
            cin >> input1;
            if (!isPolynomValid(input1)) {
                cout << "Некорректный полином!\n";
                break;
            }
            polynom2 = Polinom(input1);
            result = polynom1 + polynom2;
            cout << "Результат: " << result << endl;
            break;

        case '-':
            cout << "Введите второй полином для вычитания: ";
            cin >> input1;
            if (!isPolynomValid(input1)) {
                cout << "Некорректный полином!\n";
                break;
            }
            polynom2 = Polinom(input1);
            result = polynom1 - polynom2;
            cout << "Результат: " << result << endl;
            break;

        case '*':
            cout << "" << endl;
            cout << "Учтите, что при вводе слишком сложных полиномов операция может работать некорректно." << endl;
            cout << "Также рекомендуется указывать коэффициенты у мономов (лучше писать не x^2, а 1x^2) ." << endl;
            cout << "Введите второй полином или число: ";
            cin >> input1;
            if (isdigit(input1[0]) || input1[0] == '-') {
                double value = stod(input1);
                result = polynom1 * value;
            }
            else if (isPolynomValid(input1)) {
                polynom2 = Polinom(input1);
                result = polynom1 * polynom2;
            }
            else {
                cout << "Некорректный ввод!" << endl;
                break;
            }
            cout << "Результат: " << result << endl;
            break;

        case '=':
            double x, y, z;
            cout << "Введите значения переменных x, y, z через пробел: ";
            cin >> x >> y >> z;
            cout << "Результат вычисления: " << polynom1.evaluate(x, y, z) << endl;
            break;

        case 'd': {
            cout << "Выберите переменную для дифференцирования (например, x, y, z): ";
            char var;
            cin >> var;
            cin.ignore();

            cout << "Пожалуйста, введите полином для дифференцирования." << endl;
            cout << "Обязательно указывайте коэффициенты у мономов (нельзя писать x^2, нужно писать 1x^2)." << endl;
            cout << "Пример ввода: 1x^2+2x-3" << endl;
            cout << "Введите полином: ";

            string input2;
            getline(cin, input2);

            if (!isPolynomValid(input2)) {
                cout << "Некорректный полином!\n";
                break;
            }

            Polinom polynomToDerive;
            try {
                polynomToDerive = Polinom(input2);
                result = polynomToDerive.derivative(var);
                cout << "Производная полинома по переменной '" << var << "': " << result << endl;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
            break;
        }

        case 'q':
            cout << "Выход из программы...\n";
            return 0;

        default:
            cout << "Неверная операция. Попробуйте снова.\n";
            break;
        }
    }
}