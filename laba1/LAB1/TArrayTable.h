#ifndef TARRAYTABLE_H
#define TARRAYTABLE_H

#include "TTable.h"
#include <vector>

template <typename TKey, typename TValue>
class TArrayTable : public TTable // таблица на массиве
{
	struct TTableRec
	{
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
public:
	TArryTable() = default;
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

size_t TArrayTable::size() const noexcept
{
	return data.size();
}

TValue& TArrayTable::operator[](size_t pos)
{
	return data[pos].value;
}

void TArrayTable::Delete(TKey key)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i].key == key)
		{
			data[i] = data[data.size() - 1];
			data.pop_back();
			return;
		}
	}
}

TValue* TArrayTable::Find(TKey key)
{
	for (auto& val : data)
	{
		if (val.key == key)
			return &val.value;
	}
	return nullptr;
}

void TArrayTable::Insert(TKey key, TValue value)
{
	if (Find(key))
		return;
	data.push_back({ key, value });
}

#endif