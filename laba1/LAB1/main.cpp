#include <iostream>
#include <string>
#include "Controller.h"
#include "Polinom.h"

using namespace std;

void printMenu() {
    cout << "\n===== МЕНЮ УПРАВЛЕНИЯ ПОЛИНОМАМИ =====\n";
    cout << "1. Выбрать активную таблицу\n";
    cout << "2. Вывести содержимое активной таблицы\n";
    cout << "3. Добавить полином в таблицу\n";
    cout << "4. Удалить полином по ключу\n";
    cout << "5. Задать полином\n";
    cout << "6. Взять производную от полинома\n";
    cout << "7. Вычислить значение полинома в точке\n";
    cout << "8. Выйти\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Controller controller;
    string key, input;
    char var;
    TPostfix postfix_processor;

    while (true) {
        printMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Выберите таблицу (0 - Array, 1 - List, 2 - SortedArray, 3 - Tree, 4 - HashOpen, 5 - HashChain): ";
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
            try 
            {
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
            cout << "Задайте новый полином. Введите его название: ";
            cin >> key;
            cin.ignore();
            cout << "Введите значение полинома (алгебраическое выражение. например, pol1 + pol2 * pol3 - pol4): ";
            getline(cin, input);
            try {
                Polinom result = controller.EvaluatePolinomExpression(key, input);
                cout << "Полином '" << key << "' успешно вычислен и сохранен.\n";
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
            Polinom* p = controller.FindPolinomInActiveTable(key);
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
            Polinom* p = controller.FindPolinomInActiveTable(key);
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












case 5: {
    string input;
    cout << "Введите выражение (например, new_pol = 2 * pol1 + 3.6 * q - const1): ";
    getline(cin, input);

    size_t eq_pos = input.find('=');
    if (eq_pos == string::npos) {
        cout << "Ошибка: выражение должно содержать '='\n";
        break;
    }

    string name = input.substr(0, eq_pos);
    string expression = input.substr(eq_pos + 1);

    // удалим пробелы вокруг имени (вдруг пользователь ввёл "  new_pol   =  ...")
    name.erase(0, name.find_first_not_of(" \t"));
    name.erase(name.find_last_not_of(" \t") + 1);

    try {
        Polinom result = controller.EvaluatePolinomExpression(name, expression);
        cout << "Полином '" << name << "' успешно вычислен и сохранён.\n";
        result.Print(); // если хочешь сразу показать результат
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }

    break;
}
