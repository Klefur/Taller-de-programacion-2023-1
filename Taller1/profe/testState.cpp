#include "State.h"

int main() {
    int left[4] = {1, 1, 1, 1};
    int right[4] = {0, 0, 0, 0};
    State *s = new State(left, right, nullptr); // new llama al constructor y entrega un puntero
    right[0]=1;
    right[1]=1;
    State *s1 = new State(left, right, s);

    s->print();
    s1->print(); 

    s1->printPath();   
    delete s;
    return 0;
} 