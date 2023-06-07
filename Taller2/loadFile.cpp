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

bool isNodeNumber(Node* node) {
    return node->type == NUMBER;
}

bool isNodeVaraible(Node* node) {
    return node->type == VARIABLE;
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

int eval_recursive(Node* node) {
    if (isNodeOperator(node)) {
        Node_Operation* op = (Node_Operation*)node;
        int l = eval_recursive(op->left);
        int r = eval_recursive(op->right);
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

Node* replace(Node* node, string variable, int* value, int largo) {
    if (isNodeNumber(node)) {
        return node;
    } else if (isNodeVaraible(node)) {
        for (int i = 0; i < largo; i++) {
            if (variable[i] == ((Node_Variable*)node)->variable) {
                Node* reemplazo = new Node_Number(value[i]);
                reemplazo->parent = node->parent;
                return reemplazo;
            }
        }
    }

    Node_Operation* operation = (Node_Operation*)node;
    Node* left = replace(operation->left, variable, value, largo);
    Node* right = replace(operation->right, variable, value, largo);
    return new Node_Operation(operation->operation, left, right);
}

Node* clone(Node* node) {
    if (isNodeNumber(node)) {
        Node_Number* number = (Node_Number*)node;
        Node_Number* new_number = new Node_Number(number->number);
        new_number->parent = number->parent;
        return new_number;
    } else if (isNodeVaraible(node)) {
        Node_Variable* variable = (Node_Variable*)node;
        Node_Variable* new_ver = new Node_Variable(variable->variable);
        new_ver->parent = variable->parent;
        return new_ver;
    }

    Node_Operation* operation = (Node_Operation*)node;
    Node* left = clone(operation->left);
    Node* right = clone(operation->right);
    Node_Operation* new_operation =
        new Node_Operation(operation->operation, left, right);
    new_operation->parent = operation->parent;
    return new_operation;
    ;
}

Node* derivate(Node* node, char variable) {
    if (isNodeOperator(node)) {
        Node_Operation* op = (Node_Operation*)node;
        int numero = 0;
        Node_Number* num = nullptr;

        switch (op->operation) {
            case '+':
                return new Node_Operation('+', derivate(op->left, variable),
                                          derivate(op->right, variable));

            case '-':
                return new Node_Operation('-', derivate(op->left, variable),
                                          derivate(op->right, variable));
            case '*':
                return new Node_Operation(
                    '+',
                    new Node_Operation('*', derivate(op->left, variable),
                                       clone(op->right)),
                    new Node_Operation('*', clone(op->left),
                                       derivate(op->right, variable)));

            case '^':
                num = (Node_Number*)op->right;
                numero = (num->number) - 1;

                return new Node_Operation(
                    '*', op->right,
                    new Node_Operation(
                        '*',
                        new Node_Operation('^', op->left,
                                           new Node_Number(numero)),
                        derivate(op->left, variable)));

            default:
                cout << "Error" << endl;
                exit(1);
        }
    } else if (isNodeNumber(node)) {
        return new Node_Number(0);
    } else if (isNodeVaraible(node)) {
        Node_Variable* var = (Node_Variable*)node;
        if (var->variable == variable) {
            return new Node_Number(1);
        } else {
            return new Node_Number(0);
        }
    }

    return nullptr;
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
                    ((Node_Operation*)node)->parent = pila.top();
                } else if (pila.top()->right == nullptr) {
                    pila.top()->right = node;
                    ((Node_Operation*)node)->parent = pila.top();
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

    cout << endl;

    // Node* root2 = clone(root);

    // delete root;

    // root2->print();

    // cout << endl;

    // Node* root3 = replace(root2, "xy", new int[2]{10, 2}, 2);

    // root3->print();

    // cout << endl;

    // int value = eval_recursive(root3);

    // cout << "Evaluado es: " << value << endl;

    Node* root3 = derivate(root, 'y');
    root3->print();
    cout << endl;
    Node* root4 = replace(root3, "xy", new int[2]{10, 2}, 2);
    root4->print();
    cout << endl;
    int value = eval_recursive(root4);
    cout << "Evaluado es: " << value << endl;

    file.close();

    return 0;
}
