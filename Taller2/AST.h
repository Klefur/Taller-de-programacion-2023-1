#include <fstream>
#include <sstream>
#include <stack>
#include <string>

#include "Node_Number.h"
#include "Node_Operation.h"
#include "Node_Variable.h"

/**
 * @brief Clase que representa un arbol de operaciones en notacion polaca
 */
class AST {
   public:
    Node* root;

    AST(std::string namefile);
    ~AST();

    int eval(Node* node);
    Node* clone(Node* node);
    Node* replace(Node* node, std::string variable, int* value, int largo);
    Node* derivate(Node* node, char variable);
    Node* simplify(Node* node);
    Node* simplifySum(Node* node);
    Node* simplifyMult(Node* node);
    Node* simplifyNullable(Node* node);

    void print();

    bool readTree(Node* node,
                  std::stack<char>* variables,
                  std::stack<int>* numbers,
                  char operation);
};
