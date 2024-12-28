#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "src/selection.h"
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

int main(){
    printf("%s", CURSOR_VISIBILITY_FALSE);
    system("cls");

    int option1;
    int option2;
    int return_value;
    char path_1[] = "src/resources/options_strings/selection_one.txt";
    char path_2[] = "src/resources/options_strings/selection_two.txt";

    option1 = initializeSelection(1, 1, 9, 3, 3, 12, path_1);
    return_value = checkOption(option1);

    option2 = initializeSelection(1, 1, 2, 2, 1, 12, path_2);
    return_value = checkOption(option2);

    printf("\n\nOPZIONI SELEZIONATE (a partire da 0):");
    printf("\n >> prima selezione: %d", option1);
    printf("\n >> seconda selezione: %d", option2);

    printf("\n\n-- PREMERE UN TASTO PER CHIUDERE --");
    getch();

    printf("%s", ERASE_SCREEN);
    printf("%s", TEXT_COLOR_RESET);
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", CURSOR_VISIBILITY_TRUE);

    return return_value; // return_value: 0/1
}
