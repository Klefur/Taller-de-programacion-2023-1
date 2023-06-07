#include "Node.h"

class Node_Number : public Node {
   public:
    int number;
    Node *parent;

    Node_Number(int number);
    ~Node_Number();
    void print();
};