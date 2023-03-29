#include "State.h"

class Node
{
public:
    int key;
    int height;
    Node *left;
    Node *right;

    Node(int key);
    ~Node();
};
