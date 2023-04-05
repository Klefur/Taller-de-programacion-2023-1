#include "CrossingRiver.h"
#include "Load.h"

CrossingRiver::CrossingRiver(const char *name)
{
    Load *fileReader = new Load("test.txt");

    int *info = fileReader->readInfo();

    this->farmers = info[0];
    this->items = info[1];
    this->boatSize = info[2];
    this->boatLeft = true;
    this->largoOps = 0;

    int N = info[0] + info[1];

    this->ops = new Operacion *[1 << N];

    this->cantidadIzquierda = fileReader->readRestriccion();
    int **matrizIzquierda = fileReader->loadMatrix(this->cantidadIzquierda, N);

    this->restriccionIzquierda = new int[this->cantidadIzquierda];
    for (int i = 0; i < this->cantidadIzquierda; ++i)
    {
        this->restriccionIzquierda[i] = this->binaryToDecimal(matrizIzquierda[i], N);
    }

    this->cantidadDerecha = fileReader->readRestriccion();
    int **matrizDerecha = fileReader->loadMatrix(this->cantidadDerecha, N);

    this->restriccionDerecha = new int[this->cantidadDerecha];
    for (int i = 0; i < this->cantidadDerecha; ++i)
    {
        this->restriccionDerecha[i] = this->binaryToDecimal(matrizDerecha[i], N);
    }

    // cerrar el archivo
    fileReader->~Load();

    this->open = new Stack(1000);
    this->closed = new Stack(1000);
}

CrossingRiver::~CrossingRiver()
{
    delete this->open;
    delete this->closed;
}

void CrossingRiver::solve()
{
    int largo = this->farmers + this->items;
    State *inicial = new State(largo); // new llama al constructor y entrega un puntero
    generarCombinaciones(inicial->left, 0, largo, 0);
    cout << "EMPIEZA EL ALGORITMO" << endl;
    open->push(inicial);
    while (!open->isEmpty())
    {
        State *s = open->pop();
        if (s->isFinal(largo))
        {
            cout << "Solucion encontrada" << endl;
            s->printPath(largo);
            return;
        }
        closed->push(s);
        for (int i = 0; i < 1 << largo; ++i)
        {
            if (canMove(s, ops[i]))
            {
                cout << "Puedo mover " << i << endl;
                s->print(largo);
                State *s1 = move(s, ops[i]);
                cout << "quedando:" << endl;
                s1->print(largo);
                if (!closed->search(s1) && !open->search(s1))
                    open->push(s1);
                else
                {
                    cout << "No se agrega " << i << endl;
                    delete s1;
                }
            }
        }

    } // while
    cout << "No hay solucion" << endl;
}

State *CrossingRiver::move(State *s, Operacion *op)
{
    int largo = this->farmers + this->items;
    int left[largo];
    int right[largo];
    // copiar los arreglos
    for (int i = 0; i < largo; i++)
    {
        left[i] = op->op[i];
        if (op->op[i] == 1)
        {
            right[i] = 0;
        }
        else
        {
            right[i] = 1;
        }
    }

    return new State(left, right, s, largo, op->coste);
}

bool CrossingRiver::canMove(State *s, Operacion *op)
{
    // TODO GENERA MOVIMIENTOS DE S, COMPARA CON OP
    // TODO COMPARA LOS 0 DE CONDUCTORES Y DE ITEMS VE QUE SE MUEVE LA MISMA CANTIDAD DE ESPACIO DEL BOTE
    // TODO AGREGAR DISCRIMINACION DONDE SE MUEVE AL MENOS 1 CONDUCTOR, EL BOTE ESTA DEL LADO CORRECTO
    int count = 0;

    for (int i = 0; i < this->farmers; ++i)
    {
        if (s->left[i] == op->op[i])
        {
            count++;
        }
    }

    cout << count << endl;

    if (count > this->boatSize)
    {
        return false;
    } // Se verifica que se muevan la misma cantidad que el espacio del bote

    return true;
}

void CrossingRiver::generarCombinaciones(int v[], int i, int n, int coste)
{
    if (i == n)
    { // caso base: si hemos llegado al final del arreglo
        int peso = binaryToDecimal(v, i);

        ops[this->largoOps] = new Operacion(v, n, coste, peso);
        ++this->largoOps;

        return;
    }

    v[i] = 0; // generamos la combinación con un 0 en la posición i
    generarCombinaciones(v, i + 1, n, coste);

    v[i] = 1; // generamos la combinación con un 1 en la posición i
    ++coste;
    generarCombinaciones(v, i + 1, n, coste);
}

int CrossingRiver::binaryToDecimal(int binaryArray[], int arraySize)
{
    int decimalValue = 0;

    for (int i = 0; i < arraySize; i++)
    {
        decimalValue = (decimalValue << 1) + binaryArray[i];
    }

    return decimalValue;
}