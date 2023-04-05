#include "Load.h"

using namespace std;

Load::Load(const char *nombre)
{
    this->file = new ifstream(nombre); // abrir el archivo
    if (this->file->is_open())
    { // verificar que el archivo se abrio correctamente
        cout << "archivo abierto" << std::endl;
    }
    else
    {
        cout << "archivo no encontrado" << std::endl;
        exit(1);
    }
}

Load::~Load() { this->file->close(); }

int *Load::readInfo()
{
    int *info = new int[3];
    getline(*this->file, this->line);
    this->ss << this->line;                    // copiar la linea al stream
    this->ss >> info[0] >> info[1] >> info[2]; // leer los datos del stream
    return info;
}

int Load::readRestriccion()
{
    getline(*this->file, this->line);
    int resCount = atoi(this->line.c_str()); // c_str convierte el string a un arreglo de caracteres
    return resCount;
}

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