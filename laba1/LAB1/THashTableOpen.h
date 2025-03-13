#ifndef THASHTABLEOPEN_H
#define THASHTABLEOPEN_H

#include "TTable.h"
#include <vector>

template <typename TKey, typename TValue>
class THashTableOpen : public TTable // хеш-таблица с открытым перемешиванием
{
	struct Node 
	{
		TKey key;
		TValue value;
		bool isOccupied;
	};

	vector<Node> data{};
public:
	THashTableOpen() = default;
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

size_t THashTableOpen::size() const noexcept
{
	return data.size();
}

TValue& THashTableOpen::operator[](size_t pos)
{
	return data[pos].value;
}

// ...

#endif
