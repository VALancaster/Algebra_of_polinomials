#include "Controller.h"

using namespace std;

Controller::Controller()
{
	// инициализация всех таблиц
	tables.push_back(new TArrayTable());
	tables.push_back(new TListTable());
	tables.push_back(new TSortedArrayTable());
	tables.push_back(new TTreeTable());
	tables.push_back(new THashTableOpen());
	tables.push_back(new THashTableChain());

	// по умолчанию активная таблица
	if (!tables.empty())
		active_table = tables[0];
}

~Controller::Controller()
{
	for (auto table : tables)
		delete table;
}

void SetActiveTable(int index)
{
	if (index >= 0 && index < tables.size())
	{
		active_table = tables[index];
		cout << "Active table set to: " << active_table->GetName() << endl;
	}
	else
		throw out_of_range("Invalid table index");
}

void AddPolinom(const string& name, const Polinom& pol)
{
	for (auto table : tables)
		table->Insert(name, pol);
	cout << "Polinom " << name << " added to all tables." << endl;
}

void DeletePolinom(const string& name)
{
	for (auto table : tables)
		table->Delete(name); 
	cout << "Polinom " << name << " deleted from all tables." << endl;
}

double EvaluateExpression(const string& expression, double x, double y, double z)
{
	try
	{
		TPostfix postfix(expression);
		double result = postfix.Calculate(x, y, z);
		cout << "Expression evaluated successfully." << endl;
		return result;
	}
	catch (const exception& e)
	{
		cerr << "Error evaluating expression: " << e.what() << endl;
		throw;
	}
}

void PrintActiveTable() const
{
	if (active_table)
	{
		cout << "Active table: " << active_table->GetName() << endl;
		active_table->PrintTable();
	}
	else
		cout << "No active table selected." << endl;
}