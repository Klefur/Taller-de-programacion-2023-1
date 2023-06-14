#include <iostream>
#include "Node_Variable.h"

using namespace std;

/**
 * @brief Constructor de la clase Node_Variable
 * @param variable Variable que representa el nodo
*/
Node_Variable::Node_Variable(char variable) {
    this->variable = variable;
    type = VARIABLE;
}

/**
 * @brief Destructor de la clase Node_Variable
*/
Node_Variable::~Node_Variable() {
    delete this;
}

/**
 * @brief Imprime la variable que representa el nodo
*/
void Node_Variable::print() {
    cout << variable;
}
