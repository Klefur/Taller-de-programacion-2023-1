#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Load
{
private:
    std::ifstream *file;
    std::string line;
    std::stringstream ss;

public:
    // Constructor
    Load(const char *nombre);
    // Destructor
    ~Load();
    // Lee la cantidad de restricciones
    int *readInfo();
    // Lee la matriz de restricciones
    int **loadMatrix(int resCount, int N);
    // Lee la cantidad de restricciones
    int readRestriccion();
};
