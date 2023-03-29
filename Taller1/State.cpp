#include "State.h"

State::State(int largo)
{
    this->left = new int[largo];
    this->right = new int[largo];
    for (int i = 0; i < largo; i++)
    {
        this->left[i] = 1;  // todos a la izquierda
        this->right[i] = 0; // nada a la derecha
    }
    previous = nullptr;
}

State::State(int left[], int right[], State *previous, int largo)
{
    this->left = new int[largo];
    this->right = new int[largo];

    for (int i = 0; i < largo; i++)
    {
        this->left[i] = left[i];
        this->right[i] = right[i];
    }
    this->previous = previous;
}

State::~State()
{
    // no se necesita
}

void State::print(int largo)
{
    cout << "Izquierda: ";
    for (int i = 0; i < largo; i++)
    {
        cout << this->left[i] << " ";
    }
    cout << endl;
    cout << "Derecha: ";
    for (int i = 0; i < largo; i++)
    {
        cout << this->right[i] << " ";
    }
    cout << endl;
}

// asumimos que no hay contradicciones
bool State::isFinal(int largo)
{
    for (int i = 0; i < largo; i++)
    {
        if (this->right[i] == 0)
        {
            return false;
        }
    }
    return true;
}

void State::printPath(int largo)
{
    State *actual = this; // this es puntero al objeto actual
    actual->print(largo);
    while (actual->previous != nullptr)
    {
        actual = actual->previous;
        actual->print(largo);
    }
}