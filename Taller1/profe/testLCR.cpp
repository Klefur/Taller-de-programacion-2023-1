#include "LCR.h"


int main() {
    LCR *lcr = new LCR();
    lcr->solve();
    delete lcr;
    return 0;
}