#include <iostream>
#include "Node.h"

class AVL
{
public:
    Node *root;

    int height(Node *node);
    int balanceFactor(Node *node);
    void updateHeight(Node *node);
    Node *rotateRight(Node *node);
    Node *rotateLeft(Node *node);
    Node *balance(Node *node);
    Node *insert(Node *node, int key);
    Node *findMin(Node *node);
    Node *removeMin(Node *node);
    Node *remove(Node *node, int key);
    void printInorder(Node *node);

    AVL() {}
};