#include "Node.h"

class Node_Variable : public Node {
   public:
    char variable;

    Node_Variable(char variable);
    ~Node_Variable();
    void print();
};