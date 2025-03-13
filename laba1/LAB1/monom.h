#ifndef MONOM_H
#define MONOM_H

using namespace std;
#include <string>
#include <unordered_map>

static const int MAX_DEGREE = 9;

class Monom {
public:
	double coeff;
	std::unordered_map<char, int> powers;
	int getDegreeHash() const;
	Monom(double coeff = 0.0, int powerX = 0, int powerY = 0, int powerZ = 0);
	Monom(const std::string& expression);

	bool operator<(const Monom& other) const;
	bool operator>(const Monom& other) const;
	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;

	Monom operator*(const Monom& other) const;

	double evaluate(double x, double y, double z) const;
	std::string toString() const;

};
#endif
