#include "Node.h"

/**
 * @brief Clase que representa un nodo de tipo numero 
 */
class Node_Number : public Node {
   public:
    int number;

    Node_Number(int number);
    ~Node_Number();
    void print();
};