#include <iostream>
#include <string>
#include "Controller.h"
#include "Polinom.h"

using namespace std;

void printMenu() {
    cout << "\n===== МЕНЮ УПРАВЛЕНИЯ ПОЛИНОМАМИ =====\n";
    cout << "1. Выбрать активную таблицу\n";
    cout << "2. Вывести содержимое активной таблицы\n";
    cout << "3. Добавить полином в таблицы\n";
    cout << "4. Удалить полином по ключу\n";
    cout << "5. Вычислить и сохранить полиномное выражение\n";
    cout << "6. Взять производную от полинома\n";
    cout << "7. Вычислить значение полинома в точке\n";
    cout << "8. Выйти\n";
    cout << "Выберите действие: ";
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    

    Controller controller;
    string key, input;
    char var;

    while (true) {
        printMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Выберите таблицу:\n"
                << "0 - Array\n"
                << "1 - List\n"
                << "2 - SortedArray\n"
                << "3 - Tree\n"
                << "4 - HashOpen\n"
                << "5 - HashChain\n"
                << "Ваш выбор: ";
            int index;
            cin >> index;
            try {
                controller.SetActiveTable(index);
            }
            catch (const exception& e) {
                cerr << "Ошибка: " << e.what() << endl;
            }
        }

        else if (choice == 2) {
            controller.PrintActiveTable();
        }

        else if (choice == 3) {
            cout << "Введите название переменной для полинома: ";
            cin >> key;
            cin.ignore();
            cout << "Введите полином (например: 2x^2y + 3xy^2 - 1): ";
            getline(cin, input);
            try {
                Polinom p(input);
                controller.AddPolinom(key, p);
            }
            catch (const exception& e) {
                cerr << "Ошибка при создании полинома: " << e.what() << endl;
            }
        }

        else if (choice == 4) {
            cout << "Введите название удаляемого полинома: ";
            cin >> key;
            controller.DeletePolinom(key);
        }

        else if (choice == 5) {
            cout << "Введите название результирующего полинома: ";
            cin >> key;
            cin.ignore();
            cout << "Введите выражение с именами полиномов (например: pol1 + pol2 * pol3): ";
            getline(cin, input);
            try {
                Polinom result = controller.EvaluatePolinomExpression(key, input);
                cout << "Полином '" << key << "' успешно вычислен и сохранён.\n";
                cout << "Результат: " << result << endl;
            }
            catch (const exception& e) {
                cerr << "Ошибка при вычислении: " << e.what() << endl;
            }
        }

        else if (choice == 6) {
            cout << "Введите название полинома: ";
            cin >> key;
            cout << "Введите переменную (x, y или z), по которой брать производную: ";
            cin >> var;
            Polinom* p = controller.FindPolinom(key);
            if (!p) {
                cout << "Полином с таким ключом не найден.\n";
            }
            else {
                cout << "Производная: " << p->derivative(var) << endl;
            }
        }

        else if (choice == 7) {
            cout << "Введите название полинома: ";
            cin >> key;
            double x, y, z;
            cout << "Введите значения x, y, z через пробел: ";
            cin >> x >> y >> z;
            Polinom* p = controller.FindPolinom(key);
            if (!p) {
                cout << "Полином с таким ключом не найден.\n";
            }
            else {
                double value = p->evaluate(x, y, z);
                cout << "Значение полинома в точке: " << value << endl;
            }
        }

        else if (choice == 8) {
            cout << "Завершение работы.\n";
            break;
        }

        else {
            cout << "Неверный ввод. Повторите попытку.\n";
        }
    }

    return 0;
}
