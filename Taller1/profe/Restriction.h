#include <iostream>
#include "State.h"

using namespace std;

class Restriction {
    public:
        bool *cond; // Quienes no estan permitidos estar 
        int numCond; // Numero de condiciones

        Restriction();
        ~Restriction();
        bool isValid(State *s); // Verifica si el estado es valido
};