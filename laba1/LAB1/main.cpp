#include <iostream>
#include <string>
#include "Controller.h"
#include "Polinom.h"

using namespace std;

void PrintMainMenu() {
    cout << "\n=== Главное меню ===\n";
    cout << "1. Выбрать активную таблицу\n";
    cout << "2. Вывести активную таблицу\n";
    cout << "3. Добавить полином\n";
    cout << "4. Удалить полином\n";
    cout << "5. Выполнить операцию с полиномами (+, -, *)\n";
    cout << "6. Взять производную от полинома\n";
    cout << "7. Вычислить значение полинома в точке\n";
    cout << "8. Завершить программу\n";
    cout << "=====================\n";
    cout << "Введите номер операции: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Controller controller;
    int choice;

    while (true) {
        PrintMainMenu();
        cin >> choice;
        cin.ignore(); // очищаем буфер после ввода числа

        try {
            if (choice == 1) {
                cout << "Введите индекс таблицы (0 - массив, 1 - список, 2 - отсортированный массив, 3 - дерево, 4 - хеш (открытая), 5 - хеш (цепочки)): ";
                int index;
                cin >> index;
                controller.SetActiveTable(index);
            }
            else if (choice == 2) {
                controller.PrintActiveTable();
            }
            else if (choice == 3) {
                string key, input;
                cout << "Введите ключ (имя полинома): ";
                cin >> key;
                cin.ignore();

                cout << "Введите полином (используйте переменные x, y, z): ";
                getline(cin, input);

                Polinom pol(input);
                controller.active_table->Insert(key, pol);
                cout << "Полином добавлен в активную таблицу." << endl;
            }
            else if (choice == 4) {
                string key;
                cout << "Введите ключ полинома для удаления: ";
                cin >> key;
                controller.active_table->Delete(key);
                cout << "Полином удален из активной таблицы (если существовал)." << endl;
            }
            else if (choice == 5) {
                string expr;
                cout << "Введите выражение с использованием ключей полиномов и операций (+, -, *): ";
                getline(cin, expr);
                cout << "Введите значения переменных x y z через пробел: ";
                double x, y, z;
                cin >> x >> y >> z;
                double result = controller.EvaluateExpression(expr, x, y, z);
                cout << "Результат: " << result << endl;
                cin.ignore(); // чтобы верно обрабатывать следующий ввод
            }
            else if (choice == 6) {
                string key;
                char var;
                cout << "Введите ключ полинома: ";
                cin >> key;
                cout << "Введите переменную для дифференцирования (x, y или z): ";
                cin >> var;
                Polinom pol = controller.active_table->Get(key);
                Polinom derived = pol.derivative(var);
                cout << "Производная: " << derived << endl;
            }
            else if (choice == 7) {
                string key;
                cout << "Введите ключ полинома: ";
                cin >> key;
                double x, y, z;
                cout << "Введите значения переменных x y z через пробел: ";
                cin >> x >> y >> z;
                Polinom pol = controller.active_table->Get(key);
                double result = pol.evaluate(x, y, z);
                cout << "Результат: " << result << endl;
            }
            else if (choice == 8) {
                cout << "Завершение работы программы..." << endl;
                break;
            }
            else {
                cout << "Неверный номер команды. Попробуйте снова." << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    return 0;
}