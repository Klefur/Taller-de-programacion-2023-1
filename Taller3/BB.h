#include "Heap.h"

#define LOGIC_ONE 0.999999

class BB {
   public:
    Heap* solutions;
    Heap* noVisited;
    Heap* visited;

    BB();
    ~BB();
    void solve(std::string namefile);
    int moreFracctional(std::vector<float> numeros, std::vector<int> indices);
    int isSolution(Node* node);
};
