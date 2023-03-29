#include "Node.h"

using namespace std;

Node::Node(int key)
{
    this->key = key;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}
