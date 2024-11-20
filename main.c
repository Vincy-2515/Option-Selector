#include <stdio.h>
#include <windows.h>
#include "src/selection.h"

#define ERASE_SCREEN "\x1b[2J"
#define MOVE_CUROSOR_TO_HOME "\x1b[H"
#define DEFAULT_COLORS "\x1b[0m"

void checkOption(int option);

int main () {
    int option1;
    int option2;

    system("cls");

    option1 = initializeSelection(1);

    option2 = initializeSelection(2);

    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", DEFAULT_COLORS);
    printf("%s", ERASE_SCREEN);

    if (option1 < 0) checkOption(option1);
    if (option2 < 0) checkOption(option1);
    printf("\nop1: %d", option1);
    printf("\nop2: %d", option2);

    printf("\nPREMI [INVIO] PER CHIUDERE");
    getchar();

    return 0;
}

void checkOption (int option) {
/*     printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN); */
    
    if (option == -1) {
        printf("[ERRORE]: tasto premuto non valido");
    } 
    else if (option == -2) {
        printf("[ERRORE]: coordinate non valide");
    }
    else {
        printf("[ERRORE]: non definito");
    }
}
