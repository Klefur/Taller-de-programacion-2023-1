#include "Heap.h"

using namespace std;

/**
 * @brief Constructor de la clase Heap
 * @param capacity capacidad inicial del heap
 */
Heap::Heap(int capacity) {
    this->capacity = capacity;
    data = new Node*[capacity];
    size = 0;
}

/**
 * @brief Destructor de la clase Heap
 */
Heap::~Heap() {
    delete[] data;
}

/**
 * @brief Intercambia dos nodos del heap
 * @param i indice del primer nodo
 * @param j indice del segundo nodo
 */
void Heap::swap(int i, int j) {
    Node* temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

/**
 * @brief Retorna el indice del hijo izquierdo de un nodo
 * @param i indice del nodo
 * @return int indice del hijo izquierdo
 */
int Heap::left_idx(int i) {
    return 2 * i + 1;
}

/**
 * @brief Retorna el indice del hijo derecho de un nodo
 * @param i indice del nodo
 * @return int indice del hijo derecho
 */
int Heap::right_idx(int i) {
    return 2 * i + 2;
}

/**
 * @brief Retorna el indice del padre de un nodo
 * @param i indice del nodo
 * @return int indice del padre
 */
int Heap::parent_idx(int i) {
    return (i - 1) / 2;
}

/**
 * @brief Retorna el nodo con indice i
 * @param i indice del nodo
 * @return Node* con indice i
 */
Node* Heap::pop(int i) {
    if (size == 0) {
        return nullptr;
    }
    Node* s = data[i];
    data[i] = data[size - 1];
    size--;
    heapify(i);
    return s;
}

/**
 * @brief Inserta un nodo en el heap y lo ordena
 * @param n nodo a insertar
 */
void Heap::push(Node* n) {
    if (size == capacity) {
        Node** temp = new Node*[capacity * 2];
        for (int i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = capacity * 2;
    }
    data[size] = n;
    size++;
    int i = size - 1;
    if (n->upperBound.size() != 0) {
        while (i > 0) {
            int p = parent_idx(i);
            if (data[i]->upperBound[0] > data[p]->upperBound[0]) {
                swap(i, p);
                i = p;
            } else {
                break;
            }
        }
    } else {
        while (i > 0) {
            int p = parent_idx(i);
            if (data[i]->s->upperBound[0] > data[p]->s->upperBound[0]) {
                swap(i, p);
                i = p;
            } else {
                break;
            }
        }
    }
}

/**
 * @brief Ordena el heap de mayor a menor
 * @param i indice del nodo
 */
void Heap::heapify(int i) {
    int l = left_idx(i);
    int r = right_idx(i);
    int higher = i;

    if (data[i]->upperBound.size() != 0) {
        if (l < size && data[l]->upperBound[0] > data[i]->upperBound[0]) {
            higher = l;
        }
        if (r < size && data[r]->upperBound[0] > data[higher]->upperBound[0]) {
            higher = r;
        }
        if (higher != i) {
            swap(i, higher);
            heapify(higher);
        }
    } else {
        if (l < size && data[l]->s->upperBound[0] > data[i]->s->upperBound[0]) {
            higher = l;
        }
        if (r < size &&
            data[r]->s->upperBound[0] > data[higher]->s->upperBound[0]) {
            higher = r;
        }
        if (higher != i) {
            swap(i, higher);
            heapify(higher);
        }
    }
}

/**
 * @brief Verifica si un nodo esta dentro del heap
 * @param n nodo a verificar
 * @return int 1 si esta en el heap, 0 si no
 */
int Heap::isInHeap(Node* n) {
    int cont = 0, ubSize;

    if (n->upperBound.size() != 0) {
        ubSize = n->upperBound.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < ubSize; j++) {
                if (data[i]->upperBound[j] == n->upperBound[j]) {
                    cont++;
                }
            }
            if (cont == ubSize) {
                return 1;
            }
            cont = 0;
        }
    } else {
        ubSize = n->s->upperBound.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < ubSize; j++) {
                if (data[i]->s->upperBound[j] == n->s->upperBound[j]) {
                    cont++;
                }
            }
            if (cont == ubSize) {
                return 1;
            }
            cont = 0;
        }
    }

    return 0;
}