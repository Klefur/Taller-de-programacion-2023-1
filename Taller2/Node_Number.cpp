#include <iostream>
#include "Node_Number.h"

using namespace std;

Node_Number::Node_Number(int number) {
    this->number = number;
    type = NUMBER;
}

Node_Number::~Node_Number() {}

void Node_Number::print() {
    cout << number;
}