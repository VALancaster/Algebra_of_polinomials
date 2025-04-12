#ifndef TTABLE_H
#define TTABLE_H

#include "Polinom.h"
#include <string>

using namespace std;

template<typename TKey = string, typename TValue = Polinom>
class TTable // абстрактный класс Таблица
{
public:
	virtual ~TTable() = default;
	virtual string GetName() const = 0;
	virtual size_t size() const noexcept = 0;
	virtual void Insert(const TKey& key, const TValue& value) = 0;
	virtual void Delete(const TKey& key) = 0;
	virtual TValue* Find(const TKey& key) = 0; 
	virtual void Print() const = 0;
};

#endif