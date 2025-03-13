#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"

template <typename TKey, typename TValue>
class TTreeTable : public TTable // таблица на дереве (AVL или чернокрасном)
{
	struct TreeNode // узел дерева
	{
		TKey key;
		TValue value;
		Node* left;
		Node* right;
	};
	
	Node* root;
public:
	TTreeTable() = default;
	~TTreeTable();
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Delete(TKey key);
	TValue* Find(TKey key);
	void Insert(TKey key, TValue value);
};

// ...

#endif
