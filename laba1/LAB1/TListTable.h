#ifndef TLISTTABLE_H
#define TLISTTABLE_H

#include "TTable.h"
#include "SinglyList.h"
#include <stdexcept>

template <typename TKey, typename TValue>
class TListTable : public TTable // таблица на односвязном списке
{
    struct TTableRec
    {
        TKey key;
        TValue value;
    };
    SinglyList<TTableRec> data;
public:
    TListTable() = default;

    size_t size() const noexcept
    {
        return data.length();
    }

    TValue& operator[](size_t pos)
    {
        if (pos >= size()) {
            throw std::out_of_range("Index out of range");
        }

        auto node = data.begin();
        for (size_t i = 0; i < pos; ++i) {
            ++node;
        }
        return node->value;
    }

    void Print() const
    {
        for (auto it = data.begin(); it != data.end(); ++it) {
            std::cout << "Key: " << it->key << ", Value: " << it->value << std::endl;
        }
    }

    string GetName() const override
    {
        return "List Table";
    }

    void Delete(TKey key)
    {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->key == key) {
                data.erase(it);
                return;
            }
        }
    }

    TValue* Find(TKey key)
    {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->key == key) {
                return &it->value;
            }
        }
        return nullptr; // Если ключ не найден
    }

    void Insert(TKey key, TValue value)
    {
        if (Find(key)) 
            return;
        data.push_back(TTableRec{ key, value });
    }
};

#endif