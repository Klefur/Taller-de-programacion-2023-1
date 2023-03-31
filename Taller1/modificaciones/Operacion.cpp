#include "Operacion.h"

Operacion::Operacion(int *arr, int largo)
{
    this->op = new int[largo];

    for (int i = 0; i < largo; ++i)
    {
        this->op[i] = arr[i];
    }
}

Operacion::~Operacion()
{
}
