#include <stdio.h>
#include <windows.h>
#include <conio.h>
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
    printf("%s", CURSOR_VISIBILITY_FALSE);
    system("cls");

    int option1;
    int option2;
    int return_value;
    
    Settings settings_selection_1;
    settings_selection_1.use_columns = 1;
    settings_selection_1.use_rows = 1;
    settings_selection_1.max_options = 9;
    settings_selection_1.max_columns = 3;
    settings_selection_1.max_rows = 3;
    settings_selection_1.max_line_length = 20;
    strcpy(settings_selection_1.strings_filename, "src/resources/options_strings/selection_one.txt");

    Settings settings_selection_2;
    settings_selection_2.use_columns = 1;
    settings_selection_2.use_rows = 0;
    settings_selection_2.max_options = 2;
    settings_selection_2.max_columns = 2;
    settings_selection_2.max_rows = 1;
    settings_selection_2.max_line_length = 20;
    strcpy(settings_selection_2.strings_filename, "src/resources/options_strings/selection_two.txt");

    option1 = initializeSelection(settings_selection_1);
    if (option1 < 0){
        checkOption(option1);
        return_value = 1;
    }

    option2 = initializeSelection(settings_selection_2);
    if (option2 < 0){
        checkOption(option1);
        return_value = 1;
    }

    printf("\n\nOPZIONI SELEZIONATE (a partire da 0):");
    printf("\n >> prima selezione: %d", option1);
    printf("\n >> seconda selezione: %d", option2);

    printf("\n\n-- PREMERE UN TASTO PER CHIUDERE --");
    getch();

    printf("%s", ERASE_SCREEN);
    printf("%s", TEXT_COLOR_RESET);
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", CURSOR_VISIBILITY_TRUE);
    
    return return_value;
}

void checkOption (int error_code) {
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN);

    printf("\n");
    
    switch (error_code) {
        case -1:
            printf("%s[ERRORE]: file delle stringhe delle opzioni inesistente o percorso incorretto", TEXT_COLOR_RED);
            break;

        case -2:
            printf("%s[ERRORE]: impostazioni fornite non valide", TEXT_COLOR_RED);
            break;

        case -3:
            printf("%s[ERRORE]: tasto premuto non valido", TEXT_COLOR_RED);
            break;

        case -4:
            printf("%s[ERRORE]: coordinate non valide", TEXT_COLOR_RED);
            break;

        default:
            printf("%s[ERRORE]: non definito", TEXT_COLOR_RED);
            break;
    }

    printf(" (codice errore: %d)%s", error_code, TEXT_COLOR_RESET);

    printf("\n\n-- PREMERE UN TASTO PER PROSEGUIRE --");
    getch();
}
