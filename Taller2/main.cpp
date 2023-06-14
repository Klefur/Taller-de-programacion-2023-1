#include <iostream>
#include "AST.h"

using namespace std;

int main(int argc, char const* argv[]) {
    string filename = "expr1.txt";
    int option = 0;
    AST* tree = new AST(filename);

    while (option != 6) {
        cout << "Opciones: " << endl;
        cout << "1. Cargar expresion" << endl;
        cout << "2. Evaluar expresion" << endl;
        cout << "3. Derivar expresion" << endl;
        cout << "4. Simplificar expresion" << endl;
        cout << "5. Imprimir expresion" << endl;
        cout << "6. Salir" << endl;
        cout << "Eliga una opcion:" << endl;
        cin >> option;

        switch (option) {
            case 1: {
                cout << "Ingrese el nombre del archivo: " << endl;
                cin >> filename;
                tree = new AST(filename);
                break;
            }
            case 2: {
                int hasVariables;
                cout << "El arbol posee variables? (1: Si, 0: No)" << endl;
                cin >> hasVariables;

                if (hasVariables) {
                    int largo;
                    cout << "Ingrese el numero de variables: " << endl;
                    cin >> largo;

                    char variable;
                    string variables = "";
                    int values[largo];

                    for (int i = 0; i < largo; i++) {
                        cout << "Ingrese el nombre de la variable " << i + 1
                             << ": " << endl;
                        cin >> variable;
                        variables += variable;
                        cout << "Ingrese el valor de la variable " << i + 1
                             << ": " << endl;
                        cin >> values[i];
                    }
                    tree->root =
                        tree->replace(tree->root, variables, values, largo);
                }
                cout << "La evaluacion es: " << tree->eval(tree->root) << endl;
                break;
            }
            case 3: {
                char variable;
                cout << "Ingrese la variable a derivar: " << endl;
                cin >> variable;
                tree->root = tree->derivate(tree->root, variable);
                break;
            }
            case 4: {
                tree->root = tree->simplify(tree->root);
                break;
            }
            case 5: {
                tree->print();
                break;
            }
            case 6: {
                break;
            }
            default: {
                cout << "Opcion invalida" << endl;
                break;
            }
        }

        cout << "Operacion aplicada" << endl << endl;
    }
}
