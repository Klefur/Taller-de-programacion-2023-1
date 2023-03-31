#include "AVL.h"

using namespace std;

int AVL::height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int AVL::balanceFactor(Node *node)
{
    return height(node->left) - height(node->right);
}

void AVL::updateHeight(Node *node)
{
    node->height = max(height(node->left), height(node->right)) + 1;
}

Node *AVL::rotateRight(Node *node)
{
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node *AVL::rotateLeft(Node *node)
{
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node *AVL::balance(Node *node)
{
    updateHeight(node);
    int bf = balanceFactor(node);
    if (bf == 2)
    {
        if (balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf == -2)
    {
        if (balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

Node *AVL::insert(Node *node, int key)
{
    if (node == nullptr)
    {
        return new Node(key);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else
    {
        node->right = insert(node->right, key);
    }
    return balance(node);
}

Node *AVL::findMin(Node *node)
{
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node *AVL::removeMin(Node *node)
{
    if (node->left == nullptr)
    {
        return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

Node *AVL::remove(Node *node, int key)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (key < node->key)
    {
        node->left = remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key);
    }
    else
    {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        if (right == nullptr)
        {
            return left;
        }
        Node *min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

void AVL::printInorder(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    printInorder(node->left);
    cout << node->key << " ";
    printInorder(node->right);
}
