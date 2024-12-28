/**
 * @author Vincy-2515
 * @version v1.0.0.0
 * 
 * @note The download and other info can be found on Github (soon)
 * @link https://github.com/Vincy-2515
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define ENTER '\r'

// CURSORE:
#define ERASE_FROM_CURSOR_TO_ENDSCREEN "\x1B[0J"

// COLORE DEL TESTO:
#define INVERT_COLORS_TRUE "\x1B[7m"
#define INVERT_COLORS_FALSE "\x1B[27m"

//IMPOSTAZIONI (modificabili solo da "setSettings()"):
typedef struct Settings{
    int use_columns;
    int use_rows;
    int max_options;
    int max_columns;
    int max_rows;
    int max_option_string_length;
    char *path;
} Settings;

int initializeSelection (int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path);
static void setSettings (Settings *p_settings,int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path);
static int checkSettings (Settings settings);
static int printOptionsStrings (Settings settings, char **options_strings, int selected_option);
static int getStrings (Settings settings, char **options_strings);
static void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option);
static void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option);
static void printOnGrid (Settings settings, char **options_strings, int selected_option);
static void checkGridLimitOverflow (Settings settings, int *p_x, int *p_y, char last_input);
static int verifySelectedOptionCoords (Settings settings, int *options_coords, int x, int y);
static void coordGenerator (Settings settings, int *options_coords);

/**
 * @brief Funzione principale del file, prende in input le impostazioni per la selezione
 * 
 * @param use_columns Accetta 0 o 1 e permette di scegliere l'uso di colonne nella griglia delle opzioni
 * @param use_rows Accetta 0 o 1 e permette di scegliere l'uso di righe nella griglia delle opzioni
 * @param max_options Accetta valori >= 2 e indica il numero di opzioni che comporrà la griglia
 * @param max_columns Accetta valori > 0 e permette la scelta del numero di colonne che comporranno la griglia
 * @param max_rows Accetta valori > 0 e permette la scelta del numero di righe che comporranno la griglia
 * @param max_option_string_length Accetta valori maggiori di 3 e indica lo spazio massimo occupato dalle stringhe delle opzioni
 * @param path Indica il percorso di destinazione del file che conterrà le stringhe delle opzioni
 * 
 * @returns Il valore dell'opzione selezionata, mentre in caso di errore di qualsiasi tipo ne ritorna il codice.
 */
int initializeSelection (int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path) {
    int error_code = 0;
    char key_input;
    int i = 0;
    int x = 0;
    int y = 0;
    int selected_option = 0;
    char **options_strings;
    int *options_coords; //options_coords[n] = yyyxxx

    Settings settings;
    setSettings(&settings, use_columns, use_rows, max_options, max_columns, max_rows, max_option_string_length, path);

    error_code = checkSettings(settings);
    if (error_code != 0) {
        free(settings.path);
        return error_code;
    }

    options_strings = malloc(sizeof(char*) * settings.max_options);
    options_coords = malloc (sizeof(int) * settings.max_options);

    for (i = 0; i < settings.max_options; i++) {
        options_strings[i] = malloc (sizeof(char) * settings.max_option_string_length);
    }

    do{
        error_code = printOptionsStrings(settings, options_strings, selected_option);
        if (error_code != 0) {
            selected_option = error_code;
            break;
        }

        key_input = _getch();

        switch (key_input){
            case ENTER:
                break;
            case KEY_W:
                y--;
                break;
            case KEY_A:
                x--;
                break;
            case KEY_S:
                y++;
                break;
            case KEY_D:
                x++;
                break;
            default:
                return -300;
        }

        checkGridLimitOverflow (settings, &x, &y, key_input);

        selected_option = verifySelectedOptionCoords(settings, options_coords, x, y);
        if (selected_option < 0) {
            error_code = selected_option;
            return error_code;
        }

    }while(key_input != ENTER);


    for (i = 0; i < settings.max_options; i++) {
        free(options_strings[i]);
    }
    
    free(settings.path);
    free(options_coords);
    free(options_strings);
    
    if(selected_option >= 0) {
        return selected_option;
    }
    else{
        error_code = selected_option;
    }

    return error_code;
}

