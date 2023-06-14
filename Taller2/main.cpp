#include <iostream>
#include <stack>

using namespace std;

void add1(stack<int>* a) {
    a->push(1);
}

int main(int argc, char const* argv[]) {
    stack<int> a;
    add1(&a);
    add1(&a);
    add1(&a);
    cout << a.size() << endl;
    return 0;
}
