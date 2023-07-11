#include "Node.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Node *n = new Node(new Simplex("sistema.txt"));
    n->s->solve();
    cout << n->s->upperBound[0] << endl;    
    
    return 0;
}
