#include "BB.h"

using namespace std;

int main(int argc, char const *argv[])
{
    BB *solve = new BB();
    solve->solve("sistema.txt");
    solve->printFinalSolution();
    return 0;
}