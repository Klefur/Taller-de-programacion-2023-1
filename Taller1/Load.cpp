#include "Load.h"

using namespace std;

// Entrada: El nombre del archivo a abrir
// Salida: -
// Funcionamiento: Abre el archivo y verifica que se haya abierto correctamente
Load::Load(const char *nombre)
{
    this->file = new ifstream(nombre); // abrir el archivo
    if (this->file->is_open())
    { // verificar que el archivo se abrio correctamente
        // cout << "archivo abierto" << std::endl;
    }
    else
    {
        // cout << "archivo no encontrado" << std::endl;
        exit(1);
    }
}

// Entrada: -
// Salida: -
// Funcionamiento: Cierra el archivo
Load::~Load() { this->file->close(); }

// Entrada: -
// Salida: Un arreglo con los datos del conductores, items y tamaño del bote
// Funcionamiento: Lee la primera linea del archivo y extrae los datos
int *Load::readInfo()
{
    int *info = new int[3];
    getline(*this->file, this->line);
    this->ss << this->line;                    // copiar la linea al stream
    this->ss >> info[0] >> info[1] >> info[2]; // leer los datos del stream
    return info;
}

// Entrada: -
// Salida: La cantidad de restricciones
// Funcionamiento: Lee la cantidad de restricciones
int Load::readRestriccion()
{
    getline(*this->file, this->line);
    int resCount = atoi(this->line.c_str()); // c_str convierte el string a un arreglo de caracteres
    return resCount;
}

// Entrada: La cantidad de restricciones y la cantidad total de conductores e items
// Salida: Una matriz con las restricciones
// Funcionamiento: Lee las restricciones y las guarda en una matriz
int **Load::loadMatrix(int resCount, int N)
{

    int **restricciones;

    restricciones = new int *[resCount]; // crear la matriz de restricciones
    for (int i = 0; i < resCount; i++)
    {
        restricciones[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            restricciones[i][j] = 0;
        }
    }

    // leer las restricciones
    for (int i = 0; i < resCount; i++)
    {
        getline(*this->file, this->line);
        this->ss.clear();       // NO OLVIDAR ESTO: limpiar el stream de caracteres, porque ya viene con cosas
        this->ss << this->line; // llenar el stream con linea
        while (!this->ss.eof())
        { // mientras no termine esta linea
            int a;
            this->ss >> a;
            restricciones[i][a - 1] = 1; // a-1 porque los indices empiezan en 0
        }
    }

    return restricciones;
}