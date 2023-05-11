#include "Operacion.h"
#include <iostream>

using namespace std;

// Entrada: Un arreglo de enteros, el largo del arreglo y el peso de la operacion
// Salida: -
// Funcionamiento: Constructor de la clase
Operacion::Operacion(int *arr, int largo, int peso)
{
    this->op = new int[largo];
    this->peso = peso;

    for (int i = 0; i < largo; ++i)
    {
        this->op[i] = arr[i];
    }
}

Operacion::~Operacion()
{
}
