#include <iostream>

class State
{
public:
    int coste;
    int *left;  // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
    int *right; // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
    State *previous;
    State(int largo);                                                      // constructor por fecto con largo variable
    State(int left[], int right[], State *previous, int largo, int coste); // constructores especificos
    ~State();                                                              // destructor
    void print(int largo);                                                 // imprime el estado
    bool isFinal(int largo);                                               // verifica si es el estado final
    void printPath(int largo);                                             // imprime el camino desde el estado inicial hasta el final
};