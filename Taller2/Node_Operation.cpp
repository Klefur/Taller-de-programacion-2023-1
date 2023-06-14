#include <iostream>
#include "Node_Operation.h"

using namespace std;

/**
 * @brief Constructor de la clase Node_Operation, con nodos hijos
 * @param operation Operacion que representa el nodo
 * @param left Nodo izquierdo
 * @param right Nodo derecho
 */
Node_Operation::Node_Operation(char operation, Node* left, Node* right) {
    this->operation = operation;
    this->left = left;
    this->right = right;
    type = OPERATOR;
}

/**
 * @brief Constructor de la clase Node_Operation, sin nodos hijos
 * @param operation Operacion que representa el nodo
 */
Node_Operation::Node_Operation(char operation) {
    this->operation = operation;
    left = nullptr;
    right = nullptr;
    type = OPERATOR;
}

/**
 * @brief Destructor de la clase Node_Operation
 */
Node_Operation::~Node_Operation() {
    delete left;
    delete right;
    delete this;
}

void Node_Operation::print() {
    if (left != nullptr) {
        cout << " (";
        left->print();
    }

    cout << operation;

    if (right != nullptr) {
        right->print();
        cout << ") ";
    }
}
