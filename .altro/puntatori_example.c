#include <stdio.h>
#include <windows.h>

void addX(int *x); 
void addArray(int vettore[]);
int **createMatrix (int righe_matrice, int colonne_matrice);

int main () {
    int x = 3;

    int vettore[2] = {1, 2};

    int righe_matrice = 2;
    int colonne_matrice = 3;
    int **matrice;

    /*
     * chiamiamo la funzione addX() per incrementare il 
     * valore di x senza usare valori in ritorno, 
     * usando i puntatori
     */
    addX(&x);
    printf("r:%d", x);

    /*
     * nel caso dei vettori non c'è bisogno
     * in quanto scrivere *vettore è lo 
     * stesso di scrivere vettore[]
     */
    addArray(vettore);
    printf("\nv[0]:%d", vettore[0]);

    //addesso proviamo con una matrice
    matrice = createMatrix(righe_matrice, colonne_matrice);
    for (int i=0; i<righe_matrice; i++){
        for(int j=0; j<colonne_matrice; j++) {
            printf("\nmatrice[%d][%d]:%d", i, j, matrice[i][j]);
        }
    }

    return 0;
}

void addX(int *x) {
    *x = *x + 1;
}

void addArray(int vettore[]) {
    vettore[0] = vettore[0] + 1;
}

int **createMatrix (int righe_matrice, int colonne_matrice) {
    int **matrice;

    /*
     * nel caso di una matrice di faremo in modo di allocare
     * prima la memoria che utilizzeremo e successivamente
     * assegneremo i valori alla matrice
     */
    //allocamento memoria
    matrice = malloc(sizeof(int) * righe_matrice);
    for(int i=0; i<righe_matrice; i++){
        matrice[i] = malloc(sizeof(int) * colonne_matrice);
    }

    //assegnamento valori
    for (int i=0; i<righe_matrice; i++){
        for(int j=0; j<colonne_matrice; j++) {
            matrice[i][j] = i+j; //i+j non è importante è solo per inserire valori diversi ad ogni cella
        }
    }

    return matrice;
}