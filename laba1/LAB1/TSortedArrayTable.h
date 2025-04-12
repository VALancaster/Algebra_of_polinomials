#ifndef TSORTEDARRAYTABLE_H
#define TSORTEDARRAYTABLE_H

#include "TTable.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename TKey, typename TValue>
class TSortedArrayTable : public TTable<TKey, TValue> // таблица на упорядоченном массиве
{
    struct TTableRec
    {
        TKey key;
        TValue value;

        bool operator<(const TTableRec& other) const
        {
            return key < other.key;
        }
    };
    vector<TTableRec> data{};

    size_t FindInsertionPos(const TKey& key) const // Бинарный поиск индекса для вставки/поиска
    {
        size_t left = 0;
        size_t right = data.size();

        while (left < right) 
        {
            size_t mid = left + (right - left) / 2;
            if (data[mid].key < key) 
            {
                left = mid + 1;
            }
            else 
            {
                right = mid;
            }
        }
        return left;
    }
public:
    TSortedArrayTable() = default;

    string GetName() const override
    {
		return "Sorted Array Table";
    }

	size_t size() const noexcept override
    {
        return data.size();
    }

    void Insert(const TKey& key, const TValue& value) override
    {
		size_t pos = FindInsertionPos(key);
        if (pos < data.size() && data[pos].key == key)
        {
            data[pos].value = value; // обновление существующего
        }
        else
        {
			data.insert(data.begin() + pos, { key, value }); // вставка нового
        }
    }

    void Delete(const TKey& key) override
    {
		size_t pos = FindInsertionPos(key);
		if (pos < data.size() && data[pos].key == key)
		{
			data.erase(data.begin() + pos); 
		}
    }

    TValue* Find(const TKey& key) override
    {
        size_t pos = FindInsertionPos(key);
        if (pos < data.size() && data[pos].key == key)
        {
            return &data[pos].value;
        }
        return nullptr;
    }

    void Print() const override
    {
        cout << "Sorted Array Table Contents: " << endl;
        for (const auto& record : data) // Перебираем все записи в таблице
        {
            cout << "Key: " << record.key << ", Value: " << record.value << endl;
        }
    }

    TValue& operator[](const TKey& key) 
    {
        size_t pos = FindInsertionPos(key);
        if (pos >= data.size() || data[pos].key != key)
        {
			throw out_of_range("Key not found");
        }
        return data[pos].value;
    }
};

#endif
