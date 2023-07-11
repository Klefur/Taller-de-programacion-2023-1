#include <iostream>
#include "Node.h"

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
    Node* pop();
    void push(Node* s);
    void heapify(int i);
    int isInHeap(Node* s);
};