#include "CrossingRiver.h"
#include "Load.h"

// Entrada: El nombre del sistema a solucionar
// Salida: -
// Funcionamiento: Carga el archivo de entrada y genera las combinaciones de movimientos
CrossingRiver::CrossingRiver(const char *name)
{
    Load *fileReader = new Load(name);

    int *info = fileReader->readInfo();

    this->farmers = info[0];
    this->items = info[1];
    this->boatSize = info[2];
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
    
    int largo = this->farmers + this->items;
    State *inicial = new State(largo);
    generarCombinaciones(inicial->left, 0, largo);
    delete inicial;

    this->open = new Stack(1 << N);
    this->closed = new Stack(1 << N);
}

// Entrada: -
// Salida: -
// Funcionamiento: Destructor de la clase
CrossingRiver::~CrossingRiver()
{
    delete this->open;
    delete this->closed;
}

// Entrada: -
// Salida: -
// Funcionamiento: Itera sobre el arreglo de operaciones hasta encontrar la solucion o
//                 hasta que no queden estados en open
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
            // cout << "Solucion encontrada" << endl;
            // s->printPath(largo);
            return;
        }
        closed->push(s);
        for (int i = 0; i < 1 << largo; ++i)
        {
            if (canMove(s, ops[i]))
            {
                // cout << "Puedo aplicar op: " << i << endl;
                // s->print(largo);
                State *s1 = move(s, ops[i]);
                // cout << "quedando:" << endl;
                // s1->print(largo);
                if (!closed->search(s1) && !open->search(s1))
                    open->push(s1);
                else
                {
                    // cout << "No se aplica op: " << i << endl;
                    delete s1;
                }
            }
        }

    } // while
    cout << "No hay solucion" << endl;
}

// Entrada: Un puntero a estado s y un puntero a una operacion op
// Salida: Un puntero a estado
// Funcionamiento: Aplica la operacion op al estado s y retorna el nuevo estado
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

    return new State(left, right, s, largo, op->peso, !s->boatIsLeft);
}

// Entrada: Un puntero a estado s y un puntero a una operacion op
// Salida: Un booleano
// Funcionamiento: Revisa si se puede aplicar la operacion op al estado s
bool CrossingRiver::canMove(State *s, Operacion *op)
{
    int countMove = 0;
    int countFarmMove = 0;
    int moveToRight = 0;
    int moveToLeft = 0;
    int largo = this->farmers + this->items;

    for (int i = 0; i < this->cantidadIzquierda; ++i)
    {
        if (this->restriccionIzquierda[i] == op->peso)
        {
            return false;
        }
    }

    for (int i = 0; i < this->cantidadDerecha; ++i)
    {
        if (this->restriccionDerecha[i] == (1 << largo) - 1 - op->peso)
        {
            return false;
        }
    }

    for (int i = 0; i < this->farmers; ++i)
    {
        if (s->left[i] != op->op[i])
        {
            countMove++;
            countFarmMove++;
            if (s->left[i] == 1 && op->op[i] == 0)
            {
                moveToRight++;
            }
            else
            {
                moveToLeft++;
            }
        }
    }

    for (int i = this->farmers; i < this->items + this->farmers; ++i)
    {
        if (s->left[i] != op->op[i])
        {
            countMove++;

            if (s->left[i] == 1 && op->op[i] == 0)
            {
                moveToRight++;
            }
            else
            {
                moveToLeft++;
            }
        }
    }

    if (countMove > this->boatSize || countFarmMove == 0)
    {
        return false;
    } // Se verifica que se muevan la misma cantidad que el espacio del bote
      // y que se mueva al menos 1 conductor

    if (moveToRight > 0 && s->boatIsLeft && moveToLeft == 0)
    {
        return true;
    } // Se verifica que se muevan solo cosas hacia la derecha y el bote este en la izquierda
    else if (moveToRight == 0 && !s->boatIsLeft && moveToLeft > 0)
    {
        return true;
    } // Se verifica que se muevan solo cosas hacia la izquierda y el bote este en la derecha

    return false;
}

// Entrada: Un arreglo de enteros v, un entero i: indice y un entero n: largo
// Salida: -
// Funcionamiento: Genera todas las combinaciones posibles de 0 y 1 en un arreglo de largo n
//                 y las guarda en el arreglo de operaciones
void CrossingRiver::generarCombinaciones(int v[], int i, int n)
{
    if (i == n)
    { // caso base: si hemos llegado al final del arreglo
        int peso = binaryToDecimal(v, i);

        ops[this->largoOps] = new Operacion(v, n, peso);
        ++this->largoOps;

        return;
    }

    v[i] = 0; // generamos la combinación con un 0 en la posición i
    generarCombinaciones(v, i + 1, n);

    v[i] = 1; // generamos la combinación con un 1 en la posición i
    generarCombinaciones(v, i + 1, n);
}

// Entrada: Un arreglo de enteros binarios y un entero que representa el largo del arreglo
// Salida: Un entero que representa el valor decimal del arreglo binario
// Funcionamiento: Convierte un arreglo binario a un entero decimal
int CrossingRiver::binaryToDecimal(int binaryArray[], int arraySize)
{
    int decimalValue = 0;

    for (int i = 0; i < arraySize; i++)
    {
        decimalValue = (decimalValue << 1) + binaryArray[i];
    }

    return decimalValue;
}