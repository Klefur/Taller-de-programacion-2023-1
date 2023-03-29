#include <iostream>
#include "Stack.h"

using namespace std;

// clase que representa el problema  del Lobo-Cabra-Repollo
class CrossingRiver
{
public:
    int cantidadDerecha;
    int **restriccionDerecha;
    int cantidadIzquierda;
    int **restriccionIzquierda;
    int farmers;
    int items;
    int boatSize;
    Stack *open;
    Stack *closed;
    CrossingRiver(
        int farmers,
        int items,
        int boatSize,
        int cantidadIzquierda,
        int *restriccionIzquierda[],
        int cantidadDerecha,
        int *restriccionDerecha[]);
    ~CrossingRiver();
    void solve();                                                      // resuelve el problema
    State *move(State *s, int item);                                   // Generalizacion de move
    bool canMove(State *s, int item);                                  // Generalizacion de canMove
    bool checkMatrix(int arr[], int item, int *matrix[], int cantidad); // verifica si hay algun problema en restricciones                                       // verifica si se puede mover el repollo
};