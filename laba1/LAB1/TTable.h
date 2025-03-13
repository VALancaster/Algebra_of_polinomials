#ifndef TTABLE_H
#define TTABLE_H

#include "Polinom.h"
#include <string>

class TTable() // абстрактный класс Таблица
{
public:
	virtual void Insert(const std::string& name, const Polinom & pol) = 0;
	virtual void Delete(const std::string& name) = 0;
	virtual Polinom Find(const std::string& name) const = 0;
	virtual void PrintTable() const = 0;
};


#endif