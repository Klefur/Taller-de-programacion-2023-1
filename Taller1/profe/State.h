#include <iostream>

using namespace std;

// estos define ya no tienen sentido 
#define WOLF 0
#define GOAT 1
#define CABBAGE 2
#define FARMER 3

class State {
    public:
        int left[4]; // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
        int right[4]; // 0: Lobo 1: Cabra 2: Repollo 3: Granjero
        State* previous;
        // valores utiles para accelerar el algoritmo A*
        int value; // valor de la heuristica: puede sercantidad de 1s a la derecha
        int depth; // profundidad del estado dentro del arbol
        int valorDecimal; // valor decimal del estado

        State(); // constructor por fecto sin argumentos
        State(int *left, int *right, State* previous); // constructores especificos
        ~State(); // destructor
        void print(); // imprime el estado
        bool isFinal(); // verifica si es el estado final
        void printPath(); // imprime el camino desde el estado inicial hasta el final
};
