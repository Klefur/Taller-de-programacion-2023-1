#include "BB.h"

using namespace std;

BB::BB() {
    this->noVisited = new Heap(2);
    this->visited = new Heap(2);
    this->solutions = new Heap(2);
}

BB::~BB() {}

int BB::isSolution(Node* node) {
    vector<float> upperBound = node->s->upperBound;
    vector<int> intVars = node->s->intVars;

    if (upperBound.size() == 0) {
        return 0;
    }

    for (int i : intVars) {
        if (upperBound[i] != int(upperBound[i])) {
            return 0;
        } else {
            node->s->upperBound[i] = abs(upperBound[i]);
        }
    }

    return 1;
}

void BB::solve(string namefile) {
    Simplex* s = new Simplex("sistema.txt");

    s->solve();

    s->printProblemMatrix();
    s->printUpperBound();

    if (s->intVars.size() == 0) {
        return;
    }

    s->solveLB();
    s->printLowerBound();

    this->noVisited->push(new Node(s));

    while (this->noVisited->size > 0) {
        Node* node = this->noVisited->pop();
        this->visited->push(node);

        s = node->s;
        int indexFrac = moreFracctional(s->upperBound, s->intVars);

        Simplex* sIzq = s->copy();
        Simplex* sDer = s->copy();

        cout << "Insertando restricciones x" << indexFrac
             << " <= " << int(s->upperBound[indexFrac] + 1) << endl;
        sIzq->insertConstraint(int(s->upperBound[indexFrac]), indexFrac, 1);
        sIzq->printProblemMatrix();
        sIzq->solve();
        sIzq->printUpperBound();
        sIzq->solveLB();
        sIzq->printLowerBound();

        cout << "Insertando restricciones x" << indexFrac
             << " >= " << int(s->upperBound[indexFrac] + 1) << endl;
        sDer->insertConstraint(int(s->upperBound[indexFrac] + 1), indexFrac, 2);
        sDer->printProblemMatrix();
        sDer->solve();
        sDer->printUpperBound();
        sDer->solveLB();
        sDer->printLowerBound();

        if (s->lowerBound[0] > sIzq->upperBound[0] &&
            s->lowerBound[0] > sDer->upperBound[0]) {
            Node* nSol = new Node(s->lowerBound);

            cout << "Insertando solucion" << endl;
            if (!solutions->isInHeap(nSol))
                solutions->push(nSol);
        } else {
            if (isSolution(new Node(sIzq))) {
                Node* nSolIzq = new Node(sIzq->upperBound);

                cout << "Insertando solucion Izq" << endl;
                if (!solutions->isInHeap(nSolIzq))
                    solutions->push(nSolIzq);
            }
            if (isSolution(new Node(sDer))) {
                Node* nSolDer = new Node(sDer->upperBound);

                cout << "Insertando solucion Der" << endl;
                if (!solutions->isInHeap(nSolDer))
                    solutions->push(nSolDer);
            }
        }

        if (sIzq->upperBound[0] > s->lowerBound[0]) {
            Node* nIzq = new Node(sIzq);

            cout << "Insertando Nodo Izq " << endl;
            if (!visited->isInHeap(nIzq))
                noVisited->push(nIzq);
        } else {
            this->visited->push(new Node(sIzq));
        }

        if (sDer->upperBound[0] > s->lowerBound[0]) {
            Node* nDer = new Node(sDer);

            cout << "Insertando Nodo Der " << endl << endl;
            if (!visited->isInHeap(nDer))
                noVisited->push(nDer);
        } else {
            this->visited->push(new Node(sDer));
        }
    }

    cout << "Solucion Final:" << endl;

    Node* node = solutions->pop();

    for (float i : node->upperBound) {
        cout << i << " ";
    }
    cout << endl;
}

int BB::moreFracctional(vector<float> numeros, vector<int> indices) {
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