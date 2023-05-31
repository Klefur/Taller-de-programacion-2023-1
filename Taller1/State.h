#include <iostream>

class State
{
public:
    int coste;
    int *left;  // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
    int *right; // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
    bool boatIsLeft;
    State *previous;

    // constructor por defecto con largo variable
    State(int largo);
    // constructores especificos
    State(int left[], int right[], State *previous,
          int largo, int coste, bool boatIsLeft);
    // destructor
    ~State();
    // imprime el estado
    void print(int largo);
    // verifica si es el estado final
    bool isFinal(int largo);
    // imprime el camino desde el estado inicial hasta el final
    void printPath(int largo);
};