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
public:
	THashTableChain() = default;
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

// ...

#endif

