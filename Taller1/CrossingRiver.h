#include <iostream>
#include "Stack.h"
#include "Operacion.h"

using namespace std;

// clase que representa el problema  del Lobo-Cabra-Repollo
class CrossingRiver
{
public:
    int cantidadIzquierda;
    int cantidadDerecha;
    int *restriccionIzquierda;
    int *restriccionDerecha;

    int farmers;
    int items;
    int boatSize;
    int largoOps;

    Operacion **ops;
    Stack *open;
    Stack *closed;

    CrossingRiver(const char *name);
    ~CrossingRiver();
    void solve();                          // resuelve el problema
    State *move(State *s, Operacion *op);  // Generalizacion de move
    bool canMove(State *s, Operacion *op); // Generalizacion de canMove
    void generarCombinaciones(int v[], int i, int n);
    int binaryToDecimal(int binaryArray[], int arraySize);
};