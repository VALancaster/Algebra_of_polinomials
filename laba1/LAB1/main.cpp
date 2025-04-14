#include <iostream>
#include <string>
#include <limits>
#include "Controller.h"
#include "Polinom.h"

using namespace std;

// Функция для безопасного чтения целого числа
int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail())
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка оставшегося ввода
    return value;
}

// Функция для безопасного чтения одного символа
char getCharInput(const string& prompt) {
    char c;
    while (true) {
        cout << prompt;
        cin >> c;
        if (!cin.fail())
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a character." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return c;
}

// Функция для безопасного чтения вещественного числа
double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail())
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid number." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Функция для безопасного чтения строки
string getLineInput(const string& prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}

void printMenu() {
    cout << "\n===== POLYNOMIAL MANAGEMENT MENU =====\n";
    cout << "1. Select active table\n";
    cout << "2. Show active table contents\n";
    cout << "3. Add polynomial to tables\n";
    cout << "4. Delete polynomial by key\n";
    cout << "5. Evaluate and save polynomial expression\n";
    cout << "6. Calculate polynomial derivative\n";
    cout << "7. Evaluate polynomial at point\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Controller controller;
    string key, input;
    char var;

    while (true) {
        printMenu();
        int choice = getIntInput("");

        cout << "\n" << endl;

        if (choice == 1) {
            cout << "Select table type:\n"
                << "0 - Array\n"
                << "1 - List\n"
                << "2 - SortedArray\n"
                << "3 - Tree\n"
                << "4 - HashOpen\n"
                << "5 - HashChain\n";
            int index = getIntInput("Your choice: ");
            try {
                controller.SetActiveTable(index);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }

        else if (choice == 2) {
            controller.PrintActiveTable();
        }

        else if (choice == 3) {
            key = getLineInput("Enter variable name for the polynomial: ");
            input = getLineInput("Enter polynomial (e.g., 2x^2y + 3xy^2 - 1): ");
            try {
                Polinom p(input);
                controller.AddPolinom(key, p);
            }
            catch (const exception& e) {
                cerr << "Error creating polynomial: " << e.what() << endl;
            }
        }

        else if (choice == 4) {
            key = getLineInput("Enter name of polynomial to delete: ");
            controller.DeletePolinom(key);
        }

        else if (choice == 5) {
            key = getLineInput("Enter name for resulting polynomial: ");
            input = getLineInput("Enter expression with polynomial names (e.g., pol1 + pol2 * pol3): ");
            try {
                Polinom result = controller.EvaluatePolinomExpression(key, input);
                cout << "Polynomial '" << key << "' successfully calculated and saved.\n";
                cout << "Result: " << result << endl;
            }
            catch (const exception& e) {
                cerr << "Calculation error: " << e.what() << endl;
            }
        }

        else if (choice == 6) {
            key = getLineInput("Enter polynomial name: ");
            var = getCharInput("Enter variable (x, y or z) to differentiate by: ");
            Polinom* p = controller.FindPolinom(key);
            if (!p) {
                cout << "Polynomial with this key not found.\n";
            }
            else {
                cout << "Derivative: " << p->derivative(var) << endl;
            }
        }

        else if (choice == 7) {
            key = getLineInput("Enter polynomial name: ");
            double x = getDoubleInput("Enter x value: ");
            double y = getDoubleInput("Enter y value: ");
            double z = getDoubleInput("Enter z value: ");
            Polinom* p = controller.FindPolinom(key);
            if (!p) {
                cout << "Polynomial with this key not found.\n";
            }
            else {
                double value = p->evaluate(x, y, z);
                cout << "Polynomial value at point: " << value << endl;
            }
        }

        else if (choice == 8) {
            cout << "Exiting program.\n";
            break;
        }

        else {
            cout << "Invalid input. Please try again.\n";
        }
    }

    return 0;
}