#include "CrossingRiver.h"
#include "Load.h"

using namespace std;

int main()
{
    Load *fileReader = new Load("test.txt");

    int *info = fileReader->readInfo();

    int N = info[0] + info[1];

    int resIzq = fileReader->readRes();
    int **restriccionesIzq = fileReader->loadMatrix(resIzq, N);

    int resDer = fileReader->readRes();
    int **restriccionesDer = fileReader->loadMatrix(resDer, N);

    // cerrar el archivo
    fileReader->~Load();

    CrossingRiver *lcr = new CrossingRiver(
        info[0], info[1], info[2],
        resIzq, restriccionesIzq, resDer, restriccionesDer);
    lcr->solve();
    delete lcr;
    return 0;
}