static void setSettings (Settings *p_settings, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path) {
    Settings settings = *p_settings;
    
    settings.use_columns = use_columns;
    settings.use_rows = use_rows;
    settings.max_options = max_options;
    settings.max_columns = max_columns;
    settings.max_rows = max_rows;
    settings.max_option_string_length = max_option_string_length;
    
    settings.path = malloc(strlen(path)+1);
    strcpy(settings.path, path);

    *p_settings = settings;
}

static int checkSettings (Settings settings) {
    int temporary;
    FILE *file;
    file = fopen(settings.path, "r");
    fclose(file);
    
    if (file == NULL) {
        return -404;
    }
    else if (settings.use_columns == FALSE && settings.use_rows == FALSE ) {
        return -200;
    }
    else if (settings.max_options < 2) {
        return -201;
    }
    else if (settings.max_columns <= 0 || settings.max_rows <= 0) {
        return -202;
    }
    else if ((settings.max_columns * settings.max_rows) < settings.max_options) {
        return -203;
    }
    else if ((settings.use_columns < 0 || settings.use_columns > 1) || (settings.use_rows < 0 || settings.use_rows > 1)) {
        return -204;
    }
    else if((settings.use_columns == 0 && settings.max_columns > 1) || (settings.use_rows == 0 && settings.max_rows > 1)) {
        return -205;
    }
    else if(settings.max_option_string_length < 3) {
        return -206;
    }
    else if ((settings.use_columns == TRUE && settings.use_rows == FALSE) && settings.max_columns > settings.max_options) {
        return -207;
    }
    else if ((settings.use_columns == FALSE && settings.use_rows == TRUE) && settings.max_rows > settings.max_options) {
        return -208;
    }
    else if ((settings.use_columns == 1 && settings.max_columns <= 1 )|| (settings.use_rows == 1 && settings.max_rows <= 1)) {
        return -209;
    }
    else if ((settings.max_columns * settings.max_rows) > settings.max_options) {
        temporary = ((settings.max_columns * settings.max_rows) - settings.max_options)-1;
        if (temporary > settings.max_columns-2) return -210;
    }

    return 0; /** ||@exception|| nessun errore ##################################################################################################### */
}

static int printOptionsStrings (Settings settings, char **options_strings, int selected_option) {
    int error_code;
    printf("\x1b[%d;%dH", 0, 0);
    printf("%s", ERASE_FROM_CURSOR_TO_ENDSCREEN);
    
    error_code = getStrings(settings, options_strings);

    if (error_code != 0) {
        return error_code;
    }

    if (settings.use_columns == TRUE && settings.use_rows == FALSE) {
        printOnOnlyColumnsGrid(settings, options_strings, selected_option);
    }
    else if (settings.use_columns == FALSE && settings.use_rows == TRUE) {
        printOnOnlyRowsGrid(settings, options_strings, selected_option);
    }
    else if (settings.use_columns == TRUE && settings.use_rows == TRUE) {
        printOnGrid(settings, options_strings, selected_option);
    }
    else {
        return -200;
    }

    return 0;
}

static int getStrings (Settings settings, char **options_strings) {
    int i = 0;
    FILE *file;
    char string[settings.max_option_string_length];

    file = fopen(settings.path, "r");

    if (file == NULL){
        return -404;
    }

    i = 0;
    while (fgets(string, settings.max_option_string_length, file) != NULL) {
        size_t length = strlen(string);

        if (length > 0 && string[length - 1] == '\n') {
            string[length - 1] = '\0';
        }

        if (i < settings.max_options) {
            strcpy(options_strings[i], string);
            i++;
        }
        else if (feof(file)) {
            break;
        }
        else if (!feof(file)){
            return -400;
            break;
        }
    }

    fclose(file);
    return 0;
}

