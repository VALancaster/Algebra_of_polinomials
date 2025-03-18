#ifndef POLINOM_H
#define POLINOM_H

#include "singlylist.h"
#include "monom.h"
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Polinom 
{
private:
	SinglyList<Monom> monoms;
public:
	Polinom() = default;
	Polinom(const string& str);
	Polinom(const Polinom& other);

	void removeZeroMonoms();

	void addMonom(const Monom& monom);
	double evaluate(double x, double y, double z) const;
	string toString() const;
	Polinom derivative(char var) const;

	Polinom& operator=(const Polinom& other);
	Polinom operator+(const Polinom& other) const;
	Polinom operator-(const Polinom& other) const;
	Polinom operator*(const Polinom& other) const;
	Polinom operator*(double constant) const;
	Polinom& operator+=(const Polinom& other);
	Polinom& operator-=(const Polinom& other);
	Polinom& operator*=(const Polinom& other);
	Polinom& operator*=(double constant);

	bool operator==(const Polinom& other) const;
	bool operator!=(const Polinom& other) const;

	friend ostream& operator<<(ostream& out, const Polinom& polinom);
};

#endif