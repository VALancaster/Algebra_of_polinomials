#ifndef TLISTTABLE_H
#define TLISTTABLE_H

#include "TTable.h"
#include "SinglyList.h"

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
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

size_t TListTable::size() const noexcept
{
	return data.length();
}

TValue& TListTable::operator[](size_t pos)
{
	return data[pos].value;
}

// ...

#endif
