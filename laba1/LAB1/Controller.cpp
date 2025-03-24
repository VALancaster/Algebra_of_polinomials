#include "Controller.h"

using namespace std;

void Controller::SetActiveTable(TTable* table)
{
	if (table)
		active_table = table;
	else
	{
		cerr << "Ошибка: передана пустая таблица." << endl;
		return;
	}
}

void Controller::AddPolinom(const string& name, const Polinom& pol)
{
	if (active_table)
		active_table->Insert(name, pol);
	else
	{
		cerr << "Ошибка: активная таблица не установлена." << endl;
		return;
	}
}

Polinom Controller::EvaluateExpression(const string& expression)
{
	if (!active_table)
		throw runtime_error("Ошибка: активная таблица не установлена.");
	postfix_processor.SetInfix(expression); // ???
	return postfix_processor.Calculate(*active_table); // ???
}

void Controller::PrintActivetable()
{
	if (active_table)
		active_table->Print();
	else
	{
		cerr << "Ошибка: активная таблица не установлена." << endl;
		return;
	}
}
