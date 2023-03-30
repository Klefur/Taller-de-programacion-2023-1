#include <iostream>
#include <string>
#include "Stack.h"
#include "Operation.h"
#include "Restriction.h"

using namespace std;

// clase que representa el problema  del Lobo-Cabra-Repollo
class RiverCrossing {
    public:
        Stack *open; // estados por visitar
        Stack *closed; // estados visitados

        // tentativo
        Operation **op; // arreglo de operaciones, generar todas las operaciones posibles al inicio
        int numOperaciones; // numero de operaciones();
        Restriction **res; // arreglo de restricciones del archivo de entrada "filename"
        int numRestricciones; // numero de restricciones

        RiverCrossing(string filename); // aqui se generan todas las operaciones y restricciones
        ~RiverCrossing();
        void solve(); // resuelve el problema
        void print(); // imprime el estado actual
};


