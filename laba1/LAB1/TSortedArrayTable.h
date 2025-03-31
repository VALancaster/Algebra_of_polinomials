#ifndef TSORTEDARRAYTABLE_H
#define TSORTEDARRAYTABLE_H

#include "TTable.h"
#include <vector>
#include <iostream>

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
    size_t FindInsertionIndex(const TKey& key); // Метод для поиска индекса вставки
};

template <typename TKey, typename TValue>
size_t TSortedArrayTable<TKey, TValue>::size() const noexcept
{
    return data.size();
}

template <typename TKey, typename TValue>
TValue& TSortedArrayTable<TKey, TValue>::operator[](size_t pos)
{
    if (pos >= size()) {
        throw std::out_of_range("Position out of range");
    }
    return data[pos].value;
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Print() const
{
    for (const auto& rec : data) {
        std::cout << "Key: " << rec.key << ", Value: " << rec.value << '\n';
    }
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Delete(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        data.erase(it);
    }
}

template <typename TKey, typename TValue>
TValue* TSortedArrayTable<TKey, TValue>::Find(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        return &(it->value);
    }
    return nullptr;
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Insert(TKey key, TValue value)
{
    if (Find(key) == nullptr) {
        size_t index = FindInsertionIndex(key);
        data.insert(data.begin() + index, TTableRec{ key, value });
    }
}

template <typename TKey, typename TValue>
size_t TSortedArrayTable<TKey, TValue>::FindInsertionIndex(const TKey& key)
{
    size_t left = 0;
    size_t right = data.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (data[mid].key < key) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;
}

#endif

/*
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

template <typename TKey, typename TValue>
size_t TSortedArrayTable<TKey, TValue>::size() const noexcept
{
    return data.size();
}

template <typename TKey, typename TValue>
TValue& TSortedArrayTable<TKey, TValue>::operator[](size_t pos)
{
    if (pos >= size()) {
        throw std::out_of_range("Position out of range");
    }
    return data[pos].value;
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Print() const
{
    for (const auto& rec : data) {
        std::cout << "Key: " << rec.key << ", Value: " << rec.value << '\n';
    }
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Delete(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        data.erase(it);
    }
}

template <typename TKey, typename TValue>
TValue* TSortedArrayTable<TKey, TValue>::Find(TKey key)
{
    auto it = std::find_if(data.begin(), data.end(), [&key](const TTableRec& rec) {
        return rec.key == key;
        });
    if (it != data.end()) {
        return &(it->value);
    }
    return nullptr;
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Insert(TKey key, TValue value)
{
    if (Find(key) == nullptr) {
        data.emplace_back(TTableRec{ key, value });
        Sort();
    }
}

template <typename TKey, typename TValue>
void TSortedArrayTable<TKey, TValue>::Sort()
{
    std::sort(data.begin(), data.end(), [](const TTableRec& lhs, const TTableRec& rhs) {
        return lhs.key < rhs.key;
        });
}

#endif
*/