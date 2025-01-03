#include <stdio.h>
#include <conio.h>
#include "src/option_selector.h"
#include "src/selection_error_management.h"

#define ERASE_SCREEN "\x1b[2J"

// CURSORE:
#define MOVE_CUROSOR_TO_HOME "\x1b[H"

int main( void ){
    int option1;
    int option2;
    int return_value;
    char path_1[] = "src/resources/options_strings/selection_one.txt";
    char path_2[] = "src/resources/options_strings/selection_two.txt";
    
    printf("%s", ERASE_SCREEN);

    do{
        printf("\033[H");
        option1 = initializeSelection(1, 1, 8, 4, 2, 13, path_1, 0, 0);
        return_value = checkOption(option1);
        if (option1 <= -400) break;
    } while (option1 < 0);

    do{
        printf("\033[H");
        option2 = initializeSelection(0, 1, 2, 1, 2, 13, path_2, 0, 0);
        return_value = checkOption(option2);
        if (option1 <= -400) break;
    } while (option2 < 0);
    

    printf("OPZIONI SELEZIONATE (a partire da 0):");
    printf("\n  >> prima selezione: %d", option1);
    printf("\n  >> seconda selezione: %d", option2);

    printf("\n\nPREMERE UN TASTO PER CHIUDERE: ");
    _getch();

    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN);

    return return_value; // return_value: 0/1
}
