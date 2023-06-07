#include <iostream>
#include "Node_Operation.h"

using namespace std;

Node_Operation::Node_Operation(char operation, Node* left, Node* right) {
    this->operation = operation;
    this->left = left;
    this->right = right;
    parent = nullptr;
    type = OPERATOR;
}

Node_Operation::Node_Operation(char operation) {
    this->operation = operation;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    type = OPERATOR;
}

Node_Operation::~Node_Operation() {
    if (left != nullptr) {
        delete left;
    }

    if (right != nullptr) {
        delete right;
    }
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
