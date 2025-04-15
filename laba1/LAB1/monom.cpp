#include "monom.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

Monom::Monom(double coef2, int x2, int y2, int z2) : coef(coef2), x(x2), y(y2), z(z2) {}

Monom::Monom(const string& expression)
{
	coef = 1.0;
	x = 0; y = 0; z = 0;
	istringstream stream(expression);

	// Обработка знака
	char sign = '+';
	if (stream.peek() == '+' || stream.peek() == '-') 
	{
		sign = stream.get();
	}

	/*
	// Попытка чтения коэффициента
	if (!(stream >> coef))
	{
		coef = 1.0;  // Если коэффициент не указан, по умолчанию 1
		stream.clear();
	}
	*/
	stream >> std::ws;

	double parsedCoef;

	if (stream >> parsedCoef)
	{
		coef = parsedCoef;
	}
	else
	{
		coef = 1.0;
		stream.clear();
	}

	if (sign == '-')
	{
		coef = -coef;
	}

	// Чтение переменных и степеней
	char var;
	while (stream >> var) 
	{
		if (var != 'x' && var != 'y' && var != 'z') 
		{
			throw invalid_argument("Only variables 'x', 'y', 'z' are allowed");
		}

		int degree = 1;
		if (stream.peek() == '^') 
		{
			stream.ignore();
			if (!(stream >> degree)) 
			{
				throw invalid_argument("Invalid degree format");
			}
		}

		if (var == 'x') 
		{
			x = degree;
		}
		else if (var == 'y')
		{
			y = degree;
		}
		else if (var == 'z')
		{
			z = degree;
		}
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
