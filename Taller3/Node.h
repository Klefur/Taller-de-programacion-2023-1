#include "Simplex.h"

/**
 * @brief Clase que representa un nodo del arbol de max heap
 */
class Node {
   public:
    Simplex *s;
    std::vector<float> upperBound;

    Node(Simplex *s);
    Node(std::vector<float> upperBound);
    ~Node();
};
