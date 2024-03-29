#include <iostream>
#include "Operacion.h"

using namespace std;

int cont = 0;
Operacion **ops;
int pesos[3] = {3, 6, 7};
int restricciones[3] = {3, 6, 7};

int binaryToDecimal(int binaryArray[], int arraySize)
{
    int decimalValue = 0;

    for (int i = 0; i < arraySize; i++)
    {
        decimalValue = (decimalValue << 1) + binaryArray[i];
    }

    return decimalValue;
}

bool isValid(int *arr)
{
    int binaryArr = binaryToDecimal(arr, 4);
    for (int i = 0; i < 3; ++i)
    {
        if (binaryArr == restricciones[i])
        {
            return false;
        }
    }
    return true;
}

void generarCombinaciones(int v[], int i, int n)
{
    if (i == n)
    { // caso base: si hemos llegado al final del arreglo
        int peso = binaryToDecimal(v, i);

        ops[cont] = new Operacion(v, n, peso);
        return;
    }

    v[i] = 0; // generamos la combinación con un 0 en la posición i
    generarCombinaciones(v, i + 1, n);

    v[i] = 1; // generamos la combinación con un 1 en la posición i
    generarCombinaciones(v, i + 1, n);
}

int main(int argc, char const *argv[])
{
    int a[4] = {1, 1, 1, 1};

    ops = new Operacion *[(1 << 4)];

    generarCombinaciones(a, 0, 4);

    cout << cont << " "
         << "Lectura de ops: " << endl;

    for (int i = 0; i < 2 << 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << ops[i]->op[j] << " ";
        }
        cout << "peso: " << ops[i]->peso << endl;
    }
    return 0;
}
