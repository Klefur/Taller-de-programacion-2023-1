#include <iostream>
#include "Node_Number.h"

using namespace std;

int main(int argc, char const* argv[]) {
    Node_Number* node = new Node_Number(5);
    cout << "El valor del nodo es: " << node->number << endl;
    cout << "El tipo del nodo es: " << node->type << endl;
    node->print();
    return 0;
}
