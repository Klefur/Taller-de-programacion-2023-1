#include "Heap.h"

#define LOGIC_ONE 0.999999

/**
 * @brief Clase que representa la estructura del branch and bound
 * conformado de 3 max heap
 */
class BB {
   public:
    Heap* solutions;
    Heap* noVisited;
    Heap* visited;

    std::vector<float> lowerBound;
    std::vector<float> finalSolution;
    
    int cantidadNodos;

    BB();
    ~BB();
    void solve(std::string namefile);
    int moreFracctional(std::vector<float> numeros, std::vector<int> indices);
    int isSolution(Node* node);
    void updateLowerBound(std::vector<float> lowerBound);
    void bound();
    void printLowerBound();
    void printFinalSolution();
};
