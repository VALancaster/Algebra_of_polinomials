#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"
#include <stdexcept>

template <typename TKey, typename TValue>
class TTreeTable : public TTable // Таблица с использованием AVL-дерева.
{
    struct TTableRec
    {
        TKey key;
        TValue value;
    };

    struct TreeNode // Узел дерева
    {
        TTableRec data;
        TreeNode* pLeft = nullptr;
        TreeNode* pRight = nullptr;
        int height = 1; // Высота узла
    };

    TreeNode* pRoot = nullptr;
    size_t treeSize = 0;

    int Height(TreeNode* pNode)
    {
        return (pNode == nullptr) ? 0 : pNode->height;
    }

    int BalanceFactor(TreeNode* pNode)
    {
        return (pNode == nullptr) ? 0 : Height(pNode->pLeft) - Height(pNode->pRight);
    }

    void UpdateHeight(TreeNode* pNode)
    {
        if (pNode != nullptr) {
            pNode->height = 1 + std::max(Height(pNode->pLeft), Height(pNode->pRight));
        }
    }

    TreeNode* RotateRight(TreeNode* pNode)
    {
        TreeNode* newRoot = pNode->pLeft;
        pNode->pLeft = newRoot->pRight;
        newRoot->pRight = pNode;

        UpdateHeight(pNode);
        UpdateHeight(newRoot);

        return newRoot;
    }

    TreeNode* RotateLeft(TreeNode* pNode)
    {
        TreeNode* newRoot = pNode->pRight;
        pNode->pRight = newRoot->pLeft;
        newRoot->pLeft = pNode;

        UpdateHeight(pNode);
        UpdateHeight(newRoot);

        return newRoot;
    }

    TreeNode* Balance(TreeNode* pNode)
    {
        UpdateHeight(pNode);

        int bf = BalanceFactor(pNode);

        if (bf > 1) // Левое поддерево выше
        {
            if (BalanceFactor(pNode->pLeft) < 0) {
                pNode->pLeft = RotateLeft(pNode->pLeft);
            }
            return RotateRight(pNode);
        }
        if (bf < -1) // Правое поддерево выше
        {
            if (BalanceFactor(pNode->pRight) > 0) {
                pNode->pRight = RotateRight(pNode->pRight);
            }
            return RotateLeft(pNode);
        }
        return pNode;
    }

    TreeNode* InsertNode(TreeNode* pNode, TKey key, TValue value)
    {
        if (pNode == nullptr) {
            treeSize++;
            return new TreeNode{ {key, value}, nullptr, nullptr, 1 };
        }

        if (key < pNode->data.key) {
            pNode->pLeft = InsertNode(pNode->pLeft, key, value);
        }
        else if (key > pNode->data.key) {
            pNode->pRight = InsertNode(pNode->pRight, key, value);
        }
        else {
            pNode->data.value = value; // Обновление значения при совпадении ключа
            return pNode;
        }

        return Balance(pNode);
    }

    TreeNode* DeleteNode(TreeNode* pNode, TKey key)
    {
        if (pNode == nullptr) {
            return nullptr;
        }

        if (key < pNode->data.key) {
            pNode->pLeft = DeleteNode(pNode->pLeft, key);
        }
        else if (key > pNode->data.key) {
            pNode->pRight = DeleteNode(pNode->pRight, key);
        }
        else {
            if (pNode->pLeft == nullptr || pNode->pRight == nullptr) {
                TreeNode* tmp = pNode->pLeft ? pNode->pLeft : pNode->pRight;
                delete pNode;
                treeSize--;
                return tmp;
            }

            TreeNode* minNode = FindMin(pNode->pRight);
            pNode->data = minNode->data;
            pNode->pRight = DeleteNode(pNode->pRight, minNode->data.key);
        }
        return Balance(pNode);
    }

    TreeNode* FindNode(TKey key, TreeNode* pNode)
    {
        if (pNode == nullptr)
            return nullptr;
        if (key < pNode->data.key)
            return FindNode(key, pNode->pLeft);
        if (key > pNode->data.key)
            return FindNode(key, pNode->pRight);
        return pNode;
    }

    TreeNode* FindMin(TreeNode* pNode)
    {
        while (pNode->pLeft != nullptr)
            pNode = pNode->pLeft;
        return pNode;
    }

    void Print(TreeNode* p)
    {
        if (p == nullptr)
            return;
        Print(p->pLeft);
        std::cout << p->data.key << "-" << p->data.value << std::endl;
        Print(p->pRight);
    }

public:
    TTreeTable() = default;

    ~TTreeTable()
    {
        while (pRoot != nullptr)
            pRoot = DeleteNode(pRoot, pRoot->data.key);
    }

    size_t size() const noexcept
    {
        return treeSize;
    }

    TValue& operator[](size_t pos)
    {
        throw std::out_of_range("Operator[] not supported for tree traversal");
    }

    void Print()
    {
        std::cout << "Table\n";
        Print(pRoot);
    }

    void Delete(TKey key)
    {
        pRoot = DeleteNode(pRoot, key);
    }

    TValue* Find(TKey key)
    {
        TreeNode* pNode = FindNode(key, pRoot);
        if (pNode == nullptr)
            return nullptr;
        return &pNode->data.value;
    }

    void Insert(TKey key, TValue value)
    {
        pRoot = InsertNode(pRoot, key, value);
    }
};

#endif