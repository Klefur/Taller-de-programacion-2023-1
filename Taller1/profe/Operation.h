#include <iostream>
#include "State.h"
#include "Restriction.h"

using namespace std;

class Operation {
    public:
        int *op; // configuracion de la operacion
        int numOp; // cantidad itemes y cond

        // int op;

        Restriction **res; // arreglo de restricciones
        int numRes; // cantidad de restricciones

        Operation(int *op, int numOp, Restriction *res);
        ~Operation();
        void print(); // Imprime las operaciones
        State * Move(State e); // Mueve segun esta operacion el estado e
        bool canMove(State e, Restriction *res);
        // retorna nullptr sino puede mover
};

