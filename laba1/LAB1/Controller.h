#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "TTable.h"
#include "Postfix.h"
#include <vector>
#include <iostream>

class Controller // контроллер таблиц
{
	vector<TTable*> tables;
	TTable* active_table;
	TPostfix postfix_processor;
public:
	Controller(): active_table(nullptr) {}
	void SetActiveTable(TTable* table);
	void AddPolinom(const std::string& name, const Polinom& pol);
	Polinom EvaluateExpression(const std::string& expression);
	void PrintActivetable();
};

#endif