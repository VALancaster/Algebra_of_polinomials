#ifndef TARRAYTABLE_H
#define TARRAYTABLE_H

#include "TTable.h"
#include <vector>
#include <iostream>

using namespace std;

template <typename TKey, typename TValue>
class TArrayTable : public TTable<TKey, TValue> // таблица на массиве
{
	struct TTableRec
	{
		TKey key;
		TValue value;
	};
	vector<TTableRec> data{};
public:
	TArrayTable() = default;

	string GetName() const override
	{
		return "Array Table";
	}

	size_t size() const noexcept override
	{
		return data.size();
	}

	void Print() const override
	{
		cout << "Array Table Contents: " << endl;
		for (const auto& record : data) // Перебираем все записи в таблице
		{
			cout << "Key: " << record.key << ", Value: " << record.value << endl;
		}
	}

	void Delete(const TKey& key) override
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			if (it->key == key)
			{
				data.erase(it);
				return;
			}
		}
	}

	TValue* Find(const TKey& key) override
	{
		for (auto& val : data)
		{
			if (val.key == key)
				return &val.value;
		}
		return nullptr;
	}

	void Insert(const TKey& key, const TValue& value) override
	{
		if (Find(key))
			return;
		data.push_back({ key, value });
	}

	TValue& operator[](size_t pos)
	{
		return data[pos].value;
	}
};

#endif