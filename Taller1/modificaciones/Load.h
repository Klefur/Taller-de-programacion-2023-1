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
    Load(const char *nombre);
    ~Load();
    int *readInfo();
    int **loadMatrix(int resCount, int N);
    int readRes();
};
