#include "Stack.h"
using namespace std;

int main()
{
    int left[4] = {1, 1, 1, 1};
    int right[4] = {0, 0, 0, 0};

    Stack *stack = new Stack(2);

    for (int i = 0; i < 10; i++)
    {
        left[0] = i;
        State *s = new State(left, right, nullptr, 4, (1 << i) - 1); // new llama al constructor y entrega un puntero
        stack->push(s);
    }

    stack->print(4);

    return 0;
}