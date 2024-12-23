#include <stdio.h>
#include <windows.h>
#include "src/selection.h"

#define ERASE_SCREEN "\x1b[2J"

//MOVIMENTO CURSORE:
#define MOVE_CUROSOR_TO_HOME "\x1b[H"
#define CURSOR_VISIBILITY_TRUE "\x1B[?25h"
#define CURSOR_VISIBILITY_FALSE "\x1B[?25l"

//COLORE DEL TESTO
#define TEXT_COLOR_RED "\x1B[1;31m"
#define TEXT_COLOR_YELLOW "\x1b[1;33m"
#define TEXT_COLOR_RESET "\x1B[0;0m"

void checkOption(int option);

int main () {
    int option1;
    int option2;

    system("cls");
    printf("%s", CURSOR_VISIBILITY_FALSE);

    option1 = initializeSelection(1);
    if (option1 < 0) checkOption(option1);

    option2 = initializeSelection(2);
    if (option2 < 0) checkOption(option1);

    printf("\n\n-- PREMERE [INVIO] PER CHIUDERE --");
    getchar();

    printf("%s", ERASE_SCREEN);
    printf("%s", TEXT_COLOR_RESET);
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", CURSOR_VISIBILITY_TRUE);

    return 0;
}

void checkOption (int option) {
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN);

    printf("\n");
    
    if (option == -1) {
        printf("%s[ERRORE]: tasto premuto non valido", TEXT_COLOR_RED);
    } 
    else if (option == -2) {
        printf("%s[ERRORE]: coordinate non valide", TEXT_COLOR_RED);
    }
    else {
        printf("%s[ERRORE]: non definito", TEXT_COLOR_RED);
    }

    printf(" (codice errore: %d)%s", option, TEXT_COLOR_RESET);

    printf("\n\n-- PREMERE [INVIO] PER PROSEGUIRE --");
    getchar();
}
