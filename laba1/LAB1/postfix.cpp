#include "postfix.h"
#include "stack.h"
#include <sstream>

map<char, int> TPostfix::priority = {{'(', 0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}};

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
	for (const string& elem : TPostfix::lexems) 
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
			postfix += elem + " ";
			operands[elem] = Polinom();
		}
	}
	while (!s.IsEmpty()) 
	{
		Stack_el = s.Pop();
		postfix += Stack_el + " ";
	}
}

Polinom TPostfix::Calculate(map<string, Polinom>& namedPolinoms)
{
	TStack<Polinom> st;
	istringstream iss(postfix);
	string lexem;

	while (iss >> lexem) 
	{
		if (lexem == "+") 
		{
			Polinom b = st.Pop();
			Polinom a = st.Pop();
			st.Push(a + b);
		}
		else if (lexem == "-") 
		{
			Polinom b = st.Pop();
			Polinom a = st.Pop();
			st.Push(a - b);
		}
		else if (lexem == "*") 
		{
			Polinom b = st.Pop();
			Polinom a = st.Pop();
			st.Push(a * b);
		}
		/*
		else if (lexem == "/") 
		{
			right = st.Pop();
			left = st.Pop();
			if (right == 0)
				throw runtime_error("Division by zero");
			st.Push(left / right);
		}
		*/
		else 
		{
			if (namedPolinoms.find(lexem) == namedPolinoms.end())
				throw runtime_error("Operand '" + lexem + "' not defined");
			st.Push(namedPolinoms[lexem]);
		}
	}
	return st.Pop();
}

