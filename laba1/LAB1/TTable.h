#ifndef TTABLE_H
#define TTABLE_H

#include "Polinom.h"
#include <string>

using namespace std;

class TTable // абстрактный класс Таблица
{
public:
	virtual ~TTable() = default;
	virtual string GetName() const = 0;
	virtual void Insert(const string& name, const Polinom& pol) = 0;
	virtual void Delete(const string& name) = 0;
	virtual Polinom Find(const string& name) const = 0;
	virtual void Print() const = 0;
};


#endif