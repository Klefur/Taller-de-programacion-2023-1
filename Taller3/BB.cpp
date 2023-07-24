#include "BB.h"

using namespace std;

/**
 * @brief Constructor de la clase BB
 */
BB::BB() {
    this->noVisited = new Heap(2);
    this->visited = new Heap(2);
    this->solutions = new Heap(2);
    this->lowerBound.push_back(0);
    this->cantidadNodos = 0;
}

/**
 * @brief Destructor de la clase BB
 */
BB::~BB() {}

/**
 * @brief calcula la solucion simplex de un problema
 * resolviendo las variables que deben ser enteras
 * @param namefile string con el nombre del archivo a leer
 */
void BB::solve(string namefile) {
    Simplex* s = new Simplex(namefile);
    this->cantidadNodos = 1;

    s->solve();

    //! s->printProblemMatrix();
    //! s->printUpperBound();

    if (s->intVars.size() == 0) {
        return;
    }

    lowerBound = s->solveLB();
    //! printLowerBound();

    this->noVisited->push(new Node(s));

    while (this->noVisited->size > 0) {
        Node* node = this->noVisited->pop(0);
        this->visited->push(node);

        s = node->s;
        int indexFrac = moreFracctional(s->upperBound, s->intVars);

        Simplex* sIzq = s->copy();
        Simplex* sDer = s->copy();

        //! cout << "Izq: insertando restricciones x" << indexFrac
        //!      << " <= " << int(s->upperBound[indexFrac] + 1) << endl;
        sIzq->insertConstraint(int(s->upperBound[indexFrac]), indexFrac, 1);
        //! sIzq->printProblemMatrix();
        sIzq->solve();
        //! sIzq->printUpperBound();
        updateLowerBound(sIzq->solveLB());
        //! printLowerBound();

        //! cout << "Der: insertando restricciones x" << indexFrac
        //!      << " >= " << int(s->upperBound[indexFrac] + 1) << endl;
        sDer->insertConstraint(int(s->upperBound[indexFrac] + 1), indexFrac, 2);
        //! sDer->printProblemMatrix();
        sDer->solve();
        //! sDer->printUpperBound();
        updateLowerBound(sDer->solveLB());
        //! printLowerBound();

        if (lowerBound[0] >= sIzq->upperBound[0] &&
            lowerBound[0] >= sDer->upperBound[0]) {
            Node* nSol = new Node(lowerBound);

            //! cout << "Insertando solucion" << endl;
            if (!solutions->isInHeap(nSol))
                solutions->push(nSol);
        } else {
            if (isSolution(new Node(sIzq))) {
                Node* nSolIzq = new Node(sIzq->upperBound);

                //! cout << "Insertando solucion Izq" << endl;
                if (!solutions->isInHeap(nSolIzq))
                    solutions->push(nSolIzq);
            }
            if (isSolution(new Node(sDer))) {
                Node* nSolDer = new Node(sDer->upperBound);

                //! cout << "Insertando solucion Der" << endl;
                if (!solutions->isInHeap(nSolDer))
                    solutions->push(nSolDer);
            }
        }

        if (sIzq->upperBound[0] > lowerBound[0] && sIzq->upperBound.size() > 0) {
            Node* nIzq = new Node(sIzq);

            //! cout << "Insertando Nodo Izq " << endl;
            if (!visited->isInHeap(nIzq))
                noVisited->push(nIzq);
        } else {
            this->visited->push(new Node(sIzq));
        }

        if (sDer->upperBound[0] > lowerBound[0] && sDer->upperBound.size() > 0) {
            Node* nDer = new Node(sDer);

            //! cout << "Insertando Nodo Der " << endl;
            if (!visited->isInHeap(nDer))
                noVisited->push(nDer);
        } else {
            this->visited->push(new Node(sDer));
        }

        this->cantidadNodos++;
        //! cout << endl;
    }

    if (solutions->size > 0) {
        this->finalSolution = solutions->pop(0)->upperBound;
    }
}

/**
 * @brief Verifica que un nodo sea solucion
 * @param node nodo a verificar
 */
int BB::isSolution(Node* node) {
    vector<float> upperBound = node->s->upperBound;
    vector<int> intVars = node->s->intVars;

    if (upperBound.size() == 0) {
        return 0;
    }

    for (int i : intVars) {
        if (upperBound[i] != int(upperBound[i])) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Recorre el vector de numeros y retorna el indice del numero
 * mas fraccional en caso de que existan varios retorna el primero
 * @param numeros vector de numeros
 * @param indices vector de indices de los numeros que deben ser enteros
 */
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

/**
 * @brief Actualiza el lowerBound del algoritmo y si se actualiza,
 * tambien actualiza el vector de soluciones y el vector de nodos no visitados
 * @param lowerBound nuevo lowerBound
 */
void BB::updateLowerBound(vector<float> lowerBound) {
    if (lowerBound.size() == 0) {
        return;
    } else if (lowerBound[0] > this->lowerBound[0]) {
        this->lowerBound = lowerBound;
        bound();
    }
}

/**
 * @brief Elimina los nodos del heap solutions que sean menores que el lowerBound
 * y los nodos del heap noVisited que sean menores que el lowerBound, moviendolos
 * al heap visited
 */
void BB::bound() {
    int i;

    i = 0;
    while (i < solutions->size) {
        if (solutions->data[i]->upperBound[0] < lowerBound[0]) {
            solutions->pop(i);
            i = 0;
        }
        i++;
    }

    i = 0;
    while (i < noVisited->size) {
        if (noVisited->data[i]->s->upperBound[0] < lowerBound[0]) {
            visited->push(noVisited->pop(i));
            i = 0;
        }
        i++;
    }
}

/**
 * @brief Imprime el lowerBound
 */
void BB::printLowerBound() {
    if (lowerBound.size() > 0) {
        cout << "lowerBound: ";
        for (float i : this->lowerBound) {
            cout << i << " ";
        }
        cout << endl
             << endl;
    } else {
        cout << "lowerBound: No hay" << endl
             << endl;
    }
}

/**
 * @brief Imprime la solucion final
 */
void BB::printFinalSolution() {
    if (this->finalSolution.size() > 0) {
        cout << "Solucion Final: ";
        for (float i : this->finalSolution) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        cout << "Solucion Final: No hay" << endl;
    }
}