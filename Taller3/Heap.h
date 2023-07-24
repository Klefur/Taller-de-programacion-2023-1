#include <iostream>
#include "Node.h"

/**
 * @brief Clase que representa la estructura de un max heap
 */
class Heap {
   public:
    Node** data;
    int size;      // current size
    int capacity;  // max size
    Heap(int capacity);
    ~Heap();
    void swap(int i, int j);
    int left_idx(int i);
    int right_idx(int i);
    int parent_idx(int i);
    Node* pop(int i);
    void push(Node* s);
    void heapify(int i);
    int isInHeap(Node* s);
};