#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"

template <typename TKey, typename TValue>
class TTreeTable : public TTable // таблица на дереве (AVL или чернокрасном)
{
	struct TTableRec
	{
		TKey key;
		TValue value;
	};
	struct TreeNode // узел дерева
	{
		TTableRec data;
		TreeNode* pLeft;
		TreeNode* pRight;
	};
	
	TreeNode* pRoot;

	void Print(TreeNode* p)
	{
		if (p == nullptr)
			return;
		Print(p->pLeft);
		cout << p->data.key << "-" << p->data.value << std::endl;
		Print(p->pRight);
	}

	TreeNode* FindNode(TKey key, TreeNode* pNode)
	{
		if (pNode == nulllptr)
			return nullptr;
		if (key < pNode->data.key)
			pNode = FindNode(key, pNode->pLeft);
		if (key > pNode->data.key)
			pNode = FindNode(key, pNode->pRight);
		return pNode;
	}
public:
	TTreeTable() = default;
	~TTreeTable();
	size_t size() const noexcept;
	TValue& operator[](size_t pos);
	void Print()
	{
		cout << "Table\n";
		Print(pRoot);
	}
	void Delete(TKey key);
	TValue* Find(TKey key)
	{
		TreeNode* pNode = FindNode(key, pRoot);
		if (pNode == nullptr)
			return nullptr;
		return &pNode->data.value;
	}
	void Insert(TKey key, TValue value);
};

// ...

#endif
