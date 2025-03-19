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
	{
		monoms.addToEnd(monom);
	}
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

Polinom Polinom::derivative(char var) const {
	Polinom result;

	for (const auto& monom : monomList) {
		Monom deriv = monom;
		if (deriv.powers.count(var) > 0 && deriv.powers.at(var) > 0) {
			deriv.coeff *= deriv.powers[var];
			deriv.powers[var] -= 1;
			result.addMonom(deriv);
		}
	}

	result.removeZeroMonoms();
	return result;
}

Polinom& Polinom::operator=(const Polinom& other) {
	if (this != &other) {
		monomList.reset();
		for (const auto& monom : other.monomList) {
			monomList.addToEnd(monom);
		}
	}
	return *this;
}

Polinom Polinom::operator+(const Polinom& other) const {
	Polinom result(*this);
	result += other;
	return result;
}

Polinom& Polinom::operator+=(const Polinom& other) {
	for (const auto& monom : other.monomList) {
		addMonom(monom);
	}
	removeZeroMonoms();
	return *this;
}

Polinom Polinom::operator-(const Polinom& other) const {
	Polinom result(*this);
	result -= other;
	return result;
}

Polinom& Polinom::operator-=(const Polinom& other) {
	for (auto it = other.monomList.begin(); it != other.monomList.end(); ++it) {
		Monom invertedMonom = *it;
		invertedMonom.coeff = -invertedMonom.coeff;
		addMonom(invertedMonom);
	}
	removeZeroMonoms();
	return *this;
}

Polinom Polinom::operator*(double constant) const {
	Polinom result(*this);
	result *= constant;
	return result;
}

Polinom& Polinom::operator*=(double constant) {
	if (constant == 0.0) {
		monomList.reset();
	}
	else {
		for (auto& monom : monomList) {
			monom.coeff *= constant;
		}
	}
	return *this;
}

Polinom Polinom::operator*(const Polinom& other) const {
	Polinom result;

	for (const auto& monom1 : monomList) {
		for (const auto& monom2 : other.monomList) {
			Monom product = monom1 * monom2;
			result.addMonom(product);
		}
	}
	result.removeZeroMonoms();
	return result;
}

Polinom& Polinom::operator*=(const Polinom& other) {
	Polinom result = (*this) * other;
	*this = result;
	return *this;
}

bool Polinom::operator==(const Polinom& other) const {
	if (monomList.length() != other.monomList.length()) {
		return false;
	}
	for (size_t i = 0; i < monomList.length(); ++i) {
		if (monomList.getItem(i) != other.monomList.getItem(i)) {
			return false;
		}
	}
	return true;
}

bool Polinom::operator!=(const Polinom& other) const {
	return !(*this == other);
}

ostream& operator<<(ostream& out, const Polinom& polinom) {
	out << polinom.toString();
	return out;
}
