#include "CrossingRiver.h"
#include "Load.h"

CrossingRiver::CrossingRiver(const char *name)
{
    Load *fileReader = new Load("test.txt");

    int *info = fileReader->readInfo();

    this->farmers = info[0];
    this->items = info[1];
    this->boatSize = info[2];

    int N = info[0] + info[1];

    this->cantidadIzquierda = fileReader->readRes();

    int **matrizIzquierda = fileReader->loadMatrix(this->cantidadIzquierda, N);
    this->restriccionIzquierda = new int[this->cantidadIzquierda];

    for (int i = 0; i < this->cantidadIzquierda; ++i)
    {
        this->restriccionIzquierda[i] = this->binaryToDecimal(matrizIzquierda[i], N);
    }

    this->cantidadDerecha = fileReader->readRes();

    int **matrizDerecha = fileReader->loadMatrix(this->cantidadDerecha, N);
    this->restriccionDerecha = new int[this->cantidadDerecha];

    for (int i = 0; i < this->cantidadDerecha; ++i)
    {
        this->restriccionDerecha[i] = this->binaryToDecimal(matrizDerecha[i], N);
        cout << this->restriccionDerecha[i] << endl;
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
    // return (checkMatrix(s->left, item, this->restriccionIzquierda, this->cantidadIzquierda) ||
    //        checkMatrix(s->right, item, this->restriccionDerecha, this->cantidadDerecha));
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