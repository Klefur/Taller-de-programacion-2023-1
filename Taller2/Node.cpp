#include "Node.h"
#include "Node_Number.h"
#include "Node_Operation.h"
#include "Node_Variable.h"

/**
 * @brief Constructor de la clase Node
 */
Node::Node() {
    type = INVALID;
}

/**
 * @brief Destructor de la clase Node
 */
Node::~Node() {}

/**
 * @brief Verifica si el nodo es un nodo de operacion
 */
bool Node::isNodeOperator() {
    return type == OPERATOR;
}

/**
 * @brief Verifica si el nodo es un nodo de variable
 */
bool Node::isNodeVariable() {
    return type == VARIABLE;
}

/**
 * @brief Verifica si el nodo es un nodo de numero
 */
bool Node::isNodeNumber() {
    return type == NUMBER;
}