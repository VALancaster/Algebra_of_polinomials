#include "postfix.h"
#include "stack.h"
#include <sstream>

map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

TPostfix::TPostfix(string infx) : infix(infx) 
{
	if (infx.empty())
		throw invalid_argument("Infix is empty");
	ToPostfix();
}

string TPostfix::GetInfix() const 
{
	return infix;
}

string TPostfix::GetPostfix() const 
{
	return postfix;
}

vector<string> TPostfix::GetOperands() const // вернет вектор операндов (символов)
{ 
	vector<string> oper;
	for (const auto& item : operands) 
		oper.push_back(item.first);
	return oper;
}

void TPostfix::ParseInf() 
{
	string operand;
	for (char c : infix) 
	{
		if (isalnum(c) || c == '.' || c == '^')
			operand += c;
		else 
		{
			if (!operand.empty()) 
			{
				lexems.push_back(operand);
				operand.clear();
			}
			if (!isspace(c)) 
				lexems.push_back(string(1, c));
		}
	}
	if (!operand.empty()) 
		lexems.push_back(operand);
}

void TPostfix::ToPostfix() 
{
	ParseInf();
	TStack<string> s;
	string Stack_el;
	for (const string& elem : lexems) 
	{
		if (elem == "(") 
			s.Push(elem);
		else if (elem == ")") 
		{
			Stack_el = s.Pop();
			while (Stack_el != "(") 
			{
				postfix += Stack_el + " ";
				Stack_el = s.Pop();
			}
		}
		else if (priority.find(elem[0]) != priority.end() && elem.size() == 1) // Оператор
		{  
			while (!s.IsEmpty()) 
			{
				Stack_el = s.Pop();
				if (priority[elem[0]] <= priority[Stack_el[0]]) 
					postfix += Stack_el + " ";
				else 
				{
					s.Push(Stack_el);
					break;
				}
			}
			s.Push(elem);
		}
		else 
		{
			if (elem.find_first_not_of("0123456789.") == -1) // символ - число (включает цифры или точки)
				operands[elem] = Monom(stod(elem), 0, 0, 0); // число как моном со степенями 0
			else // Моном
				operands[elem] = Monom(elem); // добавление монома в map как операнда
			postfix += elem + " ";
		}
	}
	while (!s.IsEmpty()) 
	{
		Stack_el = s.Pop();
		postfix += Stack_el + " ";
	}
}

double TPostfix::Calculate(double x_val, double y_val, double z_val)
{
	TStack<double> st;
	double left, right;
	istringstream iss(postfix);
	string lexem;

	while (iss >> lexem) 
	{
		if (lexem == "+") 
		{
			right = st.Pop();
			left = st.Pop();
			st.Push(left + right);
		}
		else if (lexem == "-") 
		{
			right = st.Pop();
			left = st.Pop();
			st.Push(left - right);
		}
		else if (lexem == "*") 
		{
			right = st.Pop();
			left = st.Pop();
			st.Push(left * right);
		}
		else if (lexem == "/") 
		{
			right = st.Pop();
			left = st.Pop();
			if (right == 0)
				throw runtime_error("Division by zero");
			st.Push(left / right);
		}
		else 
		{
			if (operands.find(lexem) != operands.end())
				st.Push(operands[lexem].evaluate(x_val, y_val, z_val));
			else
				st.Push(stod(lexem));
		}
	}
	return st.Pop();
}

