#include "Node_Variable.h"

Node_Variable::Node_Variable(char variable) {
    this->variable = variable;
    type = VARIABLE;
}

Node_Variable::~Node_Variable() {}
