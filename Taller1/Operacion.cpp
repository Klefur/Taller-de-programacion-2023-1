#include "Operacion.h"
#include <iostream>

using namespace std;

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
