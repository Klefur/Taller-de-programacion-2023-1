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

    // Constructor
    CrossingRiver(const char *name);
    // Destructor
    ~CrossingRiver();
    // resuelve el problema
    void solve();                          
    // Generalizacion de move, mueve elementos
    State *move(State *s, Operacion *op);  
    // Generalizacion de canMove, verifica si se pueden mover elementos
    bool canMove(State *s, Operacion *op); 
    // Genera las operaciones
    void generarCombinaciones(int v[], int i, int n);
    // Convierte de binario a decimal
    int binaryToDecimal(int binaryArray[], int arraySize);
};