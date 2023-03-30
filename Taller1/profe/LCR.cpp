#include "LCR.h"

LCR::LCR() {
    open = new Stack(1000);
    closed= new Stack(1000);
}

LCR::LCR(string nombreArchivo) {
    open = new Stack(1000);
    closed= new Stack(1000);
    this->nombreArchivo = nombreArchivo;
}

LCR::~LCR() {
    delete open;
    delete closed;

}

void LCR::solve() {
    State *inicial = new State(); // new llama al constructor y entrega un puntero
    open->push(inicial);
    while (!open->isEmpty()) {
        State *s = open->pop();
        if (s->isFinal()) {
            cout << "Solucion encontrada" << endl;
            s->printPath();
            return;
        }
        closed->push(s); 
        
/*
    
    for (int k=0; k <nuOperaciones; k++)
    	operacion=op[k] 
    	if operacion->canMove(s,res):
    		s1 = operacion->Move(s)
    		if s1 no esta en open ni en close
    			open->push(s1)
    		else
    			delete s1
    			

*/



        if (canMoveL(s)) {
            cout << "Puedo mover L de:" << endl;
            s->print();
            State *s1 = moveL(s);
            cout << "quedando:" << endl;
            s1->print();
            if (!closed->search(s1) && !open->search(s1))
                open->push(s1);
            else {
                cout << "No se agrega L" << endl;
                delete s1;
            }
        }
        if (canMoveC(s)) {
            cout << "Puedo mover C" << endl;
            s->print();
            State *s1 = moveC(s);
            cout << "quedando:" << endl;
            s1->print();
            if (!closed->search(s1) && !open->search(s1))
                open->push(s1);
            else {
                cout << "No se agrega C" << endl;
                delete s1;
            }
        }
        if (canMoveR(s)) {
            cout << "Puedo mover R" << endl;
            s->print();
            State *s1 = moveR(s);
            cout << "quedando:" << endl;
            s1->print();
            if (!closed->search(s1) && !open->search(s1))
                open->push(s1);
            else {
                cout << "No se agrega R" << endl;
                delete s1;
            }
        }
        if (canMoveG(s)) {
            cout << "Puedo mover G" << endl;
            s->print();
            State *s1 = moveG(s);
            cout << "quedando:" << endl;
            s1->print();
            if (!closed->search(s1) && !open->search(s1))
                open->push(s1);
            else {
                cout << "No se agrega G" << endl;
                delete s1;
            }
        }
    } // while
    cout << "No hay solucion" << endl;
}

State* LCR::moveL(State *s) {
    int left[4];
    int right[4];
    // copiar los arreglos
    for (int i = 0; i < 4; i++) {
        left[i] = s->left[i];
        right[i] = s->right[i];
    }
    if (left[WOLF] == 1) {
        left[WOLF] = 0;
        right[WOLF] = 1;
        left[FARMER] = 0;
        right[FARMER] = 1;
    } else {
        left[WOLF] = 1;
        right[WOLF] = 0;
        left[FARMER] = 1;
        right[FARMER] = 0;
    }
    return new State(left, right, s);
}

State* LCR::moveC(State *s) {
    int left[4];
    int right[4];
    // copiar los arreglos
    for (int i = 0; i < 4; i++) {
        left[i] = s->left[i];
        right[i] = s->right[i];
    }
    if (left[GOAT] == 1) {
        left[GOAT] = 0;
        right[GOAT] = 1;
        left[FARMER] = 0;
        right[FARMER] = 1;
    } else {
        left[GOAT] = 1;
        right[GOAT] = 0;
        left[FARMER] = 1;
        right[FARMER] = 0;
    }
    return new State(left, right, s);
}

State* LCR::moveR(State *s) {
    int left[4];
    int right[4];
    // copiar los arreglos
    for (int i = 0; i < 4; i++) {
        left[i] = s->left[i];
        right[i] = s->right[i];
    }
    if (left[CABBAGE] == 1) {
        left[CABBAGE] = 0;
        right[CABBAGE] = 1;
        left[FARMER] = 0;
        right[FARMER] = 1;
    } else {
        left[CABBAGE] = 1;
        right[CABBAGE] = 0;
        left[FARMER] = 1;
        right[FARMER] = 0;
    }
    return new State(left, right, s);
}

State* LCR::moveG(State *s) {
    int left[4];
    int right[4];
    // copiar los arreglos
    for (int i = 0; i < 4; i++) {
        left[i] = s->left[i];
        right[i] = s->right[i];
    }
    if (left[FARMER] == 1) {
        left[FARMER] = 0;
        right[FARMER] = 1;
    } else {
        left[FARMER] = 1;
        right[FARMER] = 0;
    }
    return new State(left, right, s);
}

bool LCR::canMoveL(State *s) { // El lobo se mueve si 
    return ((s->left[FARMER] == 1 && s->left[WOLF]==1 // el granjero esta en la izquierda y el lobo tambien
             && (s->left[GOAT]==0 || s->left[CABBAGE]==0))) // y no estan simultaneamente la cabra y el repollo
             ||
           ((s->right[FARMER] == 1 && s->right[WOLF]==1 
             && (s->right[GOAT]==0 || s->right[CABBAGE]==0)));
}

bool LCR::canMoveR(State *s) { // El repollo se mueve si
    return ((s->left[FARMER] == 1 && s->left[CABBAGE]==1 // el granjero esta en la izquierda y el repollo tambien 
             && (s->left[GOAT]==0 || s->left[WOLF]==0))) // y no estan simultaneamente la cabra y el lobo
             ||
           ((s->right[FARMER] == 1 && s->right[CABBAGE]==1 
             && (s->right[GOAT]==0 || s->right[WOLF]==0)));
}


bool LCR::canMoveC(State *s) {// La cabra se mueve si
    return (s->left[FARMER] == 1 && s->left[GOAT]==1  // el granjero esta en la izquierda y la cabra tambien) 
             ||
           (s->right[FARMER] == 1 && s->right[GOAT]==1 ) );
}

bool LCR::canMoveG(State *s) { // El granjero se mueve si
    return ((s->left[FARMER] == 1   // el granjero esta en la izquierda
             && (s->left[WOLF]==0 || s->left[GOAT]==0)) // y no estan simultaneamente el lobo y la cabra
             && (s->left[CABBAGE]==0 || s->left[GOAT]==0)) // y no estan simultaneamente el repollo y la cabra
             ||
           ((s->right[FARMER] == 1   
             && (s->right[WOLF]==0 || s->right[GOAT]==0))
             && (s->right[CABBAGE]==0 || s->right[GOAT]==0));
}
