#include <iostream>
#include <string>
#include "Controller.h"
#include "Polinom.h"

using namespace std;

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
        int choice;
        cin >> choice;
        cin.ignore();

        cout << "\n" << endl;

        if (choice == 1) {
            cout << "Select table type:\n"
                << "0 - Array\n"
                << "1 - List\n"
                << "2 - SortedArray\n"
                << "3 - Tree\n"
                << "4 - HashOpen\n"
                << "5 - HashChain\n"
                << "Your choice: ";
            int index;
            cin >> index;
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
            cout << "Enter variable name for the polynomial: ";
            cin >> key;
            cin.ignore();
            cout << "Enter polynomial (e.g., 2x^2y + 3xy^2 - 1): ";
            getline(cin, input);
            try {
                Polinom p(input);
                controller.AddPolinom(key, p);
            }
            catch (const exception& e) {
                cerr << "Error creating polynomial: " << e.what() << endl;
            }
        }

        else if (choice == 4) {
            cout << "Enter name of polynomial to delete: ";
            cin >> key;
            controller.DeletePolinom(key);
        }

        else if (choice == 5) {
            cout << "Enter name for resulting polynomial: ";
            cin >> key;
            cin.ignore();
            cout << "Enter expression with polynomial names (e.g., pol1 + pol2 * pol3): ";
            getline(cin, input);
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
            cout << "Enter polynomial name: ";
            cin >> key;
            cout << "Enter variable (x, y or z) to differentiate by: ";
            cin >> var;
            Polinom* p = controller.FindPolinom(key);
            if (!p) {
                cout << "Polynomial with this key not found.\n";
            }
            else {
                cout << "Derivative: " << p->derivative(var) << endl;
            }
        }

        else if (choice == 7) {
            cout << "Enter polynomial name: ";
            cin >> key;
            double x, y, z;
            cout << "Enter x, y, z values separated by spaces: ";
            cin >> x >> y >> z;
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
