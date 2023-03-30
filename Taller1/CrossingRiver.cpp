#include "CrossingRiver.h"

CrossingRiver::CrossingRiver(
    int farmers,
    int items,
    int boatSize,
    int cantidadIzquierda,
    int *restriccionIzquierda[],
    int cantidadDerecha,
    int *restriccionDerecha[])
{
    this->farmers = farmers;
    this->items = items;
    this->boatSize = boatSize;
    this->restriccionIzquierda = restriccionIzquierda;
    this->cantidadIzquierda = cantidadIzquierda;
    this->cantidadDerecha = cantidadDerecha;
    this->restriccionDerecha = restriccionDerecha;
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

        for (int i = 1; i < largo; ++i)
        {
            cout << i << endl;
            if (canMove(s, i))
            {
                cout << "Puedo mover " << i << endl;
                s->print(largo);
                State *s1 = move(s, i);
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

        cout << 0 << endl;
        if (canMove(s, 0))
        {
            cout << "Puedo mover G" << endl;
            s->print(largo);
            State *s1 = move(s, 0);
            cout << "quedando:" << endl;
            s1->print(largo);
            if (!closed->search(s1) && !open->search(s1))
                open->push(s1);
            else
            {
                cout << "No se agrega G" << endl;
                delete s1;
            }
        }

    } // while
    cout << "No hay solucion" << endl;
}

State *CrossingRiver::move(State *s, int item)
{
    int largo = this->farmers + this->items;
    int left[largo];
    int right[largo];
    // copiar los arreglos
    for (int i = 0; i < largo; i++)
    {
        left[i] = s->left[i];
        right[i] = s->right[i];
    }

    if (item != 0)
    {
        if (left[item] == 1)
        {
            left[item] = 0;
            right[item] = 1;
            left[0] = 0;
            right[0] = 1;
        }
        else
        {
            left[item] = 1;
            right[item] = 0;
            left[0] = 1;
            right[0] = 0;
        }
        return new State(left, right, s, largo);
    }

    if (left[0] == 1)
    {
        left[0] = 0;
        right[0] = 1;
    }
    else
    {
        left[0] = 1;
        right[0] = 0;
    }

    return new State(left, right, s, largo);
}

bool CrossingRiver::canMove(State *s, int item)
{
    return (checkMatrix(s->left, item, this->restriccionIzquierda, this->cantidadIzquierda) ||
        checkMatrix(s->right, item, this->restriccionDerecha, this->cantidadDerecha));
}

bool CrossingRiver::checkMatrix(int arr[], int item, int *matrix[], int cantidad)
{
    int largo = this->farmers + this->items;
    int *temp = new int[largo];

    if (arr[0] == 0 || arr[item] == 0) // caso onde el granjero no esta o no esta el item
    {
        return false;
    }

    for (int i = 0; i < largo; ++i) // se copia el arreglo
    {
        if (i == item)
        {
            temp[item] = 0;
            temp[0] = 0;
        }
        else
        {
            temp[i] = arr[i];
        }
    }

    for (int i = 0; i < cantidad; ++i) // se revisa la matriz
    {
        if (arraysEqual(matrix[i], temp, largo))
        {
            return false;
        }
    }

    return true;
}

bool CrossingRiver::arraysEqual(int a[], int b[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}