#ifndef THASHTABLEOPEN_H
#define THASHTABLEOPEN_H

#include "TTable.h"
#include <vector>
#include <iostream>
#include <optional> // Для std::nullopt

template <typename TKey, typename TValue>
class THashTableOpen : public TTable // хеш-таблица с открытым перемешиванием
{
    struct Node
    {
        TKey key;
        TValue value;
        bool isOccupied = false;
        bool isDeleted = false; // Флаг для пометки удалённых ячеек
    };

    std::vector<Node> data;
    size_t bucketCount;

    size_t HashFunction(TKey key) const;

public:
    THashTableOpen(size_t buckets = 10) : bucketCount(buckets)
    {
        data.resize(bucketCount);
    }

    size_t size() const noexcept;
    TValue& operator[](TKey key);
    void Print() const;
    string GetName() const override;
    void Delete(TKey key);
    TValue* Find(TKey key);
    void Insert(TKey key, TValue value);
};

template <typename TKey, typename TValue>
size_t THashTableOpen<TKey, TValue>::HashFunction(TKey key) const
{
    return std::hash<TKey>()(key) % bucketCount;
}

template <typename TKey, typename TValue>
size_t THashTableOpen<TKey, TValue>::size() const noexcept
{
    size_t count = 0;
    for (const auto& node : data)
    {
        if (node.isOccupied && !node.isDeleted)
        {
            count++;
        }
    }
    return count;
}

template <typename TKey, typename TValue>
TValue& THashTableOpen<TKey, TValue>::operator[](TKey key)
{
    size_t index = HashFunction(key);
    size_t start_index = index;

    while (data[index].isOccupied)
    {
        if (data[index].key == key && !data[index].isDeleted)
            return data[index].value;

        index = (index + 1) % bucketCount;
        if (index == start_index)
            throw std::out_of_range("Key not found");
    }

    throw std::out_of_range("Key not found");
}

template <typename TKey, typename TValue>
void THashTableOpen<TKey, TValue>::Print() const
{
    std::cout << "Hash table contents:" << std::endl;
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (data[i].isOccupied && !data[i].isDeleted)
        {
            std::cout << "Index " << i << ": (" << data[i].key << ": " << data[i].value << ")" << std::endl;
        }
    }
}

template <typename TKey, typename TValue>
string GetName() const override
{
    return "Hash Table Open";
}

template <typename TKey, typename TValue>
void THashTableOpen<TKey, TValue>::Delete(TKey key)
{
    size_t index = HashFunction(key);
    size_t start_index = index;

    while (data[index].isOccupied)
    {
        if (data[index].key == key && !data[index].isDeleted)
        {
            data[index].isDeleted = true;
            return;
        }

        index = (index + 1) % bucketCount;
        if (index == start_index)
            return;
    }
}

template <typename TKey, typename TValue>
TValue* THashTableOpen<TKey, TValue>::Find(TKey key)
{
    size_t index = HashFunction(key);
    size_t start_index = index;

    while (data[index].isOccupied)
    {
        if (data[index].key == key && !data[index].isDeleted)
            return &data[index].value;

        index = (index + 1) % bucketCount;
        if (index == start_index)
            return nullptr;
    }
    return nullptr;
}

template <typename TKey, typename TValue>
void THashTableOpen<TKey, TValue>::Insert(TKey key, TValue value)
{
    size_t index = HashFunction(key);
    size_t start_index = index;
    bool foundDeleted = false;
    size_t deletedIndex = 0;

    while (data[index].isOccupied && !data[index].isDeleted)
    {
        if (data[index].key == key)
        {
            data[index].value = value;
            return;
        }

        index = (index + 1) % bucketCount;
        if (index == start_index)
            return;
    }

    if (!data[index].isOccupied)
    {
        data[index] = { key, value, true, false };
    }
    else
    {
        data[index].key = key;
        data[index].value = value;
        data[index].isOccupied = true;
        data[index].isDeleted = false;
    }
}

#endif