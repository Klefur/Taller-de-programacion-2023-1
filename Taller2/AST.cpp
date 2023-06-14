#include <iostream>

#include "AST.h"

using namespace std;

/**
 * @brief Verifica si un token es un operador
 * @param token Token a verificar
 * @return True si es un operador, false si no
 * */
bool isOperator(string token) {
    return token == "+" || token == "-" || token == "*" || token == "^";
}

/**
 * @brief Verifica si un token es un numero
 * @param token Token a verificar
 * @return True si es un numero, false si no
 * */
bool isNumber(string token) {
    return token[0] >= '0' && token[0] <= '9';
}

/**
 * @brief Verifica si un token es una variable
 * @param token Token a verificar
 * @return True si es una variable, false si no
 * */
bool isVariable(string token) {
    return (token[0] >= 'a' && token[0] <= 'z') ||
           (token[0] >= 'A' && token[0] <= 'Z');
}

/**
 * @brief Obtiene la potencia de un numero
 * @param base numero a elevar
 * @param exp exponente
 * @return Resultado de la potencia
 * */
int pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/**
 * @brief Constructor de AST, lee un archivo y genera el arbol
 * @param filename Nombre del archivo a leer
 * */
AST::AST(string filename) {
    root = nullptr;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << endl;
        exit(1);
    }
    Node_Operation* op = nullptr;
    Node_Number* num = nullptr;
    Node_Variable* var = nullptr;
    Node* node = nullptr;

    string line, token;
    stringstream ss;

    stack<Node_Operation*> pila;

    if (getline(file, line, '\n')) {
        cout << line << endl;
        ss << line;
        while (getline(ss, token, ' ')) {
            cout << token << endl;
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

            if (root == nullptr) {
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
        exit(1);
    }

    file.close();
}

/**
 * @brief Destructor de AST
 * */
AST::~AST() {}

/**
 * @brief Evalua el arbol si todos son enteros
 * @param node Nodo a evaluar, puede ser un numero o una operacion
 * @return Resultado de la evaluacion
 * */
int AST::eval(Node* node) {
    if (node->isNodeOperator()) {
        Node_Operation* op = (Node_Operation*)node;
        int l = eval(op->left);
        int r = eval(op->right);
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

/**
 * @brief Clona el arbol
 * @param node Nodo a clonar
 * @return arbol clonado
 * */
Node* AST::clone(Node* node) {
    if (node->isNodeNumber()) {
        Node_Number* number = (Node_Number*)node;
        Node_Number* new_number = new Node_Number(number->number);
        return new_number;
    } else if (node->isNodeVariable()) {
        Node_Variable* variable = (Node_Variable*)node;
        Node_Variable* new_ver = new Node_Variable(variable->variable);
        return new_ver;
    }

    Node_Operation* operation = (Node_Operation*)node;
    Node* left = clone(operation->left);
    Node* right = clone(operation->right);
    Node_Operation* new_operation =
        new Node_Operation(operation->operation, left, right);
    return new_operation;
}

/**
 * @brief Reemplaza las variables por valores
 * @param node arbol en el que se reemplzaran las variables
 * @param variable Variables a reemplazar
 * @param value Valorres a reemplazar
 * @param largo Largo de los arreglos
 * @return Nodo reemplazado
 * */
Node* AST::replace(Node* node, string variable, int* value, int largo) {
    if (node->isNodeNumber()) {
        return node;
    } else if (node->isNodeVariable()) {
        for (int i = 0; i < largo; i++) {
            if (variable[i] == ((Node_Variable*)node)->variable) {
                Node* reemplazo = new Node_Number(value[i]);
                return reemplazo;
            }
        }
    }

    Node_Operation* operation = (Node_Operation*)node;
    Node* left = replace(operation->left, variable, value, largo);
    Node* right = replace(operation->right, variable, value, largo);
    return new Node_Operation(operation->operation, left, right);
}

/**
 * @brief Deriva el arbol
 * @param node Nodo a derivar
 * @param variable Variable a derivar
 * @return Nodo derivado
 * */
Node* AST::derivate(Node* node, char variable) {
    if (node->isNodeOperator()) {
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
    } else if (node->isNodeNumber()) {
        return new Node_Number(0);
    } else if (node->isNodeVariable()) {
        Node_Variable* var = (Node_Variable*)node;
        if (var->variable == variable) {
            return new Node_Number(1);
        } else {
            return new Node_Number(0);
        }
    }

    return nullptr;
}

/**
 * @brief Simplifica un arbol
 * @param node Nodo a simplificar
 * @return Node* Nodo simplificado
 * */
Node* AST::simplify(Node* node) {
    Node* simplified;
    Node* compared;
    Node_Operation* op = (Node_Operation*)node;

    if (op->operation == '+') {
        simplified = simplifySum(node);
    } else if (op->operation == '*') {
        simplified = simplifyMult(node);
    }
    if (simplified == nullptr) {
        simplified = node;
    }

    do {
        compared = simplified;
        simplified = simplifyNullable(simplified);
    }
    while (!equals(simplified, compared));

    return simplified;
}

/**
 * @brief Simplifica un arbol constituído solo por sumas
 * @param node Nodo a simplificar
 * @return Node* Nodo simplificado
 * */
Node* AST::simplifySum(Node* node) {
    Node_Operation* simplified = new Node_Operation('+');

    stack<int> numbers;
    stack<char> variables;
    stack<Node_Operation*> operators;

    bool isOnlySum = readTree(node, &variables, &numbers, '+');

    if (!isOnlySum) {
        return nullptr;
    }

    int largo = variables.size();
    char* variable = new char[largo];
    int* countVariable = new int[largo];

    for (int i = 0; i < largo; i++) {
        countVariable[i] = 0;
        variable[i] = '0';
    }

    int sum = 0;

    while (!numbers.empty()) {
        sum += numbers.top();
        numbers.pop();
    }

    bool added = false;
    while (!variables.empty()) {
        for (int i = 0; i < largo; i++) {
            if (variable[i] == variables.top()) {
                countVariable[i]++;
                added = true;
            } else if (variable[i] == '0') {
                variable[i] = variables.top();
                countVariable[i]++;
                added = true;
            }

            if (added) {
                variables.pop();
                added = false;
                break;
            }
        }
    }

    for (int i = 0; i < largo; i++) {
        if (variable[i] != '0') {
            Node_Operation* new_operator =
                new Node_Operation('*', new Node_Variable(variable[i]),
                                   new Node_Number(countVariable[i]));
            operators.push(new_operator);
        }
    }

    Node* new_number = new Node_Number(sum);

    simplified->right = new_number;

    Node_Operation* aux = simplified;

    while (!operators.empty()) {
        if (operators.size() == 1) {
            aux->left = operators.top();
            operators.pop();
        } else {
            aux->left = new Node_Operation('+');
            aux = (Node_Operation*)aux->left;
            aux->right = operators.top();
            operators.pop();
        }
    }

    return simplified;
}

/**
 * @brief Simplifica un arbol constituído solo por multiplicaciones
 * @param node Nodo a simplificar
 * @return Node* Nodo simplificado
 * */
Node* AST::simplifyMult(Node* node) {
    Node_Operation* simplified = new Node_Operation('*');

    stack<int> numbers;
    stack<char> variables;
    stack<Node_Operation*> operators;

    bool isOnlyMult = readTree(node, &variables, &numbers, '*');

    if (!isOnlyMult) {
        return nullptr;
    }

    int largo = variables.size();
    char* variable = new char[largo];
    int* countVariable = new int[largo];

    for (int i = 0; i < largo; i++) {
        countVariable[i] = 0;
        variable[i] = '0';
    }

    int mult = 1;

    while (!numbers.empty()) {
        mult *= numbers.top();
        numbers.pop();
    }

    bool added = false;
    while (!variables.empty()) {
        for (int i = 0; i < largo; i++) {
            if (variable[i] == variables.top()) {
                countVariable[i]++;
                added = true;
            } else if (variable[i] == '0') {
                variable[i] = variables.top();
                countVariable[i]++;
                added = true;
            }

            if (added) {
                variables.pop();
                added = false;
                break;
            }
        }
    }

    for (int i = 0; i < largo; i++) {
        if (variable[i] != '0') {
            Node_Operation* new_operator =
                new Node_Operation('^', new Node_Variable(variable[i]),
                                   new Node_Number(countVariable[i]));
            operators.push(new_operator);
        }
    }

    Node* new_number = new Node_Number(mult);

    simplified->right = new_number;

    Node_Operation* aux = simplified;

    while (!operators.empty()) {
        if (operators.size() == 1) {
            aux->left = operators.top();
            operators.pop();
        } else {
            aux->left = new Node_Operation('*');
            aux = (Node_Operation*)aux->left;
            aux->right = operators.top();
            operators.pop();
        }
    }

    return simplified;
}

/**
 * @brief Simplifica casos simples de un arbol como la multiplicación por 0
 * @param node Nodo a simplificar
 * @return Node* Nodo simplificado
 * */
Node* AST::simplifyNullable(Node* node) {
    if (node->type == OPERATOR) {
        Node_Operation* op = (Node_Operation*)node;

        if (op->operation == '+') {
            if (op->left->type == NUMBER &&
                ((Node_Number*)op->left)->number == 0) {
                return op->right;
            } else if (op->right->type == NUMBER &&
                       ((Node_Number*)op->right)->number == 0) {
                return op->left;
            } else if (op->left->type == VARIABLE &&
                       op->right->type == VARIABLE) {
                Node_Variable* var1 = (Node_Variable*)op->left;
                Node_Variable* var2 = (Node_Variable*)op->right;

                if (var1->variable == var2->variable) {
                    return new Node_Operation('*',
                                              new Node_Variable(var1->variable),
                                              new Node_Number(2));
                }
            }
        } else if (op->operation == '*') {
            if (op->left->type == NUMBER &&
                ((Node_Number*)op->left)->number == 1) {
                return op->right;
            } else if (op->right->type == NUMBER &&
                       ((Node_Number*)op->right)->number == 1) {
                return op->left;
            } else if (op->left->type == NUMBER &&
                       ((Node_Number*)op->left)->number == 0) {
                return new Node_Number(0);
            } else if (op->right->type == NUMBER &&
                       ((Node_Number*)op->right)->number == 0) {
                return new Node_Number(0);
            } else if (op->left->type == VARIABLE &&
                       op->right->type == VARIABLE) {
                Node_Variable* var1 = (Node_Variable*)op->left;
                Node_Variable* var2 = (Node_Variable*)op->right;

                if (var1->variable == var2->variable) {
                    return new Node_Operation('^',
                                              new Node_Variable(var1->variable),
                                              new Node_Number(2));
                }
            }
        } else if (op->operation == '-') {
            if (op->right->type == NUMBER &&
                ((Node_Number*)op->right)->number == 0) {
                return op->left;
            } else if (op->left->type == VARIABLE &&
                       op->right->type == VARIABLE) {
                Node_Variable* var1 = (Node_Variable*)op->left;
                Node_Variable* var2 = (Node_Variable*)op->right;

                if (var1->variable == var2->variable) {
                    return new Node_Number(0);
                }
            }
        } else if (op->operation == '^') {
            if (op->left->type == NUMBER &&
                ((Node_Number*)op->left)->number == 0) {
                return new Node_Number(0);
            } else if (op->right->type == NUMBER &&
                       ((Node_Number*)op->right)->number == 0) {
                return new Node_Number(1);
            } else if (op->left->type == NUMBER &&
                       ((Node_Number*)op->left)->number == 1) {
                return new Node_Number(1);
            } else if (op->right->type == NUMBER &&
                       ((Node_Number*)op->right)->number == 1) {
                return op->left;
            }
        }
        Node* left = simplifyNullable(op->left);
        Node* right = simplifyNullable(op->right);
        ((Node_Operation*)node)->left = left;
        ((Node_Operation*)node)->right = right;
    }

    return node;
}

/**
 * @brief Recibe 2 nodos y compara si el arbol que representa
 * es igual al a comparar
 * @param node1 Nodo a comparar
 * @param node2 Nodo a comparar
 * @return bool True si son iguales False si no
 * */
bool AST::equals(Node* node1, Node* node2) {
    if (node1->type == node2->type) {
        if (node1->type == OPERATOR) {
            Node_Operation* op1 = (Node_Operation*)node1;
            Node_Operation* op2 = (Node_Operation*)node2;

            if (op1->operation == op2->operation) {
                return (equals(op1->left, op2->left) &&
                        equals(op1->right, op2->right)) ||
                       (equals(op1->left, op2->right) &&
                        equals(op1->right, op2->left));
            } else {
                return false;
            }
        } else if (node1->type == NUMBER && node2->type == NUMBER) {
            Node_Number* num1 = (Node_Number*)node1;
            Node_Number* num2 = (Node_Number*)node2;

            return num1->number == num2->number;
        } else if (node1->type == VARIABLE && node2->type == VARIABLE) {
            Node_Variable* var1 = (Node_Variable*)node1;
            Node_Variable* var2 = (Node_Variable*)node2;

            return var1->variable == var2->variable;
        }
    }
    return false;
}

/**
 * @brief Imprime el arbol
 * */
void AST::print() {
    root->print();
}

/**
 * @brief Recibe un nodo y lee el arbol guandando los numeros y variables en en
 * un stack esto para un arbol de un solo tipo de operacion
 * @param node Nodo a leer
 * @param variables Stack de variables
 * @param numbers Stack de numeros
 * @param operation Operacion a buscar
 * @return bool False si el arbol no es del tipo de operacion buscado True si lo
 * es
 * */
bool AST::readTree(Node* node,
                   stack<char>* variables,
                   stack<int>* numbers,
                   char operation) {
    bool left, right;

    if (node->isNodeOperator() &&
        ((Node_Operation*)node)->operation == operation) {
        Node_Operation* op = (Node_Operation*)node;
        left = readTree(op->left, variables, numbers, operation);

        if (!left) {
            return left;
        }

        right = readTree(op->right, variables, numbers, operation);

        if (!right) {
            return right;
        }
    } else if (node->isNodeNumber()) {
        numbers->push(((Node_Number*)node)->number);
    } else if (node->isNodeVariable()) {
        variables->push(((Node_Variable*)node)->variable);
    } else {
        return false;
    }
    return true;
}