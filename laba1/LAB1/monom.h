#ifndef MONOM_H
#define MONOM_H

#include <string>

using namespace std;

static const int MAX_DEGREE = 9;

class Monom 
{
private:
	double coef; // коэффициент 
	int x, y, z; // степени переменных
public:
	Monom(double coef = 0.0, int x2 = 0, int y2 = 0, int z2 = 0); //конструктор инициализатор + по умолчанию
	Monom(const string& expression); // конструктор преобразования типа
	Monom(const Monom& other); // конструктор копирования

	double getCoef() const noexcept;
	int getX() const noexcept;
	int getY() const noexcept;
	int getZ() const noexcept;

	void setCoef(double c2);
	void setX(int x2);
	void setY(int y2);
	void setZ(int z2);

	Monom& operator=(const Monom& other);
	bool operator<(const Monom& other) const;
	bool operator>(const Monom& other) const;
	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;
	Monom operator*(const Monom& other) const; // ?

	double evaluate(double x_value, double y_value, double z_value) const;
	string toString() const;
};
#endif
