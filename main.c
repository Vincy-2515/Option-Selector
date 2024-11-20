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
    if (option1 < 0) checkOption(option1);

    option2 = initializeSelection(2);
    if (option2 < 0) checkOption(option1);

    printf("\nPREMI [INVIO] PER CHIUDERE:");
    getchar();

    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", DEFAULT_COLORS);
    printf("%s", ERASE_SCREEN);

    return 0;
}

void checkOption (int option) {
/*     printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN); */
    
    if (option == -1) {
        printf("\n[ERRORE]: tasto premuto non valido");
    } 
    else if (option == -2) {
        printf("\n[ERRORE]: coordinate non valide");
    }
    else {
        printf("\n[ERRORE]: non definito");
    }

    printf("\noption: %d", option);
    printf("\nPREMI [INVIO] PER PROSEGUIRE:");
    getchar();
}
