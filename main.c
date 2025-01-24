#include <stdio.h>
#include "src/option_selector.h"

int main( void ){
    int option1;
    int option2;
    char path_1[] = "src/resources/options_strings/selection_one.txt";
    char path_2[] = "src/resources/options_strings/selection_two.txt";

    option1 = initializeSelection(1, 0, 8, 8, 1, 13, path_1, 0, 0);
    option2 = initializeSelection(0, 1, 2, 1, 2, 13, path_2, 0, 0);

    printf("OPZIONI SELEZIONATE (a partire da 0):");
    printf("\n  >> prima selezione: %d", option1);
    printf("\n  >> seconda selezione: %d", option2);

    return 0;
}
