#include "CrossingRiver.h"
#include "Load.h"

using namespace std;

int main()
{
    CrossingRiver *lcr = new CrossingRiver("test2.txt");

    lcr->solve();
    delete lcr;
    return 0;
}