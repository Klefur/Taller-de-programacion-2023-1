#include <iostream>
#include "Node_Number.h"

using namespace std;

/**
 * @brief Constructor de la clase Node_Number
 * @param number Numero que representa el nodo
*/
Node_Number::Node_Number(int number) {
    this->number = number;
    type = NUMBER;
}

/**
 * @brief Destructor de la clase Node_Number
*/
Node_Number::~Node_Number() {
    delete this;
}

/**
 * @brief Imprime el numero que representa el nodo
*/
void Node_Number::print() {
    cout << number;
}