#include <iostream>
#include "Stack.h"

using namespace std;

// clase que representa el problema  del Lobo-Cabra-Repollo
class CrossingRiver
{
public:
    int cantidadDerecha;
    int *restriccionDerecha;
    int cantidadIzquierda;
    int *restriccionIzquierda;
    int farmers;
    int items;
    int boatSize;
    Stack *open;
    Stack *closed;
    CrossingRiver(const char *name);
    ~CrossingRiver();
    void solve();                                                       // resuelve el problema
    State *move(State *s, int item);                                    // Generalizacion de move
    bool canMove(State *s, int item);                                   // Generalizacion de canMove
    int binaryToDecimal(int binaryArray[], int arraySize);
};