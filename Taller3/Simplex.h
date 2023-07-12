#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define EPS 1.0e-6

/*
 Se basa en implementacion de libro "Numerical Recipes in C" W.PRESS et al,
 Cambridge University press, 2d Ed, 1992. pag 439
*/
class Simplex {
   private:
    // Numero total de restricciones
    int m;
    // Numero de variables
    int n;
    // Indica si el metodo solve ha sido llamado.
    bool isSolved;
    // Indica el estado de la solucion del problema despues de
    // solve, 0:Solucion encontrada 1:Solucion no acotada
    // -1:Solucion no factible
    int icase;
    // indice de variables que son cero en la solucion
    std::vector<int> izrov;
    // indice de variables que constituyen la solucion.
    // Si indice >=n entonces la variable es artificial
    // y no se cuenta en la solucion
    std::vector<int> iposv;
    int simplx();  // Metodo que ejecuta el algoritmo simplex
    void maxValue(int mm,
                  std::vector<int> ll,
                  int nll,
                  int iabf,
                  int* kp,
                  float* bmax);
    void locatePivot(int* ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);

   public:
    // Matriz inicial  --> de aqui pueden calcular el LB
    std::vector<std::vector<float>> initialA;
    //***** Matriz del problema: incluye c,a,b inicialmente se
    // transforma a la solucion por piveoteo*****
    std::vector<std::vector<float>> a;
    std::vector<int> intVars;       // Indices de variables enteras
    std::vector<float> upperBound; // Solucion del problema
    int m1;  // numero de restricciones <=
    int m2;  // numero de restricciones >=
    int m3;  // numero de restricciones =

    // Constructor con archivo de entrada
    Simplex(std::string file_name);
    // Constructor con matriz de entrada
    Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3);
    ~Simplex();
    // Metodo que ejecuta metodo simplex
    std::vector<float> solve();
    // Agrega una restriccion var<=b (tipo 1),
    // var>=b (tipo 2), var=b (tipo 3)
    void insertConstraint(float b, int var, int type);
    // Retorna el valor minimo de la solucion simplex
    std::vector<float> solveLB();
    // Retorna una copia del objeto
    Simplex* copy();
    // Retorna la solucion del problema de tamaño n+1
    // [Z,x1,...,xn] Z: valor funcion objetivo, xi: valor de la
    // variable i
    std::vector<float> getSolution();
    // Imprime la matriz del problema
    void printProblemMatrix();
    // Imprime la solucion del problema
    void printSolution();
    // Imprime la cota superior del problema
    void printUpperBound();
};