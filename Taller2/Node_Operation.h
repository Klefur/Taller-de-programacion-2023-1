#include "Node.h"

/**
 * @brief Clase que representa un nodo de tipo operacion
 */
class Node_Operation : public Node {
   public:
    char operation;
    Node* left;
    Node* right;

    Node_Operation(char operation, Node* left, Node* right);
    Node_Operation(char operation);  // caso de no conocer hijos
    ~Node_Operation();
    void print();
};