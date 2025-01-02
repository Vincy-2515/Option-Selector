#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "src/option_selector.h"
#include "src/selection_error_management.h"

#define ERASE_SCREEN "\x1b[2J"

// CURSORE:
#define MOVE_CUROSOR_TO_HOME "\x1b[H"
#define CURSOR_VISIBILITY_TRUE "\x1B[?25h"
#define CURSOR_VISIBILITY_FALSE "\x1B[?25l"

// COLORE DEL TESTO:
#define TEXT_COLOR_RED "\x1B[1;31m"
#define TEXT_COLOR_YELLOW "\x1b[1;33m"
#define TEXT_COLOR_RESET "\x1B[0;0m"

int main( void ){
    printf("%s", CURSOR_VISIBILITY_FALSE);
    system("cls");

    int option1;
    int option2;
    int return_value;
    char path_1[] = "src/resources/options_strings/selection_one.txt";
    char path_2[] = "src/resources/options_strings/selection_two.txt";
    
    do{
        option1 = initializeSelection(1, 1, 8, 4, 2, 13, path_1, 0, 0);
        return_value = checkOption(option1);
        if (option1 <= -400) break;
    } while (option1 < 0);
    
    do{
        option2 = initializeSelection(0, 1, 2, 1, 2, 13, path_2, 0, 0);
        return_value = checkOption(option2);
        if (option1 <= -400) break;
    } while (option2 < 0);
    

    printf("\n\nOPZIONI SELEZIONATE (a partire da 0):");
    printf("\n >> prima selezione: %d", option1);
    printf("\n >> seconda selezione: %d", option2);

    printf("\n\n-- PREMERE UN TASTO PER CHIUDERE --");
    _getch();

    printf("%s", ERASE_SCREEN);
    printf("%s", TEXT_COLOR_RESET);
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", CURSOR_VISIBILITY_TRUE);

    return return_value; // return_value: 0/1
}
