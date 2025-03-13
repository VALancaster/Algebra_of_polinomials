#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "TTable.h"
#include "Postfix.h"
#include <vector>

class Controller // контроллер таблиц
{
	vector<TTable*> tables;
	TTable* active_table;
	TPostfix postfix_processor;
public:
	void SetActiveTable(TTable* table);
	void AddPolinom(const std::string& name, const Polinom& pol);
	Polinom EvaluateExpression(const std::string& expression);
	void PrintActivetable();
};

#endif