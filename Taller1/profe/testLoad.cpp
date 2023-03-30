#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {



    ifstream *input = new ifstream("sistema.txt"); // abrir el archivo
    if (input->is_open()) { // verificar que el archivo se abrio correctamente
        std::cout << "archivo abierto" << std::endl;

    } else {
        std::cout << "archivo no encontrado" << std::endl;
        exit(1);
    }

    string line; // linea de texto
    stringstream ss; // stream de caracteres

    // variables a leer del archivo
    int C,I,b,N; // cantidad de conductores, cantidad de item, capacidad del bote, cantidad total de item mas conductores
    int cantidadRestriccionesIzq, cantidadRestriccionesDer; // cantidad de restricciones de cada lado
    int **restriccionesIzq, **restriccionesDer; // matriz de restricciones de cada lado


    // leer la primera linea
    getline(*input, line);
    ss << line; // copiar la linea al stream
    ss >> C >> I >> b; // leer los datos del stream
    N = C + I;
    cout <<"C:"<< C << " I:" << I << " b:" << b << endl;

    // leer la segunda linea
    getline(*input, line);
    cantidadRestriccionesIzq=atoi(line.c_str()) ; // c_str convierte el string a un arreglo de caracteres
    cout<<"cantidadRestriccionesIzq:"<<cantidadRestriccionesIzq<<endl;
    restriccionesIzq = new int*[cantidadRestriccionesIzq]; // crear la matriz de restricciones
    for (int i = 0; i < cantidadRestriccionesIzq; i++) {
        restriccionesIzq[i] = new int[N];
        for (int j = 0; j < N; j++) {
            restriccionesIzq[i][j] = 0;
        }
    }

    // leer las restricciones del lado izquierdo
    for (int i = 0; i < cantidadRestriccionesIzq; i++) {
        getline(*input, line);
        ss.clear(); // NO OLVIDAR ESTO: limpiar el stream de caracteres, porque ya viene con cosas
        ss << line; // llenar el stream con linea
        while (!ss.eof()) { // mientras no termine esta linea
            int a;
            ss >> a;
            restriccionesIzq[i][a-1] = 1; // a-1 porque los indices empiezan en 0
            cout << a << " ";
        }
        cout << endl;
    }
    
    
    // leer las restricciones del lado derecho
    getline(*input, line);
    ss.clear(); // limpiar el stream de caracteres
    ss << line; // copiar la linea al stream
    ss >> cantidadRestriccionesDer ;
    cout<<"cantidadRestriccionesDer:"<<cantidadRestriccionesDer<<endl;
    restriccionesDer = new int*[cantidadRestriccionesDer]; // crear la matriz de restricciones
    for (int i = 0; i < cantidadRestriccionesDer; i++) {
        restriccionesDer[i] = new int[N];
        for (int j = 0; j < N; j++) { // inicialmente en 0
            restriccionesDer[i][j] = 0;
        }
    }

    for (int i = 0; i < cantidadRestriccionesDer; i++) {
        getline(*input, line);
        ss.clear(); // limpiar el stream de caracteres
        ss << line; // copiar la linea al stream
        while (!ss.eof()) { // mientras no termine esta linea
            int a;
            ss >> a;
            restriccionesDer[i][a-1] = 1; // recuerden que los elementos de los archivos empiezan en 1, pero los indices en 0
            cout << a << " ";
        }
        cout << endl;
    }

    // cerrar el archivo
    input->close();

    // veamos como quedan las matrices

    cout<<"restriccionesIzq:"<<endl;
    for(int i=0;i<cantidadRestriccionesIzq;i++){
        for(int j=0;j<N;j++){
            cout<<restriccionesIzq[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"restriccionesDer:"<<endl;
    for(int i=0;i<cantidadRestriccionesDer;i++){
        for(int j=0;j<N;j++){
            cout<<restriccionesDer[i][j]<<" ";
        }
        cout<<endl;
    }
}