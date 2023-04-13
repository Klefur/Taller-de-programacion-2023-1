#include "State.h"
using namespace std;

int main()
{
    State s1 = State(4);
    State s2 = State(10);
    State s3 = State(3);

    s1.print(4);
    s2.print(10);
    s3.print(3);

    cout << "Coste de s1: " << s1.coste << endl;
    cout << "Coste de s2: " << s2.coste << endl;
    cout << "Coste de s3: " << s3.coste << endl;

    return 0;
}