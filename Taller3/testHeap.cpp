#include <cstdlib>
#include "Heap.h"

using namespace std;

int main() {
    Heap h(10);
    cout << "capacity:" << h.capacity << endl;
    cout << "size:" << h.size << endl;

    int left[4] = {0, 0, 0, 0};
    int right[4] = {0, 0, 0, 0};

    for (int i = 0; i < 40; i++) {
        cout << "inserting:" << i << endl;
        Simplex *s = new Simplex("sistema.txt");
        s->solve();
        s->upperBound[0] += i;
        Node* n = new Node(s);
        cout << "inserting:" << n->upperBound[0] << endl;
        h.push(n);
    }
    cout << "Now we extract all the elements from the heap: " << endl;
    for (int i = 0; i < 42; i++) {
        Node* s = h.pop(0);
        if (s != nullptr) {
            cout << s->upperBound[0] << endl;
        } else {
            cout << "nullptr" << endl;
        }
    }

    return 0;
}