#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <stack>

#include "Node_Number.h"
#include "Node_Operation.h"
#include "Node_Variable.h"

// sstream es un stream de caracteres
using namespace std;

int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

bool isNodeOperator(Node* node) {
    return node->type == OPERATOR;
}

bool isOperator(string token) {
    return token == "+" || token == "-" || token == "*" || token == "^";
}

bool isNumber(string token) {
    return token[0] >= '0' && token[0] <= '9';
}

bool isVariable(string token) {
    return (token[0] >= 'a' && token[0] <= 'z') ||
           (token[0] >= 'A' && token[0] <= 'Z');
}

int eval_int(Node* node) {
    if (isNodeOperator(node)) {
        Node_Operation* op = (Node_Operation*)node;
        int l = eval_int(op->left);
        int r = eval_int(op->right);
        switch (op->operation) {
            case '+':
                return l + r;
            case '-':
                return l - r;
            case '*':
                return l * r;
            case '^':
                return pow(l, r);
            default:
                cout << "Error" << endl;
                exit(1);
        }
    } else {
        return ((Node_Number*)node)->number;
    }
}

int main() {
    ifstream file("expr1.txt");
    if (!file.is_open()) {
        cout << "Could not open file " << endl;
        return 1;
    }
    Node_Operation* op = nullptr;
    Node_Number* num = nullptr;
    Node_Variable* var = nullptr;
    Node* node = nullptr;
    Node* root = nullptr;

    string line, token;
    stringstream ss;

    stack<Node_Operation*> pila;

    if (getline(file, line, '\n')) {
        cout << line << endl;
        ss << line;
        // si stream ss es "+ * - 1 2 3"
        // el primer get line obtiene "+"
        while (getline(ss, token, ' ')) {
            cout << token << endl;
            // creamos el nodo dependiendo del token
            if (isOperator(token)) {
                cout << "Es un operador" << token << endl;
                node = new Node_Operation(token[0]);

            } else if (isNumber(token)) {
                cout << "Es un numero: " << token << endl;
                int valor = stoi(token);
                node = new Node_Number(valor);

            } else if (isVariable(token)) {
                cout << "Es un identificador: " << token << endl;
                char name = token[0];
                node = new Node_Variable(name);
            }

            if (root == NULL) {
                root = node;
            }

            // dependiendo del top del stack se agrega a la izquierda o derecha
            if (!pila.empty()) {
                if (pila.top()->left == nullptr) {
                    pila.top()->left = node;
                } else if (pila.top()->right == nullptr) {
                    pila.top()->right = node;
                    pila.pop();
                } else {
                    node->print();
                    cout << "Error" << endl;
                    exit(1);
                }
            }
            // si es un operador se agrega a la pila
            if (node->type == OPERATOR) {
                pila.push((Node_Operation*)node);
            }
        }
    } else {
        cout << "Could not read line" << endl;
        return 1;
    }

    root->print();

    cout << endl << eval_int(root) << endl;



    file.close();
    return 0;
}