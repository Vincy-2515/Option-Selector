#include <stdio.h>
#include <conio.h>
#include "src/option_selector.h"

#define ERASE_SCREEN "\x1b[2J"

// CURSORE:
#define MOVE_CUROSOR_TO_HOME "\x1b[H"

int main( void ){
    int option1;
    int option2;
    char path_1[] = "src/resources/options_strings/selection_one.txt";
    char path_2[] = "src/resources/options_strings/selection_two.txt";
    
    printf("%s", ERASE_SCREEN);

    option1 = initializeSelection(1, 1, 8, 3, 3, 13, path_1, 0, 0);

    option2 = initializeSelection(0, 1, 2, 1, 2, 13, path_2, 0, 0);

    printf("OPZIONI SELEZIONATE (a partire da 0):");
    printf("\n  >> prima selezione: %d", option1);
    printf("\n  >> seconda selezione: %d", option2);

    printf("\n\nPREMERE UN TASTO PER CHIUDERE: ");
    _getch();

    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN);

    return 0;
}
