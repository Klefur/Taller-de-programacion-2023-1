#include "Solve.h"

using namespace std;

int main(int argc, char const* argv[]) {
    Solve* solve = new Solve();
    solve->resolve("sistema.txt");
    return 0;
}