#ifndef TSORTEDARRAYTABLE_H
#define TSORTEDARRAYTABLE_H

#include "TTable.h"
#include <vector>

template <typename TKey, typename TValue>
class TSortedArrayTable : public TTable // таблица на упорядоченном массиве
{
	struct TTableRec
	{
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
public:
	TSortedArrayTable() = default;
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

size_t TSortedArrayTable::size() const noexcept
{
	return data.size();
}

TValue& TSortedArrayTable::operator[](size_t pos)
{
	return data[pos].value;
}

// ...

#endif
