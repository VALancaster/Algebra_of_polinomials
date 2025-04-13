#include "Controller.h"

using namespace std;

Controller::Controller()
{
	// инициализация всех таблиц
	tables.push_back(new TArrayTable<string, Polinom>());
	tables.push_back(new TListTable<string, Polinom>());
	tables.push_back(new TSortedArrayTable<string, Polinom>());
	tables.push_back(new TTreeTable<string, Polinom>());
	tables.push_back(new THashTableOpen<string, Polinom>());
	tables.push_back(new THashTableChain<string, Polinom>());

	// по умолчанию активная таблица
	if (!tables.empty())
		active_table = tables[0];
}

Controller::~Controller()
{
	for (auto table : tables)
		delete table;
}

void Controller::SetActiveTable(int index)
{
	if (index >= 0 && index < static_cast<int>(tables.size()))
	{
		active_table = tables[index];
		cout << "Active table set to: " << active_table->GetName() << endl;
	}
	else
	{
		throw out_of_range("Invalid table index");
	}
}

void Controller::AddPolinom(const string& name, const Polinom& pol)
{
	for (auto table : tables)
		table->Insert(name, pol);
	cout << "Polinom " << name << " added to all tables." << endl;
}

void Controller::DeletePolinom(const string& name)
{
	for (auto table : tables)
		table->Delete(name);
	cout << "Polinom " << name << " deleted from all tables." << endl;
}

void Controller::PrintActiveTable() const
{
	if (active_table)
	{
		cout << "Active table: " << active_table->GetName() << endl;
		active_table->Print();
	}
	else
	{
		cout << "No active table selected." << endl;
	}
}

Polinom* Controller::FindPolinom(const string& name)
{
	for (auto table : tables)
	{
		Polinom* p = table->Find(name);
		if (p)
			return p;
	}
	return nullptr; // не найдено ни в одной таблице
}

Polinom Controller::EvaluatePolinomExpression(const string& name, const string& expression)
{
	TPostfix postfix(expression);
	vector<string> operand_names = postfix.GetOperands();
	map<string, Polinom> namedPolinoms;
	for (const string& pol_name : operand_names)
	{
		Polinom* p = active_table->Find(pol_name);
		if (!p)
			throw runtime_error("Polinom not found: " + pol_name);
		namedPolinoms[pol_name] = *p;
	}
	Polinom result = postfix.Calculate(namedPolinoms);
	active_table->Insert(name, result);
	return result;
}



/*
double Controller::EvaluateExpression(const string& expression, double x, double y, double z)
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

*/