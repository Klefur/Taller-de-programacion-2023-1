#ifndef _NODE
#define _NODE

#define NUMBER 0
#define OPERATOR 1
#define VARIABLE 2
#define INVALID 3

/**
 * @brief Clase abstracta que representa un nodo de un arbol
 * 
 */
class Node {
   public:
    int type;

    Node();
    ~Node();
    bool isNodeOperator();
    bool isNodeVariable();
    bool isNodeNumber();
    virtual void print() = 0;
};

#endif