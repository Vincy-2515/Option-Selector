#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//IMPOSTAZIONI (modificabili solo da "getSettings()"):
struct Settings {
    int use_columns;
    int use_rows;
    int max_options;
    int max_columns;
    int max_rows;
    int max_line_length;

    //percorso dei file di impostazioni
    char strings_filename[200];
    char settings_filename[200];
};

struct Settings settings;

#define TRUE 1
#define FALSE 0

//TASTI:
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define ENTER '\r'

//ESCAPE CODES:
#define ERASE_FROM_CURSOR_TO_ENDSCREEN "\x1B[0J"
#define INVERT_COLORS_TRUE "\x1B[7m"
#define INVERT_COLORS_FALSE "\x1B[27m"

//DICHIARAZIONE FUNZIONI:
int initializeSelection (int requested_option_list);
static void getSettings (int list_choice);

static int getStrings (char **options_strings);
static int printOptionsStrings (char **options_strings, int selected_option);
static void printOnOnlyColumnsGrid (char **options_strings, int selected_option);
static void printOnOnlyRowsGrid (char **options_strings, int selected_option);
static void printOnGrid (char **options_strings, int selected_option);

static void checkGridLimitOverflow (int *x, int *y);
static int verifySelectedOptionCoords (int *options_coords, int x, int y);
static void coordGenerator (int *options_coords);

int initializeSelection (int requested_option_list) {
    int error_code = 0;
    char key_input;
    int i = 0;
    int x = 0;
    int y = 0;
    int selected_option = 0;
    char **options_strings;
    int *options_coords;

    getSettings (requested_option_list);

    options_strings = malloc(sizeof(char*) * settings.max_options);
    options_coords = malloc (sizeof(int) * settings.max_options);

    for (i = 0; i < settings.max_options; i++) {
        options_strings[i] = malloc (sizeof(char) * settings.max_line_length);
    }

    do{
        error_code = printOptionsStrings(options_strings, selected_option);

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
                return -3;
        }

        checkGridLimitOverflow (&x, &y);

        selected_option = verifySelectedOptionCoords(options_coords, x, y);

        if (selected_option < 0) {
            return selected_option;
        }

    }while(key_input != ENTER);


    for (i = 0; i < settings.max_options; i++) {
        free(options_strings[i]);
    }
    
    free(options_coords);
    free(options_strings);
    
    return selected_option;
}

static void getSettings (int list_choice) {
    FILE *file;

    switch(list_choice){
        case 1:
        
            strcpy(settings.settings_filename, "src/resources/selection_one/options_settings.txt");
            strcpy(settings.strings_filename, "src/resources/selection_one/options_strings.txt");
            break;
        case 2:
            strcpy(settings.settings_filename, "src/resources/selection_two/options_settings.txt");
            strcpy(settings.strings_filename, "src/resources/selection_two/options_strings.txt");
            break;
    }

    //#########################################################################################
    //#################################### DA ELIMINARE #######################################
    //#########################################################################################
        file  = fopen (settings.settings_filename, "r");
        fscanf (file, 
                "use_columns:%d use_rows:%d max_options:%d max_columns:%d max_rows:%d max_line_length:%d",
                &settings.use_columns,
                &settings.use_rows,
                &settings.max_options,
                &settings.max_columns,
                &settings.max_rows,
                &settings.max_line_length
            );


        fclose (file);
    //---
}

static int printOptionsStrings (char **options_strings, int selected_option) {
    int error_code;
    printf("\x1b[%d;%dH", 0, 0);
    printf("%s", ERASE_FROM_CURSOR_TO_ENDSCREEN);
    
    error_code = getStrings(options_strings);

    if (error_code != 0) {
        return error_code;
    }

    if (settings.use_columns == TRUE && settings.use_rows == FALSE) {
        printOnOnlyColumnsGrid(options_strings, selected_option);
    }
    else if (settings.use_columns == FALSE && settings.use_rows == TRUE) {
        printOnOnlyRowsGrid(options_strings, selected_option);
    }
    else if (settings.use_columns == TRUE && settings.use_rows == TRUE) {
        printOnGrid(options_strings, selected_option);
    }
    else {
        return -2;
    }

    return 0;
}

static int getStrings (char **options_strings) {
    int i = 0;
    FILE *file;
    char string[settings.max_line_length];

    file = fopen(settings.strings_filename, "r");

    if (file == NULL){
        return -1;
    }

    i = 0;
    while (fgets(string, settings.max_line_length, file) != NULL) {
        size_t length = strlen(string);

        if (length > 0 && string[length - 1] == '\n') {
            string[length - 1] = '\0';
        }

        if (i < settings.max_options) {
            strcpy(options_strings[i], string);
            i++;
        } 
        else {
            break;
        }
    }

    fclose(file);
    return 0;
}

static void printOnOnlyColumnsGrid (char **options_strings, int selected_option) {
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

static void printOnOnlyRowsGrid (char **options_strings, int selected_option) {
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

static void printOnGrid (char **options_strings, int selected_option) {
    int i;
    int j;
    int current_option = 0;

    for (i = 0; i < settings.max_rows; i++) {

        for (j = 0; j < settings.max_columns; j++) {
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

static void checkGridLimitOverflow (int *x, int *y) {
    if(settings.use_columns == TRUE && settings.use_rows == TRUE){
        if((*x < 0 && *y == 0) || (*x == 0 && *y < 0)) {*x = settings.max_columns-1; *y = settings.max_rows-1;}
        if(*y < 0 && *x != 0) {(*x)--; *y = 0;}
        if(*y > settings.max_rows-1 && *x != settings.max_columns-1) {(*x)++; *y = settings.max_rows-1;}
        if(*x > settings.max_columns-1) {*x = 0; (*y)++;}
        if(*x < 0) {*x = settings.max_columns-1; (*y)--;}
        if(*y > settings.max_rows-1) {*x = 0; *y = 0;}
        if(*y < 0) {*x = 0; *y = settings.max_rows-1; }
    }

    if(settings.use_columns == TRUE && settings.use_rows == FALSE){
        if(*x < 0) *x = settings.max_columns-1;
        if(*x > settings.max_columns-1) *x = 0;
        if(*y < 0){(*x)++; *y = 0;}
        if(*y > 0){(*x)--; *y = 0;}
    }

    if(settings.use_columns == FALSE && settings.use_rows == TRUE){
        if(*x < 0){*x = 0; (*y)--;}
        if(*x > 0){*x = 0; (*y)++;}
        if(*y < 0) *y = settings.max_rows-1;
        if(*y > settings.max_rows-1) *y = 0;
    }
}

static int verifySelectedOptionCoords(int *options_coords, int x, int y){
    int selected_option;
    int converted_y;
    int converted_x;
    int cursor_position;

    coordGenerator(options_coords);

    converted_y = y*1000;
    converted_x = x*1;
    cursor_position = converted_x + converted_y;

    for(selected_option=0; selected_option < settings.max_options; selected_option++){
        if (cursor_position == options_coords[selected_option]) {
            return selected_option;
        }
    }

    return -4;
}

static void coordGenerator(int *options_coords){
    int x = 0, y = 0, option = 0;

    for (y = 0; y < settings.max_rows; y++) {

        for (x = 0; x < settings.max_columns; x++) {
            // options_coords[n] = yyyxxx
            options_coords[option] = x + y*1000;
            option++;
        }
    }
}
