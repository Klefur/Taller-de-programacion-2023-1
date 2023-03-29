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

        // if (canMove(s, 1))
        // {
        //     cout << "Puedo mover L de:" << endl;
        //     s->print(largo);
        //     State *s1 = move(s, 1);
        //     cout << "quedando:" << endl;
        //     s1->print(largo);
        //     if (!closed->search(s1) && !open->search(s1))
        //         open->push(s1);
        //     else
        //     {
        //         cout << "No se agrega L" << endl;
        //         delete s1;
        //     }
        // }

        // if (canMove(s, 2))
        // {
        //     cout << "Puedo mover C" << endl;
        //     s->print(largo);
        //     State *s1 = move(s, 2);
        //     cout << "quedando:" << endl;
        //     s1->print(largo);
        //     if (!closed->search(s1) && !open->search(s1))
        //         open->push(s1);
        //     else
        //     {
        //         cout << "No se agrega C" << endl;
        //         delete s1;
        //     }
        // }

        // if (canMove(s, 3))
        // {
        //     cout << "Puedo mover R" << endl;
        //     s->print(largo);
        //     State *s1 = move(s, 3);
        //     cout << "quedando:" << endl;
        //     s1->print(largo);
        //     if (!closed->search(s1) && !open->search(s1))
        //         open->push(s1);
        //     else
        //     {
        //         cout << "No se agrega R" << endl;
        //         delete s1;
        //     }
        // }

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
    if (checkMatrix(s->left, item, this->restriccionIzquierda, this->cantidadIzquierda) ||
        checkMatrix(s->right, item, this->restriccionDerecha, this->cantidadDerecha))
    {
        return true;
    }
    return false;
}

bool CrossingRiver::checkMatrix(int arr[], int item, int *matrix[], int cantidad)
{
    int largo = this->farmers + this->items;
    int *temp = new int[largo];
    int cont;

    if (arr[0] == 0 || arr[item] == 0) // caso onde el granjero no esta o no esta el item
    {
        return false;
    }
    if (arr[item] == 1 && item == 0) // caso de mover el granjero solo
    {
        return true;
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
        if (matrix[i][item] == temp[item])
        {
            cont = 0;
            for (int j = 0; j < largo; ++j)
            {
                if (matrix[i][j] != temp[j])
                {
                    j = largo;
                }
                else if (matrix[i][j] == 1 && temp[j] == 1) // TODO: HACER QUE ESTA WEA FUNCIONE CTM AAAAH
                {
                    cont += 1;
                }
                if (cont >= 2)
                {
                    return false;
                }
            }
        }
    }

    return true;
}