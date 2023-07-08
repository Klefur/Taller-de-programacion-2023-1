#include <cmath>

#include "Simplex.h"

using namespace std;

float numeroMasFraccional(vector<float> numeros, int longitud) {
    float fraccionMaxima = modf(numeros[1], &fraccionMaxima);
    int indiceMaximo = 1;

    for (int i = 2; i < longitud; i++) {
        float fraccionActual = modf(numeros[i], &fraccionActual);

        if (fraccionActual > fraccionMaxima) {
            fraccionMaxima = fraccionActual;
            indiceMaximo = i;
        }
    }

    return indiceMaximo;
}

int main(int argc, char const* argv[]) {
    Simplex* simplex1 = new Simplex("sistema.txt");

    vector<float> par1 = simplex1->solve();
    simplex1->printProblemMatrix();
    simplex1->solveLB();
    cout << "Solucion: " << endl;

    for (int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;

    int flag = 1;

    while (flag) {
        // retorna [Z,x1,...,xn] sino []
        int indexFrac = numeroMasFraccional(par1, par1.size());

        Simplex* simplex2 = simplex1->copy();
        Simplex* simplex3 = simplex1->copy();

        cout << "Insertando restricciones x" << indexFrac
             << " >= " << int(par1[indexFrac] + 1) << endl;
        simplex2->insertConstraint(int(par1[indexFrac] + 1), indexFrac, 2);
        vector<float> par2 = simplex2->solve();
        simplex2->printProblemMatrix();
        simplex2->solveLB();
        if (par2.size() == 0) {
            cout << "No hay solucion" << endl;
            par2.push_back(0);
        } else {
            cout << "Solucion: " << endl;
            for (int i = 0; i < par2.size(); i++) {
                cout << par2[i] << " ";
            }
            cout << endl;
        }

        cout << "Insertando restricciones x" << indexFrac
             << " <= " << int(par1[indexFrac]) << endl;
        simplex3->insertConstraint(int(par1[indexFrac]), indexFrac, 1);
        vector<float> par3 = simplex3->solve();
        simplex3->printProblemMatrix();
        simplex3->solveLB();
        if (par3.size() == 0) {
            cout << "No hay solucion" << endl;
            par3.push_back(0);
        } else {
            cout << "Solucion: " << endl;
            for (int i = 0; i < par3.size(); i++) {
                cout << par3[i] << " ";
            }
            cout << endl;
        }

        if (simplex1->lowerBound > par2[0] && simplex1->lowerBound > par3[0]) {
            flag = 0;
            cout << "Solucion: " << endl;
            for (int i = 0; i < par1.size(); i++) {
                cout << par1[i] << " ";
            }
            cout << endl;
        } else if (par2[0] > simplex1->lowerBound && par2[0] > par3[0]) {
            cout << "Se elige el simplex 2" << endl;
            simplex1 = simplex2->copy();
            par1 = par2;
        } else if (par3[0] > simplex1->lowerBound && par3[0] > par2[0]) {
            cout << "Se elige el simplex 3" << endl;
            simplex1 = simplex3->copy();
            par1 = par3;
        } else if (simplex1->lowerBound == par2[0]) {
            flag = 0;
            cout << "Solucion: " << endl;
            for (int i = 0; i < par2.size(); i++) {
                cout << par2[i] << " ";
            }
            cout << endl;
        } else if (simplex1->lowerBound == par3[0]) {
            flag = 0;
            cout << "Solucion: " << endl;
            for (int i = 0; i < par3.size(); i++) {
                cout << par3[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
