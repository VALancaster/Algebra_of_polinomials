
#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"
#include <algorithm>
#include <iostream>

template <typename TKey, typename TValue>
class TTreeTable : public TTable<TKey, TValue> 
{
    struct Node {
        TKey key;
        TValue value;
        Node* left = nullptr;
        Node* right = nullptr;
        int height = 1;
    };

    Node* root = nullptr;
    size_t count = 0;

    int Height(Node* node) const 
    {
        return node ? node->height : 0;
    }

    int BalanceFactor(Node* node) const 
    {
        return Height(node->left) - Height(node->right);
    }

    void UpdateHeight(Node* node) 
    {
        node->height = 1 + max(Height(node->left), Height(node->right));
    }

    Node* RotateRight(Node* y) 
    {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        UpdateHeight(y);
        UpdateHeight(x);
        return x;
    }

    Node* RotateLeft(Node* x) 
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        UpdateHeight(x);
        UpdateHeight(y);
        return y;
    }

    Node* Balance(Node* node) 
    {
        UpdateHeight(node);
        int bf = BalanceFactor(node);

        if (bf > 1) {
            if (BalanceFactor(node->left) < 0) {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        }
        if (bf < -1) {
            if (BalanceFactor(node->right) > 0) {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        }
        return node;
    }

    Node* Insert(Node* node, const TKey& key, const TValue& value) 
    {
        if (!node) {
            count++;
            return new Node{ key, value };
        }

        if (key < node->key) {
            node->left = Insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = Insert(node->right, key, value);
        }
        else {
            node->value = value;
            return node;
        }

        return Balance(node);
    }

    Node* FindMin(Node* node) const 
    {
        while (node->left) node = node->left;
        return node;
    }

    Node* Remove(Node* node, const TKey& key) 
    {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = Remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = Remove(node->right, key);
        }
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
                count--;
            }
            else {
                Node* minRight = FindMin(node->right);
                node->key = minRight->key;
                node->value = minRight->value;
                node->right = Remove(node->right, minRight->key);
            }
        }

        if (!node) return nullptr;
        return Balance(node);
    }

    Node* FindNode(Node* node, const TKey& key) const 
    {
        if (!node) return nullptr;
        if (key < node->key) return FindNode(node->left, key);
        if (key > node->key) return FindNode(node->right, key);
        return node;
    }

    void Print(Node* node) const 
    {
        if (!node) 
            return;
        Print(node->left);
        cout << "Key: " << node->key << ", Value: " << node->value << endl;
        Print(node->right);
    }

public:
    ~TTreeTable() 
    {
        while (root) 
        {
            root = Remove(root, root->key);
        }
    }

    std::string GetName() const override 
    {
        return "AVL Tree Table";
    }

    size_t size() const noexcept override 
    {
        return count;
    }

    void Insert(const TKey& key, const TValue& value) override 
    {
        root = Insert(root, key, value);
    }

    void Delete(const TKey& key) override 
    {
        root = Remove(root, key);
    }

    TValue* Find(const TKey& key) override 
    {
        Node* node = FindNode(root, key);
        return node ? &node->value : nullptr;
    }

    void Print() const override 
    {
        std::cout << "AVL Tree Table Contents: " << endl;
        Print(root);
    }

    TValue& operator[](const TKey& key) 
    {
        Node* node = FindNode(root, key);
        if (!node) 
        {
            throw out_of_range("Key not found");
        }
        return node->data.value;
    }
};

#endif

/*
#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"
#include <stdexcept>

template <typename TKey, typename TValue>
class TTreeTable : public TTable<TKey, TValue> // Таблица с использованием AVL-дерева.
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
        else 
        {
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

    string GetName() const override
    {
        return "Tree Table";
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
*/

