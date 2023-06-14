#include "Node.h"

/**
 * @brief Clase que representa un nodo de tipo variable
 */
class Node_Variable : public Node {
   public:
    char variable;

    Node_Variable(char variable);
    ~Node_Variable();
    Node* clone(Node* node);
    void print();
};