#include "Simplex.h"

class Node {
   public:
    Simplex *s;
    std::vector<float> upperBound;

    Node(Simplex *s);
    Node(std::vector<float> upperBound);
    ~Node();
};
