#include <ctime>

#include "BB.h"

using namespace std;

int main(int argc, char const* argv[]) {
    BB* solve = new BB();
    string namefile;
    clock_t start, end;
    int veces;
    double secs = 0;

    cout << "Ingrese el nombre del archivo: ";
    cin >> namefile;

    cout << "Ingrese cuantas veces quiere que se resuelva: ";
    cin >> veces;

    for (int i = 0; i < veces; i++) {
        start = clock();
        solve = new BB();
        // La funcion tiene los cout comentados por los problemas grandes que quedan ilegibles
        solve->solve(namefile);
        end = clock();
        secs += (double)(end - start) / CLOCKS_PER_SEC;
    }

    solve->printFinalSolution();
    cout << "Cantidad de nodos revisados: " << solve->cantidadNodos << endl;
    cout << "Tiempo de ejecucion promedio: " << secs / veces << " segundos" << endl;

    return 0;
}