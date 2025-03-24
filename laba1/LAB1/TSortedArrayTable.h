#ifndef TSORTEDARRAYTABLE_H
#define TSORTEDARRAYTABLE_H

#include "TTable.h"
#include <vector>
#include <iostream>
#include <algorithm>

template <typename TKey, typename TValue>
class TSortedArrayTable : public TTable // таблица на упорядоченном массиве
{
    struct TTableRec
    {
        TKey key;
        TValue value;
    };
    std::vector<TTableRec> data{};
public:
    TSortedArrayTable() = default;
    size_t size() const noexcept;
    TValue& operator[](size_t pos);
    void Print() const;
    void Delete(TKey key);
    TValue* Find(TKey key);
    void Insert(TKey key, TValue value);

private:
    void Sort(); // Метод для сортировки
};

size_t TSortedArrayTable::size() const noexcept
{
    return data.size();
}

TValue& TSortedArrayTable::operator[](size_t pos)
{
    if (pos >= size()) {
        throw std::out_of_range("Position out of range");
    }
    return data[pos].value;
}

void TSortedArrayTable::Print() const
{
    for (const auto& rec : data) {
        std::cout << "Key: " << rec.key << ", Value: " << rec.value << '\n';
    }
}

void TSortedArrayTable::Delete(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        data.erase(it);
    }
}

TValue* TSortedArrayTable::Find(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        return &(it->value);
    }
    return nullptr;
}

void TSortedArrayTable::Insert(TKey key, TValue value)
{
    if (Find(key) == nullptr) {
        data.emplace_back(TTableRec{ key, value });
        Sort();
    }
}

void TSortedArrayTable::Sort()
{
    std::sort(data.begin(), data.end(), [](const TTableRec& lhs, const TTableRec& rhs) {
        return lhs.key < rhs.key;
        });
}

#endif