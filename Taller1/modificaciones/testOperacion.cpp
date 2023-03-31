#include <iostream>
#include "Operacion.h"

using namespace std;
const int largo = 2 << 4;
Operacion *ops[largo]; 
int pesos[3] = {3, 6, 7};


int binaryToDecimal(int binaryArray[], int arraySize)
{
    int decimalValue = 0;

    for (int i = 0; i < arraySize; i++)
    {
        decimalValue = (decimalValue << 1) + binaryArray[i];
    }

    return decimalValue;
}

void generarCombinaciones(int v[], int i, int n, int coste, int count)
{
    if (i == n)
    { // caso base: si hemos llegado al final del arreglo
        // for (int j = 0; j < n; j++)
        // {
        //     cout << v[j] << " "; // imprimimos la combinación actual
        // }
        int peso = binaryToDecimal(v, i);
        // cout << " peso: " << peso;
        // cout << " coste: " << coste << endl;
        for (int j = 0; j < 3; j++)
        {
            if (pesos[j] == peso || v[0] == 1)
            {
                return;
            }
        }
        Operacion *op = new Operacion(v, n);
        for (int j = 0; j < 4; ++j) {
            cout << op->op[j] << " ";
        }
        cout << endl;
        ops[count] = op;
        ++count; 
        return;
    }

    v[i] = 0; // generamos la combinación con un 0 en la posición i
    generarCombinaciones(v, i + 1, n, coste, count);

    v[i] = 1; // generamos la combinación con un 1 en la posición i
    ++coste;
    generarCombinaciones(v, i + 1, n, coste, count);
}

int main(int argc, char const *argv[])
{
    int a[4] = {1, 1, 1, 1};

    generarCombinaciones(a, 0, 4, 0, 0);

    cout << "Lectura de ops: " << endl;

    for (int i = 0; i < largo; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << ops[i]->op[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
