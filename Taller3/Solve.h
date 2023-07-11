#include "Simplex.h"

#define LOGIC_ONE 0.999999
class Solve
{
public:
    Solve(/* args */);
    ~Solve();
    void resolve(std::string namefile);
    int moreFracctional(std::vector<float> numeros,
                        int longitud,
                        std::vector<int> indices);
};

