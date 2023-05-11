#include "Stack.h"

// Entrada: El tamaño del stack
// Salida: -
// Funcionamiento: Constructor de la clase
Stack::Stack(int size)
{
    this->size = size;
    top = -1;
    stack = new State *[size]; // crea arreglo de tamaño size
}

// Entrada: -
// Salida: -
// Funcionamiento: Destructor de la clase
Stack::~Stack()
{
    delete[] stack;
}

// Entrada: Un estado
// Salida: -
// Funcionamiento: Agrega un estado al stack
void Stack::push(State *s)
{
    if (top < size - 1)
    {
        top++;
        stack[top] = s;
    }
    else
    {
        cout << "Stack overflow" << endl;
        State **tmp = new State *[2 * size];
        for (int i = 0; i < size; i++)
        {
            tmp[i] = stack[i];
        }
        delete[] stack;
        stack = tmp;
        this->size = 2 * size;
        push(s);
    }
}

// Entrada: -
// Salida: Un estado
// Funcionamiento: Saca un estado del stack y lo retorna
State *Stack::pop()
{
    if (top >= 0)
    {
        State *s = stack[top];
        top--;
        return s;
    }
    else
    { // caso vacio
        cout << "Stack underflow" << endl;
        return nullptr;
    }
}

// Entrada: Un estado
// Salida: Un booleano
// Funcionamiento: Busca un estado en el stack y retorna true si lo encuentra, false sino
bool Stack::search(State *s)
{
    bool equal = false;
    for (int i = 0; i <= top; i++)
    {
        equal = true;

        if (stack[i]->coste != s->coste || stack[i]->boatIsLeft != s->boatIsLeft)
        {
            equal = false;
        }

        if (equal)
        {
            return true;
        }
    }
    return false;
}

// Entrada: -
// Salida: Un booleano
// Funcionamiento: Retorna true si el stack esta vacio, false sino
bool Stack::isEmpty()
{
    return top == -1;
}

// Entrada: Un entero
// Salida: -
// Funcionamiento: Imprime el stack
void Stack::print(int largo)
{
    for (int i = 0; i <= top; i++)
    {
        stack[i]->print(largo);
    }
}