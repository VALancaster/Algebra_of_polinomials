#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "TTable.h"
#include "TArrayTable.h"
#include "THashTableChain.h"
#include "THashTableOpen.h"
#include "TListTable.h"
#include "TSortedArrayTable.h"
#include "TTreeTable.h"
#include "postfix.h"
#include <vector>
#include <iostream>

using namespace std;

class Controller // контроллер таблиц
{
	vector<TTable<string, Polinom>*> tables;
	TTable<string, Polinom>* active_table;
public:
	Controller(): active_table(nullptr) {}
	Controller(const Controller& source) = delete;
	Controller& operator=(const Controller& source) = delete;

	~Controller();

	void SetActiveTable(int index);
	void AddPolinom(const string& name, const Polinom& pol);
	void DeletePolinom(const string& name);
	//Polinom EvaluateExpression(const string& expression, double x, double y, double z);
	Polinom EvaluatePolinomExpression(const string& name, const string& expression);
	void PrintActiveTable() const;
	Polinom* FindPolinom(const string& name);
};

#endif