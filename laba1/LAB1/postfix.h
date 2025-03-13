#ifndef POSTFIX_H
#define POSTFIX_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <limits>
#include "stack.h"

using namespace std;

class TPostfix {
	string infix;
	string postfix;
	vector<string> lexems;
	map<string, double> operands;
	static map<char, int> priority;
	void ParseInf();
	void ToPostfix();
public:
	TPostfix(string infx);
	string GetInfix() const;
	string GetPostfix() const;
	vector<string> GetOperands() const;
	double Calculate(const map<string, double>& values);
};

#endif

