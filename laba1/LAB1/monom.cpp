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

Monom Monom::operator*(const Monom& other) const 
{
	int new_x = x + other.x;
	int new_y = y + other.y;
	int new_z = z + other.z;
	if (new_x > MAX_DEGREE || new_y > MAX_DEGREE || new_z > MAX_DEGREE) 
		throw runtime_error("The degrees of the variables must be less than 10");
	return Monom(coef * other.coef, new_x, new_y, new_z);
}

double Monom::evaluate(double x_value, double y_value, double z_value) const 
{
	double result = coef;
	result *= pow(x_value, x);
	result *= pow(y_value, y);
	result *= pow(z_value, z);
	return result;
}

string Monom::toString() const 
{
	if (coef == 0) 
		return "";
	ostringstream oss; // cоздается объект - поток вывода
	if (coef == 1) 
	{
		if (x == 0 && y == 0 && z == 0)
			oss << "1";
	}
	else if (coef == -1) 
	{
		if (x == 0 && y == 0 && z == 0) 
			oss << "-1";
		else 
			oss << "-";
	}
	else 
		oss << coef;
	if (x > 0)
	{
		oss << "x";
		if (x > 1) 
			oss << "^" << x;
	}
	if (y > 0) 
	{
		oss << "y";
		if (y > 1) 
			oss << "^" << y;
	}
	if (z > 0) 
	{
		oss << "z";
		if (z > 1) 
			oss << "^" << z;
	}
	return oss.str(); // возвращает строку из потока вывода
}
