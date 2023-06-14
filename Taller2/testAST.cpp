#include <iostream>
#include "AST.h"

using namespace std;

int main(int argc, char const* argv[]) {
    string filename = "expr1.txt";
    AST* tree = new AST(filename);
    tree->print();
    cout << endl;
    cout << "La evaluacion es: " << tree->eval(tree->root) << endl;
    cout << "La derivada es: ";
    Node* derivative = tree->derivate(tree->root, 'x');
    derivative->print();

    return 0;
}
