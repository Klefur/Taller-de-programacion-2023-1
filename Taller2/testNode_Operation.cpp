#include <iostream>
#include "Node_Number.h"
#include "Node_Operation.h"

using namespace std;

int main(int argc, char const* argv[]) {
    Node* node1 = new Node_Number(5);
    Node* node2 = new Node_Number(7);
    Node_Operation* node = new Node_Operation('+', node1, node2);
    cout << "El valor del nodo es: " << node->operation << endl;
    cout << "El tipo del nodo es: " << node->type << endl;
    cout << "El tipo del nodo izquierdo es: " << node->left->type << endl;
    cout << "El tipo del nodo derecho es: " << node->right->type << endl;
    node->print();

    return 0;
}
