#ifndef _NODE
#define _NODE

class Node {
#define NUMBER 0
#define OPERATOR 1
#define VARIABLE 2
#define INVALID 3

   public:
    Node* parent;

    Node();
    ~Node();
    int type;
    int getType();
    virtual void print() = 0;
};

#endif