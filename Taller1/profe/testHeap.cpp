#include "Heap.h"
#include <cstdlib>

int main() {
    Heap h(10);
    cout << "capacity:"<< h.capacity << endl;
    cout << "size:"<<h.size << endl;

    int left[4] = {0,0,0,0  };
    int right[4] = {0,0,0,0};

    for (int i = 0; i < 40; i++) {
        State *s = new State(left,right,nullptr);
        s->value = rand()%40;
        cout <<"inserting:"<< s->value << endl;
        h.push(s);
    }
    cout<<"Now we extract all the elements from the heap: "<<endl;
    for (int i = 0; i < 42; i++) {
        State *s = h.pop();
        if (s != nullptr) {
            cout << s->value << endl;
        } else {
            cout << "nullptr" << endl;
        }
    }

    return 0;
}