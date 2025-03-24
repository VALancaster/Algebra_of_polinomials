#ifndef THASHTABLECHAIN_H
#define THASHTABLECHAIN_H

#include "TTable.h"
#include <vector>
#include <list> // здесь возможно заменить std::list на наш SinglyList ?

template <typename TKey, typename TValue>
class THashTableChain : public TTable // хеш-таблица с цепочками
{
    struct Node
    {
        TKey key;
        TValue value;
    };

    vector<list<Node>> data{};
    size_t bucketCount;

    size_t HashFunction(TKey key) const;

public:
    THashTableChain(size_t buckets = 10) : bucketCount(buckets)
    {
        data.resize(bucketCount);
    }
    size_t size() const noexcept;
    TValue& operator[](TKey key);
    void Print() const;
    void Delete(TKey key);
    TValue* Find(TKey key);
    void Insert(TKey key, TValue value);
};

template <typename TKey, typename TValue>
size_t THashTableChain<TKey, TValue>::HashFunction(TKey key) const
{
    return std::hash<TKey>()(key) % bucketCount;
}

template <typename TKey, typename TValue>
size_t THashTableChain<TKey, TValue>::size() const noexcept
{
    size_t count = 0;
    for (const auto& chain : data)
    {
        count += chain.size();
    }
    return count;
}

template <typename TKey, typename TValue>
TValue& THashTableChain<TKey, TValue>::operator[](TKey key)
{
    size_t index = HashFunction(key);
    for (auto& node : data[index])
    {
        if (node.key == key)
            return node.value;
    }
    throw std::out_of_range("Key not found");
}

template <typename TKey, typename TValue>
void THashTableChain<TKey, TValue>::Print() const
{
    std::cout << "Printing hash table contents:" << std::endl;
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::cout << "Bucket " << i << ": ";
        for (const auto& node : data[i])
        {
            std::cout << "(" << node.key << ": " << node.value << ") ";
        }
        std::cout << std::endl;
    }
    if (size() == 0)
    {
        std::cout << "The hash table is empty." << std::endl;
    }
}

template <typename TKey, typename TValue>
void THashTableChain<TKey, TValue>::Delete(TKey key)
{
    size_t index = HashFunction(key);
    auto& chain = data[index];

    for (auto it = chain.begin(); it != chain.end(); ++it)
    {
        if (it->key == key)
        {
            chain.erase(it);
            return;
        }
    }
}

template <typename TKey, typename TValue>
TValue* THashTableChain<TKey, TValue>::Find(TKey key)
{
    size_t index = HashFunction(key);
    for (auto& node : data[index])
    {
        if (node.key == key)
            return &node.value;
    }
    return nullptr;
}

template <typename TKey, typename TValue>
void THashTableChain<TKey, TValue>::Insert(TKey key, TValue value)
{
    if (Find(key))
        return;
    size_t index = HashFunction(key);
    data[index].emplace_back(Node{ key, value });
}

#endif
