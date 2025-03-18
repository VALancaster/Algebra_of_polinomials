#include "monom.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

Monom::Monom(double coef = 0.0, int x2 = 0, int y2 = 0, int z2 = 0) 
{
	if (x2 < 0 || y2 < 0 || z2 < 0 || x2 > MAX_DEGREE || y2 > MAX_DEGREE || z2 > MAX_DEGREE)
		throw invalid_argument("The degrees of the variables must be non-negative and less than 10");
}

Monom::Monom(const string& expression) 
{
	coef = 1.0;
	x = 0;
	y = 0;
	z = 0;
	istringstream stream(expression); // создается объект - потом ввода
	bool negative = false; // знак монома
	if (!stream.eof() && stream.peek() == '-') // stream.peek() - возвращает следующий символ из потока, не удаляя его из самого потока
	{
		negative = true;
		stream.ignore(); // пропуск символа в потоке
	}
	if (stream >> coef) // попытка извлечь коэффициент из потока
	{
		if (negative) 
			coef = -coef;
	}
	else 
	{
		coef = 1.0 * (negative ? -1 : 1);
		stream.clear(); // cброс флага состояния потока (ошибки fаilbit)
		stream.seekg(0); // возврат указателя на начало потока для повторного чтения
	}
	char variable;
	while (stream >> variable) 
	{
		if (variable != 'x' || variable != 'y' || variable != 'z')
			throw invalid_argument("Only variables 'x', 'y', 'z' are allowed");
		int degree = 0;
		if (stream.peek() == '^') 
		{
			stream.ignore();
			stream >> degree;
		}
		else 
			degree = 1;
		if (degree < 0 || degree > MAX_DEGREE) 
			throw invalid_argument("The degrees of the variables must be non-negative and less than 10");
		if (variable == 'x')
			x = degree;
		else if (variable == 'y')
			y = degree;
		else
			z = degree;
	}
}

Monom::Monom(const Monom& other) : coef(other.coef), x(other.x), y(other.y), z(other.z) {}

double Monom::getCoef() const noexcept
{
	return coef;
}

int Monom::getX() const noexcept
{
	return x;
}

int Monom::getY() const noexcept
{
	return y;
}

int Monom::getZ() const noexcept
{
	return z;
}

void Monom::setCoef(double c2)
{
	coef = c2;
}

void Monom::setX(int x2)
{
	x = x2;
}

void Monom::setY(int y2)
{
	y = y2;
}

void Monom::setZ(int z2)
{
	z = z2;
}

Monom& Monom::operator=(const Monom& other)
{
	if (this != &other)
	{
		coef = other.coef;
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return  *this;
}

bool Monom::operator<(const Monom& other) const 
{
	if (x != other.x)
		return x < other.x;
	if (y != other.y)
		return y < other.y;
	return z < other.z;
}

bool Monom::operator>(const Monom& other) const
{
	if (x != other.x)
		return x > other.x;
	if (y != other.y)
		return y > other.y;
	return z > other.z;
}

bool Monom::operator==(const Monom& other) const 
{
	return x == other.x && y == other.y && z == other.z;
}

bool Monom::operator!=(const Monom& other) const 
{
	return !(*this == other);
}

Monom Monom::operator*(const Monom& other) const {
	int newPowerX = powers.at('x') + other.powers.at('x');
	int newPowerY = powers.at('y') + other.powers.at('y');
	int newPowerZ = powers.at('z') + other.powers.at('z');

	if (newPowerX > MAX_DEGREE || newPowerY > MAX_DEGREE || newPowerZ > MAX_DEGREE) {
		throw std::invalid_argument("Ðåçóëüòèðóþùèé ìîíîì ïðåâûøàåò ìàêñèìàëüíî äîïóñòèìóþ ñòåïåíü.");
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
