#ifndef POLINOM_H
#define POLINOM_H

using namespace std;
#include "singlylist.h"
#include "monom.h"
#include <string>
#include <sstream>
#include <cctype>

class Polinom {
public:
	SinglyList<Monom> monomList;
	void removeZeroMonoms();
	Polinom() {};
	Polinom(const std::string& polynomialStr);
	Polinom(const Polinom& other);

	void addMonom(const Monom& monom);
	double evaluate(double x, double y, double z) const;
	std::string toString() const;
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

	friend std::ostream& operator<<(std::ostream& out, const Polinom& polinom);
};

#endif