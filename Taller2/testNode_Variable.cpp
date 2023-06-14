#include <iostream>
#include "Node_Variable.h"

using namespace std;

int main(int argc, char const* argv[]) {
    Node_Variable* node = new Node_Variable('x');
    cout << "El valor del nodo es: " << node->variable << endl;
    cout << "El tipo del nodo es: " << node->type << endl;
    node->print();
    return 0;
}
