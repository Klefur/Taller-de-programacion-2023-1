#include "Load.h"

using namespace std;

int main()
{
    Load *fileReader = new Load("test.txt");

    int *info = fileReader->readInfo();

    int N = info[0] + info[1];

    int resIzq = fileReader->readRestriccion();
    int **restriccionesIzq = fileReader->loadMatrix(resIzq, N);

    int resDer = fileReader->readRestriccion();
    int **restriccionesDer = fileReader->loadMatrix(resDer, N);

    // cerrar el archivo
    fileReader->~Load();
    // veamos como quedan las matrices

    cout << "restriccionesIzq:" << endl;
    for (int i = 0; i < resIzq; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << restriccionesIzq[i][j] << " ";
        }
        cout << endl;
    }

    cout << "restriccionesDer:" << endl;
    for (int i = 0; i < resDer; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << restriccionesDer[i][j] << " ";
        }
        cout << endl;
    }
}