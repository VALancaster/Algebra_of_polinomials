#ifndef TTREETABLE_H
#define TTREETABLE_H

#include "TTable.h"
#include <algorithm>
#include <iostream>

template <typename TKey, typename TValue>
class TTreeTable : public TTable<TKey, TValue> 
{
    struct Node 
    {
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
        Node* x = y->left; // Запоминаем левый потомок (новый корень)
        y->left = x->right; // Перемещаем правое поддерево x на место левого поддерева y
        x->right = y; // Старый корень y становится правым потомком x
        UpdateHeight(y); 
        UpdateHeight(x);
        return x; // Возвращаем новый корень поддерева
    }

    Node* RotateLeft(Node* x) 
    {
        Node* y = x->right; // Запоминаем правый потомок (новый корень)
        x->right = y->left; // Перемещаем левое поддерево y на место правого поддерева x
        y->left = x; // Старый корень x становится левым потомком y
        UpdateHeight(x);
        UpdateHeight(y);
        return y; // Возвращаем новый корень поддерева
    }

    Node* Balance(Node* node) 
    {
        UpdateHeight(node); // Обновляем высоту текущего узла
        int bf = BalanceFactor(node); // баланс-фактор

        if (bf > 1) // левый перевес
        {
            if (BalanceFactor(node->left) < 0) // перевес в левое-правое поддерево
            {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node); // перевес в левое-левое поддерево
        }
        if (bf < -1) // правый перевес
        {
            if (BalanceFactor(node->right) > 0) // перевес в правое-левое поддерево
            {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node); // перевес в правое-правое поддерево
        }
        return node; // балансировка не требуется
    }

    Node* Insert(Node* node, const TKey& key, const TValue& value) 
    {
        if (!node) 
        {
            count++;
            return new Node{ key, value };
        }
        if (key < node->key) 
        {
            node->left = Insert(node->left, key, value);
        }
        else if (key > node->key) 
        {
            node->right = Insert(node->right, key, value);
        }
        else 
        {
            node->value = value;
            return node;
        }
        return Balance(node);
    }

    Node* FindMin(Node* node) const 
    {
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node* Remove(Node* node, const TKey& key) 
    {
        if (!node)
        {
            return nullptr;
        }
        if (key < node->key) 
        {
            node->left = Remove(node->left, key);
        }
        else if (key > node->key) 
        {
            node->right = Remove(node->right, key);
        }
        else 
        {
            if (!node->left || !node->right) // лист
            {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) 
                {
                    temp = node;
                    node = nullptr;
                }
                else 
                {
                    *node = *temp;
                }
                delete temp;
                count--;
            }
            else 
            {
                Node* minRight = FindMin(node->right);
                node->key = minRight->key;
                node->value = minRight->value;
                node->right = Remove(node->right, minRight->key);
            }
        }
        if (!node)
        {
            return nullptr;
        }
        return Balance(node);
    }

    Node* FindNode(Node* node, const TKey& key) const 
    {
        if (!node)
        {
            return nullptr;
        }
        if (key < node->key)
        {
            return FindNode(node->left, key);
        }
        if (key > node->key)
        {
            return FindNode(node->right, key);
        }
        return node;
    }

    void Print(Node* node) const 
    {
        if (!node)
        {
            return;
        }
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
