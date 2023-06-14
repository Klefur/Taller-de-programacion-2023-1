#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

#include "AST.h"

// sstream es un stream de caracteres
using namespace std;

int main() {
    AST* tree = new AST("expr2.txt");

    tree->print();

    cout << endl;

    // Node* root3 = tree->derivate(tree->root, 'x');
    // root3->print();
    // cout << endl;

    Node* root5 = tree->simplify(tree->root);

    root5->print();

    return 0;
}
