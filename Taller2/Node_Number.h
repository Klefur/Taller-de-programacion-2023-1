#include "Node.h"

class Node_Number : public Node {
   public:
    char operation;

    Node_Number(int number);
    ~Node_Number();
    void print();
};