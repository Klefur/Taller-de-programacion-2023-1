#include "State.h"

using namespace std;

// Entrada: El largo del arreglo
// Salida: -
// Funcionamiento: Constructor de la clase inicial
State::State(int largo)
{
    this->left = new int[largo];
    this->right = new int[largo];
    this->boatIsLeft = true;

    for (int i = 0; i < largo; i++)
    {
        this->left[i] = 1;  // todos a la izquierda
        this->right[i] = 0; // nada a la derecha
    }
    this->coste = (1 << largo) - 1;
    previous = nullptr;
}

// Entrada: Un arreglo de enteros, el largo del arreglo, el estado anterior,
//          el costo de la operacion y la posicion del bote
// Salida: -
// Funcionamiento: Constructor de la clase para un estado en secuencia de otro
State::State(int left[], int right[], State *previous, int largo, int coste, bool boatIsLeft)
{
    this->left = new int[largo];
    this->right = new int[largo];
    this->boatIsLeft = boatIsLeft;

    for (int i = 0; i < largo; i++)
    {
        this->left[i] = left[i];
        this->right[i] = right[i];
    }
    this->previous = previous;
    this->coste = coste;
}

State::~State()
{
    // no se necesita
}

// Entrada: El largo del arreglo
// Salida: -
// Funcionamiento: Imprime el estado
void State::print(int largo)
{
    for (int i = 0; i < largo; i++)
    {
        cout << this->left[i] << " ";
    }
    cout << " | ";
    for (int i = 0; i < largo; i++)
    {
        cout << this->right[i] << " ";
    }

    cout << endl;
}

// Entrada: El largo del arreglo
// Salida: Un booleano
// Funcionamiento: Retorna true si el estado es final verificando que 
//                 todos en la derecha sean 1, false sino
bool State::isFinal(int largo)
{
    for (int i = 0; i < largo; i++)
    {
        if (this->right[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// Entrada: El largo del arreglo
// Salida: -
// Funcionamiento: Imprime el camino desde el estado final hasta el inicial
void State::printPath(int largo)
{
    State *actual = this; // this es puntero al objeto actual
    actual->print(largo);
    while (actual->previous != nullptr)
    {
        actual = actual->previous;
        actual->print(largo);
    }
}