#include "postfix.h"
#include "stack.h"
#include <sstream>

map<char, int> TPostfix::priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

TPostfix::TPostfix(string infx) : infix(infx) {
	if (infx.empty())
		throw invalid_argument("Infix is empty");
	ToPostfix();
}

string TPostfix::GetInfix() const {
	return infix;
}

string TPostfix::GetPostfix() const {
	return postfix;
}

vector<string> TPostfix::GetOperands() const {
	vector<string> oper;
	for (const auto& item : operands) {
		oper.push_back(item.first);
	}
	return oper;
}

void TPostfix::ParseInf() {
	string operand;
	for (char c : infix) {
		if (isalnum(c) || c == '.') {
			operand += c;
		}
		else {
			if (!operand.empty()) {
				lexems.push_back(operand);
				operand.clear();
			}
			if (!isspace(c)) {
				lexems.push_back(string(1, c));
			}
		}
	}
	if (!operand.empty()) {
		lexems.push_back(operand);
	}
}

void TPostfix::ToPostfix() {
	ParseInf();
	TStack<string> s;
	string Stack_el;
	for (const string& elem : lexems) {
		if (elem == "(") {
			s.Push(elem);
		}
		else if (elem == ")") {
			Stack_el = s.Pop();
			while (Stack_el != "(") {
				postfix += Stack_el + " ";
				Stack_el = s.Pop();
			}
		}
		else if (priority.find(elem[0]) != priority.end() && elem.size() == 1) {  // Если это оператор
			while (!s.IsEmpty()) {
				Stack_el = s.Pop();
				if (priority[elem[0]] <= priority[Stack_el[0]]) {
					postfix += Stack_el + " ";
				}
				else {
					s.Push(Stack_el);
					break;
				}
			}
			s.Push(elem);
		}
		else {
			if (elem.find_first_not_of("0123456789.") == string::npos) {
				postfix += elem + " ";
			}
			else {
				operands[elem] = 0.0;
				postfix += elem + " ";
			}
		}
	}
	while (!s.IsEmpty()) {
		Stack_el = s.Pop();
		postfix += Stack_el + " ";
	}
}

double TPostfix::Calculate(const map<string, double>& values) {
	for (const auto& val : values) {
		if (operands.find(val.first) != operands.end()) {
			operands[val.first] = val.second;
		}
	}
	TStack<double> st;
	double left, right;
	istringstream iss(postfix);
	string lexem;
	while (iss >> lexem) {
		if (lexem == "+") {
			right = st.Pop();
			left = st.Pop();
			st.Push(left + right);
		}
		else if (lexem == "-") {
			right = st.Pop();
			left = st.Pop();
			st.Push(left - right);
		}
		else if (lexem == "*") {
			right = st.Pop();
			left = st.Pop();
			st.Push(left * right);
		}
		else if (lexem == "/") {
			right = st.Pop();
			left = st.Pop();
			st.Push(left / right);
		}
		else {
			if (lexem.find_first_not_of("0123456789.") == string::npos) {
				st.Push(stod(lexem));
			}
			else {
				st.Push(operands.at(lexem));
			}
		}
	}
	return st.Pop();
}
