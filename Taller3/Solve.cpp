#include "Solve.h"

using namespace std;

Solve::Solve() {}

Solve::~Solve() {}

void Solve::resolve(string namefile) {
    Simplex* simplex1 = new Simplex("sistema.txt");

    vector<float> par1 = simplex1->solve();
    simplex1->printProblemMatrix();
    simplex1->solveLB();
    cout << "Solucion: " << endl;

    for (int i = 0; i < par1.size(); i++) {
        cout << par1[i] << " ";
    }
    cout << endl;

    if (simplex1->intVars.size() == 0) {
        return;
    }

    cout << "LB: ";
    for (float i : simplex1->lowerBound) {
        cout << i << " ";
    }
    cout << endl << endl;

    int flag = 1;
    while (flag) {
        // retorna [Z,x1,...,xn] sino []
        int indexFrac = moreFracctional(par1, par1.size(), simplex1->intVars);

        Simplex* simplex2 = simplex1->copy();
        Simplex* simplex3 = simplex1->copy();

        cout << "Insertando restricciones x" << indexFrac
             << " >= " << int(par1[indexFrac] + 1) << endl;
        simplex2->insertConstraint(int(par1[indexFrac] + 1), indexFrac, 2);
        vector<float> par2 = simplex2->solve();
        simplex2->printProblemMatrix();
        simplex2->solveLB();
        if (par2.size() == 0) {
            cout << "No hay solucion" << endl << endl;
            par2.push_back(0);
        } else {
            cout << "Solucion: " << endl;
            for (int i = 0; i < par2.size(); i++) {
                cout << par2[i] << " ";
            }
            cout << endl;
            cout << "LB: ";
            for (float i : simplex2->lowerBound) {
                cout << i << " ";
            }
            cout << endl << endl;
        }

        cout << "Insertando restricciones x" << indexFrac
             << " <= " << int(par1[indexFrac]) << endl;
        simplex3->insertConstraint(int(par1[indexFrac]), indexFrac, 1);
        vector<float> par3 = simplex3->solve();
        simplex3->printProblemMatrix();
        simplex3->solveLB();
        if (par3.size() == 0) {
            cout << "No hay solucion" << endl << endl;
            par3.push_back(0);
        } else {
            cout << "Solucion: " << endl;
            for (int i = 0; i < par3.size(); i++) {
                cout << par3[i] << " ";
            }
            cout << endl;
            cout << "LB: ";
            for (float i : simplex3->lowerBound) {
                cout << i << " ";
            }
            cout << endl << endl;
        }

        if (simplex1->lowerBound[0] > par2[0] &&
            simplex1->lowerBound[0] > par3[0]) {
            flag = 0;
            cout << "Solucion Final: " << endl;
            for (float i : simplex1->lowerBound) {
                cout << i << " ";
            }
            cout << endl;
        } else if (par2[0] > simplex1->lowerBound[0] && par2[0] > par3[0]) {
            cout << "Se elige simplex x" << indexFrac
             << " >= " << int(par1[indexFrac]) + 1 << endl;
            simplex1 = simplex2->copy();
            par1 = par2;
            cout << endl;
        } else if (par3[0] > simplex1->lowerBound[0] && par3[0] > par2[0]) {
            cout << "Se elige simplex x" << indexFrac
                 << " <= " << int(par1[indexFrac]) << endl;
            simplex1 = simplex3->copy();
            cout << endl;
            par1 = par3;
        } else if (0 <= (par2[0] - simplex1->lowerBound[0]) &&
                   (par2[0] - simplex1->lowerBound[0]) < EPS) {
            flag = 0;
            cout << "Solucion Final: " << endl;
            for (int i = 0; i < par2.size(); i++) {
                cout << par2[i] << " ";
            }
            cout << endl;
        } else if (0 <= (par3[0] - simplex1->lowerBound[0]) &&
                   (par3[0] - simplex1->lowerBound[0]) < EPS) {
            flag = 0;
            cout << "Solucion Final: " << endl;
            for (int i = 0; i < par3.size(); i++) {
                cout << par3[i] << " ";
            }
            cout << endl;
        }
    }
}

int Solve::moreFracctional(vector<float> numeros,
                           int longitud,
                           vector<int> indices) {
    float fraccionMaxima = 0.6;
    int indiceMaximo = 1;
    float fraccionActual;
    if (indices.size() > 1) {
        for (int i : indices) {
            fraccionActual = modf(numeros[i], &fraccionActual);
            fraccionActual =
                fraccionActual - LOGIC_ONE >= 0 ? 0 : fraccionActual;

            fraccionActual = abs(fraccionActual - 0.5);

            if (fraccionActual < fraccionMaxima) {
                fraccionMaxima = fraccionActual;
                indiceMaximo = i;
            }
        }
    }
    return indiceMaximo;
}