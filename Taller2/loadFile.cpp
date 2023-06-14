#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

#include "AST.h"

// sstream es un stream de caracteres
using namespace std;

int main() {
    AST* tree = new AST("expr1.txt");

    tree->print();

    cout << endl;

    Node* root3 = tree->derivate(tree->root, 'x');
    root3->print();
    cout << endl;

    Node* root4 = tree->simplify(root3);
    root4->print();

    // Node_Operation *root2 = (Node_Operation*)tree->root;
    // cout << tree->equals(root2->left, root2->right) << endl;

    return 0;
}
