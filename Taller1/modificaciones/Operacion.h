class Operacion
{
public:
    int *op;
    int coste;
    int peso;

    Operacion(int *arr, int largo, int peso, int coste);
    ~Operacion();
};