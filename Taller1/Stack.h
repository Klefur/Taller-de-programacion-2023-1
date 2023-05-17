#include <iostream>
#include "State.h"

using namespace std;

class Stack
{
public:
    int top;       // indice del tope
    State **stack; // arreglo de punteros a State
    int size;      // tamaño del arreglo

    // Constructor
    Stack(int size);
    // Destructor
    ~Stack();
    // Inserta un elemento al tope del stack
    void push(State *s);
    // Elimina el elemento del tope del stack
    State *pop();
    // Verifica si se encuentra un estado en el stack
    bool search(State *s);
    // Retorna true si el stack está vacio
    bool isEmpty();
    // Imprime el stack
    void print(int largo);
};