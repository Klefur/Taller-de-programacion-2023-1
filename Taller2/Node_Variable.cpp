#include <iostream>
#include "Node_Variable.h"

using namespace std;

Node_Variable::Node_Variable(char variable) {
    this->variable = variable;
    parent = nullptr;
    type = VARIABLE;
}

Node_Variable::~Node_Variable() {}

void Node_Variable::print() {
    cout << variable;
}
