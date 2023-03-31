#include "CrossingRiver.h"
#include "Load.h"

using namespace std;

int main()
{
    CrossingRiver *lcr = new CrossingRiver("test.txt");

    cout << lcr->farmers << lcr->items << lcr->boatSize << endl;

    cout << lcr->cantidadIzquierda << endl;

    cout << lcr->cantidadDerecha << endl;

    //lcr->solve();
    delete lcr;
    return 0;
}