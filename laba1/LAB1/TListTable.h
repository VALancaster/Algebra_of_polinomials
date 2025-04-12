#ifndef TLISTTABLE_H
#define TLISTTABLE_H

#include "TTable.h"
#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template <typename TKey, typename TValue>
class TListTable : public TTable<TKey, TValue> // таблица на односвязном списке
{
    struct TTableRec
    {
        TKey key;
        TValue value;
    };
    list<TTableRec> data;
public:
    TListTable() = default;

	string GetName() const override
	{
		return "List Table";
	}

    size_t size() const noexcept override
    {
        return data.size();
    }

    void Insert(const TKey& key, const TValue& value) override
    {
        for (auto& node : data)
        {
            if (node.key == key)
            {
                node.value = value;
                return;
            }
        }
        data.push_back(TTableRec{ key, value });
    }

    void Delete(const TKey& key) override
    {
		data.remove_if([&key](const TTableRec& node) 
        {
            return node.key == key; 
        });
    }

	TValue* Find(const TKey& key) override
    {
        for (auto& node : data) 
        {
            if (node.key == key) 
            {
                return &node.value;
            }
        }
        return nullptr; 
    }

    void Print() const
    {
        cout << "List Table Contents: " << endl;
        for (const auto& node : data) 
        {
            cout << "Key: " << node.key << ", Value: " << node.value << endl;
        }
    }

    TValue& operator[](const TKey& key)
    {
        for (auto& node : data)
        {
            if (node.key == key)
            {
                return node.value;
            }
        }
        throw out_of_range("Key not found");
    }
};

#endif