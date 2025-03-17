#include "monom.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

Monom::Monom(double coeff, int powerX, int powerY, int powerZ) {
	if (powerX < 0 || powerY < 0 || powerZ < 0 || powerX > MAX_DEGREE || powerY > MAX_DEGREE || powerZ > MAX_DEGREE) {
		throw std::invalid_argument("Некорректные степени переменных в мономе.");
	}
	this->coeff = coeff;
	powers['x'] = powerX;
	powers['y'] = powerY;
	powers['z'] = powerZ;
}

Monom::Monom(const std::string& expr) {
	coeff = 1.0;
	powers['x'] = 0;
	powers['y'] = 0;
	powers['z'] = 0;
	std::istringstream stream(expr);
	bool negative = false;

	if (!stream.eof() && stream.peek() == '-') {
		negative = true;
		stream.ignore();
	}

	if (stream >> coeff) {
		if (negative) {
			coeff = -coeff;
		}
	}
	else {
		coeff = 1.0 * (negative ? -1 : 1);
		stream.clear();
		stream.seekg(0);
	}

	char variable;
	while (stream >> variable) {
		if (powers.find(variable) == powers.end()) {
			throw std::invalid_argument("Некорректная переменная в мономе.");
		}
		int degree = 0;
		if (stream.peek() == '^') {
			stream.ignore();
			stream >> degree;
		}
		else {
			degree = 1;
		}
		if (degree < 0 || degree > MAX_DEGREE) {
			throw std::invalid_argument("Степень переменной превышает допустимое значение.");
		}
		powers[variable] = degree;
	}
}

bool Monom::operator<(const Monom& other) const {
	return getDegreeHash() < other.getDegreeHash();
}

bool Monom::operator>(const Monom& other) const {
	return getDegreeHash() > other.getDegreeHash();
}

bool Monom::operator==(const Monom& other) const {
	return coeff == other.coeff && powers == other.powers;
}

bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}

Monom Monom::operator*(const Monom& other) const {
	int newPowerX = powers.at('x') + other.powers.at('x');
	int newPowerY = powers.at('y') + other.powers.at('y');
	int newPowerZ = powers.at('z') + other.powers.at('z');

	if (newPowerX > MAX_DEGREE || newPowerY > MAX_DEGREE || newPowerZ > MAX_DEGREE) {
		throw std::invalid_argument("Результирующий моном превышает максимально допустимую степень.");
	}

	return Monom(coeff * other.coeff, newPowerX, newPowerY, newPowerZ);
}

double Monom::evaluate(double x, double y, double z) const {
	double result = coeff;
	result *= std::pow(x, powers.at('x'));
	result *= std::pow(y, powers.at('y'));
	result *= std::pow(z, powers.at('z'));
	return result;
}

std::string Monom::toString() const {
	if (coeff == 0) {
		return "";
	}

	std::ostringstream oss;
	if (coeff == 1) {
		if (powers.at('x') == 0 && powers.at('y') == 0 && powers.at('z') == 0) {
			oss << "1";
		}
	}
	else if (coeff == -1) {
		if (powers.at('x') == 0 && powers.at('y') == 0 && powers.at('z') == 0) {
			oss << "-1";
		}
		else {
			oss << "-";
		}
	}
	else {
		oss << coeff;
	}

	if (powers.at('x') > 0) {
		oss << "x";
		if (powers.at('x') > 1) {
			oss << "^" << powers.at('x');
		}
	}
	if (powers.at('y') > 0) {
		oss << "y";
		if (powers.at('y') > 1) {
			oss << "^" << powers.at('y');
		}
	}
	if (powers.at('z') > 0) {
		oss << "z";
		if (powers.at('z') > 1) {
			oss << "^" << powers.at('z');
		}
	}

	return oss.str();
}

int Monom::getDegreeHash() const {
	const int HASH_BASE = 100;
	return (powers.at('x') * (HASH_BASE * HASH_BASE)) + (powers.at('y') * HASH_BASE) + powers.at('z');
}
