#include "polinom.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

Polinom::Polinom(const string& str) 
{
	size_t pos = 0;
	size_t length = str.size();
	while (pos < length) 
	{
		while (pos < length && isspace(str[pos])) // пропуск если пробелы и табуляция
			pos++;
		if (pos >= length) 
			break;
		size_t startPos = pos; // начало строки
		if (str[pos] == '+' || str[pos] == '-') // пропуск знака
			pos++;
		while (pos < length && !isspace(str[pos]) && str[pos] != '+' && str[pos] != '-') // пока не знаки, пробелы и табуляция
			pos++;
		string monomStr = str.substr(startPos, pos - startPos); // подстрока - моном
		if (!monomStr.empty() && monomStr.find_first_not_of(" \t") != -1) // не пусто и все символы подстроки - не пробелы и не табуляция
		{ 
			Monom monom(monomStr); // создание монома из строки
			addMonom(monom);
		}
	}
	removeZeroMonoms();
}

Polinom::Polinom(const Polinom& other) {
	for (const auto& monom : other.monoms) 
		monoms.addToEnd(monom);
}

void Polinom::removeZeroMonoms() 
{
	size_t i = 0;
	while (i < monoms.length()) 
	{
		if (monoms.getItem(i).coef == 0.0) // если коэффициент 0
			monoms.eraseAt(i);
		else 
			++i;
	}
}

void Polinom::addMonom(const Monom& monom) 
{
	if (monom.coef == 0.0) // если коэффициент = 0
		return;
	bool found = false;
	for (auto& existingMonom : monoms) 
	{
		if (existingMonom.x == monom.x && existingMonom.y == monom.y && existingMonom.z == monom.z)
		{
			existingMonom.coef += monom.coef; // если степени мономов одинаковые, то суммируем коэффициенты
			found = true;
			break;
		}
	}
	if (!found) 
		monoms.addToEnd(monom);
}

double Polinom::evaluate(double x, double y, double z) const 
{
	double result = 0.0;
	for (auto& monom : monoms) 
		result += monom.evaluate(x, y, z);
	return result;
}

string Polinom::toString() const {
	string result = ""; // сначала пустая строка

	for (size_t i = 0; i < monoms.length(); ++i) 
	{
		const Monom& monom = monoms.getItem(i); // берется моном из списка
		string monomStr = monom.toString(); // каждый моном превращается в строку
		if (!monomStr.empty()) 
		{
			if (result.empty()) // текущий моном - первый
				result = monomStr;
			else 
				result += monomStr[0] == '-' ? monomStr : "+" + monomStr; // если моном начинается с минуса, он добавляется как есть
				// если моном начинается с плюса, перед ним добавляется знак +
		}
	}
	return result.empty() ? "0" : result; // если строка осталась пустой - вернется '0', иначе полином
}

Polinom Polinom::derivative(char var) const 
{
	Polinom result;
	for (const auto& monom : monoms) 
	{
		Monom deriv = monom;
		if (var == 'x' && deriv.x > 0)  
		{
			deriv.coef *= deriv.x;
			deriv.x -= 1;
			result.addMonom(deriv);
		}
		if (var == 'y' && deriv.y > 0)
		{
			deriv.coef *= deriv.y;
			deriv.y -= 1;
			result.addMonom(deriv);
		}
		if (var == 'z' && deriv.z > 0)
		{
			deriv.coef *= deriv.z;
			deriv.z -= 1;
			result.addMonom(deriv);
		}
	}
	result.removeZeroMonoms();
	return result;
}

Polinom& Polinom::operator=(const Polinom& other) 
{
	if (this != &other) 
	{
		monoms.reset();
		for (const auto& monom : other.monoms) 
			monoms.addToEnd(monom);
	}
	return *this;
}

Polinom Polinom::operator+(const Polinom& other) const 
{
	Polinom result(*this);
	result += other;
	return result;
}

Polinom& Polinom::operator+=(const Polinom& other) 
{
	for (const auto& monom : other.monoms) 
		addMonom(monom);
	removeZeroMonoms();
	return *this;
}

Polinom Polinom::operator-(const Polinom& other) const 
{
	Polinom result(*this);
	result -= other;
	return result;
}

Polinom& Polinom::operator-=(const Polinom& other) 
{
	for (const auto& monom : other.monoms)
	{
		Monom invertedMonom = monom;
		invertedMonom.coef = -invertedMonom.coef;
		addMonom(invertedMonom);
	}
	removeZeroMonoms();
	return *this;
}

Polinom Polinom::operator*(double constant) const 
{
	Polinom result(*this);
	result *= constant;
	return result;
}

Polinom& Polinom::operator*=(double constant) 
{
	if (constant == 0.0) 
		monoms.reset(); // cписок очищается
	else 
	{
		for (auto& monom : monoms) 
			monom.coef *= constant; // домножение каждого коэффициента
	}
	return *this;
}

Polinom Polinom::operator*(const Polinom& other) const 
{
	Polinom result;
	for (const auto& monom1 : monoms) // берется моном исходного полинома
	{
		for (const auto& monom2 : other.monoms) // берется моном полинома, на который умножаем
		{
			Monom product = monom1 * monom2;
			result.addMonom(product); // добавляет моном с упрощением
		}
	}
	result.removeZeroMonoms();
	return result;
}

Polinom& Polinom::operator*=(const Polinom& other) 
{
	Polinom result = (*this) * other;
	*this = result; // результат копируется из временного монома в текущий
	return *this;
}

bool Polinom::operator==(const Polinom& other) const 
{
	if (monoms.length() != other.monoms.length()) 
		return false;
	for (size_t i = 0; i < monoms.length(); ++i) 
	{
		if (monoms.getItem(i) != other.monoms.getItem(i)) 
			return false;
	}
	return true;
}

bool Polinom::operator!=(const Polinom& other) const 
{
	return !(*this == other);
}

ostream& operator<<(ostream& out, const Polinom& polinom) 
{
	out << polinom.toString();
	return out;
}
