#include "Operacion.h"
#include <iostream>

using namespace std;

Operacion::Operacion(int *arr, int largo, int peso, int coste)
{
    this->op = new int[largo];
    this->peso = peso;
    this->coste = coste;

    for (int i = 0; i < largo; ++i)
    {
        this->op[i] = arr[i];
    }
}

Operacion::~Operacion()
{
}