static void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option) {
    int j;

    for(j=0; j<settings.max_columns; j++){
        printf("     ");

        if (j == selected_option) {
            printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[selected_option], INVERT_COLORS_FALSE);
        }
        else {
            printf("-- %s", options_strings[j]);
        }
    }
}

static void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option) {
    int j;

    for(j=0; j<settings.max_rows; j++){
        printf("\n     ");

        if (j == selected_option) {
            printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[selected_option], INVERT_COLORS_FALSE);
        }
        else {
            printf("-- %s", options_strings[j]);
        }
    }
}

static void printOnGrid (Settings settings, char **options_strings, int selected_option) {
    int i;
    int j;
    int current_option = 0;

    for (i = 0; i < settings.max_rows; i++) {

        for (j = 0; j < settings.max_columns && current_option < settings.max_options; j++) {
            printf("     ");

            if (current_option == selected_option) {
                printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[current_option], INVERT_COLORS_FALSE);
            }
            else {
                printf("-- %s", options_strings[current_option]);
            }

            current_option++;
        }

        printf("\n");
    }
}

static void checkGridLimitOverflow (Settings settings, int *p_x, int *p_y, char last_input) {
    int x = *p_x;
    int y = *p_y;
    int last_column_of_last_row;

    if(settings.use_columns == TRUE && settings.use_rows == TRUE){
        if ((settings.max_columns * settings.max_rows) > settings.max_options) {
            last_column_of_last_row = (settings.max_options - (settings.max_columns * (settings.max_rows-1)))-1;

            if((x < 0 && y == 0) || (x == 0 && y < 0)) {x = last_column_of_last_row; y = settings.max_rows-1;}
            if(y > settings.max_rows-2 && x > last_column_of_last_row && last_input == KEY_S) {x = last_column_of_last_row; y = settings.max_rows-1;}
            if((y > settings.max_rows-1 && x == last_column_of_last_row) && last_input == KEY_S) {x = 0; y = 0;}
            if((y == settings.max_rows-1 && x > last_column_of_last_row) && last_input == KEY_D) {x = 0; y = 0;}
        }
        if((x < 0 && y == 0) || (x == 0 && y < 0)) {x = settings.max_columns-1; y = settings.max_rows-1;}
        if(y < 0 && x != 0) {x--; y = 0;}
        if(y > settings.max_rows-1 && x != settings.max_columns-1) {x++; y = settings.max_rows-1;}

        if(x > settings.max_columns-1) {x = 0; y++;}
        if(x < 0) {x = settings.max_columns-1; y--;}
        if(y > settings.max_rows-1) {x = 0; y = 0;}
        if(y < 0) {x = 0; y = settings.max_rows-1;}
    }
    else if(settings.use_columns == TRUE && settings.use_rows == FALSE){
        if(y > 0){x++; y = 0;}
        if(y < 0){x--; y = 0;}
        if(x > settings.max_columns-1) x = 0;
        if(x < 0) x = settings.max_columns-1;
    }
    else if(settings.use_columns == FALSE && settings.use_rows == TRUE){
        if(x > 0){x = 0; y++;}
        if(x < 0){x = 0; y--;}
        if(y > settings.max_rows-1) y = 0;
        if(y < 0) y = settings.max_rows-1;
    }

    *p_x = x;
    *p_y = y;
}

static int verifySelectedOptionCoords(Settings settings, int *options_coords, int x, int y){
    int current_option;
    int converted_y;
    int converted_x;
    int cursor_position;

    coordGenerator(settings, options_coords);

    converted_y = y*1000;
    converted_x = x*1;
    cursor_position = converted_x + converted_y;

    for(current_option = 0; current_option < settings.max_options; current_option++){
        if (cursor_position == options_coords[current_option]) {
            return current_option;
        }
    }

    return -100;
}

static void coordGenerator(Settings settings, int *options_coords){
    int x = 0, y = 0, current_option = 0;

    for (y = 0; y < settings.max_rows; y++) {

        for (x = 0; x < settings.max_columns && current_option < settings.max_options; x++) {
            options_coords[current_option] = x + y*1000;
            current_option++;
        }
    }
}
