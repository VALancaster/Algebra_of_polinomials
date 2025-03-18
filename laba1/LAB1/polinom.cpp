#include "polinom.h"
#include "monom.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <list>

using namespace std;

class Polinom {
private:
	list<Monom> monomList;

public:
	Polinom(const string& polynomialStr) {
		size_t pos = 0;
		size_t length = polynomialStr.size();

		while (pos < length) {
			while (pos < length && isspace(polynomialStr[pos])) {
				pos++;
			}

			if (pos >= length) break;

			size_t startPos = pos;

			if (polynomialStr[pos] == '+' || polynomialStr[pos] == '-') {
				pos++;
			}

			while (pos < length && !isspace(polynomialStr[pos]) && polynomialStr[pos] != '+' && polynomialStr[pos] != '-') {
				pos++;
			}

			string monomStr = polynomialStr.substr(startPos, pos - startPos);
			if (!monomStr.empty() && monomStr.find_first_not_of(" \t") != string::npos) {
				Monom monom(monomStr);
				addMonom(monom);
			}
		}

		removeZeroMonoms();
	}

	Polinom(const Polinom& other) {
		for (const auto& monom : other.monomList) {
			monomList.push_back(monom);
		}
	}

	void removeZeroMonoms() {
		monomList.remove_if([](const Monom& monom) { return monom.getCoef() == 0.0; });
	}

	void addMonom(const Monom& monom) {
		if (monom.getCoef() == 0.0) {
			return;
		}

		bool found = false;
		for (auto& existingMonom : monomList) {
			if (existingMonom.getX() == monom.getX() && existingMonom.getY() == monom.getY() && existingMonom.getZ() == monom.getZ()) {
				existingMonom.setCoef(existingMonom.getCoef() + monom.getCoef());
				found = true;
				break;
			}
		}

		if (!found) {
			monomList.push_back(monom);
		}
	}

	double evaluate(double x, double y, double z) const {
		double result = 0.0;
		for (const auto& monom : monomList) {
			result += monom.evaluate(x, y, z);
		}
		return result;
	}

	string toString() const {
		string result = "";

		for (const auto& monom : monomList) {
			string monomStr = monom.toString();

			if (!monomStr.empty()) {
				if (result.empty()) {
					result = monomStr;
				}
				else {
					result += monomStr[0] == '-' ? monomStr : "+" + monomStr;
				}
			}
		}

		return result.empty() ? "0" : result;
	}

	Polinom derivative(char var) const {
		Polinom result;

		for (const auto& monom : monomList) {
			Monom deriv = monom;
			int degree = (var == 'x') ? deriv.getX() : (var == 'y') ? deriv.getY() : deriv.getZ();
			if (degree > 0) {
				double newCoef = deriv.getCoef() * degree;
				(var == 'x' ? deriv.setX(degree - 1) : (var == 'y' ? deriv.setY(degree - 1) : deriv.setZ(degree - 1)));
				deriv.setCoef(newCoef);
				result.addMonom(deriv);
			}
		}

		result.removeZeroMonoms();
		return result;
	}

	Polinom& operator=(const Polinom& other) {
		if (this != &other) {
			monomList.clear();
			for (const auto& monom : other.monomList) {
				monomList.push_back(monom);
			}
		}
		return *this;
	}

	Polinom operator+(const Polinom& other) const {
		Polinom result(*this);
		result += other;
		return result;
	}

	Polinom& operator+=(const Polinom& other) {
		for (const auto& monom : other.monomList) {
			addMonom(monom);
		}
		removeZeroMonoms();
		return *this;
	}

	Polinom operator-(const Polinom& other) const {
		Polinom result(*this);
		result -= other;
		return result;
	}

	Polinom& operator-=(const Polinom& other) {
		for (const auto& monom : other.monomList) {
			Monom invertedMonom = monom;
			invertedMonom.setCoef(-invertedMonom.getCoef());
			addMonom(invertedMonom);
		}
		removeZeroMonoms();
		return *this;
	}

	Polinom operator*(double constant) const {
		Polinom result(*this);
		result *= constant;
		return result;
	}

	Polinom& operator*=(double constant) {
		if (constant == 0.0) {
			monomList.clear();
		}
		else {
			for (auto& monom : monomList) {
				monom.setCoef(monom.getCoef() * constant);
			}
		}
		return *this;
	}

	Polinom operator*(const Polinom& other) const {
		Polinom result;
		for (const auto& monom1 : monomList) {
			for (const auto& monom2 : other.monomList) {
				try {
					result.addMonom(monom1 * monom2);
				}
				catch (const std::runtime_error& e) {
					cerr << "Error: " << e.what() << endl;
				}
			}
		}
		result.removeZeroMonoms();
		return result;
	}
};










/*
#include "polinom.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

Polinom::Polinom(const std::string& polynomialStr) {
	size_t pos = 0;
	size_t length = polynomialStr.size();

	while (pos < length) {
		while (pos < length && std::isspace(polynomialStr[pos])) {
			pos++;
		}

		if (pos >= length) break;

		size_t startPos = pos;

		if (polynomialStr[pos] == '+' || polynomialStr[pos] == '-') {
			pos++;
		}

		while (pos < length && !std::isspace(polynomialStr[pos]) && polynomialStr[pos] != '+' && polynomialStr[pos] != '-') {
			pos++;
		}

		std::string monomStr = polynomialStr.substr(startPos, pos - startPos);
		if (!monomStr.empty() && monomStr.find_first_not_of(" \t") != std::string::npos) {
			Monom monom(monomStr);
			addMonom(monom);
		}
	}

	removeZeroMonoms();
}

Polinom::Polinom(const Polinom& other) {
	for (const auto& monom : other.monomList) {
		monomList.addToEnd(monom);
	}
}

void Polinom::removeZeroMonoms() {
	size_t i = 0;
	while (i < monomList.length()) {
		if (monomList.getItem(i).coeff == 0.0) {
			monomList.eraseAt(i);
		}
		else {
			++i;
		}
	}
}

void Polinom::addMonom(const Monom& monom) {
	if (monom.coeff == 0.0) {
		return;
	}

	bool found = false;
	for (auto& existingMonom : monomList) {
		if (existingMonom.getDegreeHash() == monom.getDegreeHash()) {
			existingMonom.coeff += monom.coeff;
			found = true;
			break;
		}
	}

	if (!found) {
		monomList.addToEnd(monom);
	}
}

double Polinom::evaluate(double x, double y, double z) const {
	double result = 0.0;
	for (auto& monom : monomList) {
		result += monom.evaluate(x, y, z);
	}
	return result;
}

std::string Polinom::toString() const {
	std::string result = "";

	for (size_t i = 0; i < monomList.length(); ++i) {
		const Monom& monom = monomList.getItem(i);
		std::string monomStr = monom.toString();

		if (!monomStr.empty()) {
			if (result.empty()) {
				result = monomStr;
			}
			else {
				result += monomStr[0] == '-' ? monomStr : "+" + monomStr;
			}
		}
	}

	return result.empty() ? "0" : result;
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

std::ostream& operator<<(std::ostream& out, const Polinom& polinom) {
	out << polinom.toString();
	return out;
}

*/