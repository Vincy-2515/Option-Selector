#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//TASTI:
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define ENTER '\r'

//ESCAPE CODES:
#define DEL_CRS_TO_ENDSCR "\x1B[0J" //cancella dalla posizione del cursore fino alla fine della finestra
#define CHR_INV_T "\x1B[7m" //inverte colori carattere: true
#define CHR_INV_F "\x1B[27m" //inverte colori carattere: false

//DICHIARAZIONE FUNZIONI:
int initializeSelection(int requested_option_list);
int verifySelectedOptionCoords(int x, int y, int max_options, int max_rows, int max_columns);
void checkGridLimitOverflow (int* p_x, int* p_y, int use_columns, int use_rows, int max_columns, int max_rows);
void printOptionsStrings(char strings_filename[], int selected_option, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_line_length);
void printOnOnlyColumnsGrid (char **options_strings, int selected_option, int max_columns);
void printOnOnlyRowsGrid (char **options_strings, int selected_option, int max_rows);
void printOnGrid (char **options_strings, int selected_option, int max_options, int max_columns);
char **getStrings(char strings_filename[], int max_options, int max_line_length);
void getSettings(char settings_filename[], char strings_filename[],int list_choice, int *p_use_columns, int *p_use_rows, int *p_max_options, int *p_max_columns, int *p_max_rows, int *p_max_line_length);
void coord_generator(int options_coords[], int max_rows, int max_columns);

int initializeSelection(int requested_option_list){
    char key_input;
    int x = 0; 
    int y = 0;
    int selected_option = 0;

    int use_columns; //"true" se le opzioni vanno solo nella prima riga
    int use_rows; //"true" se le opzioni vanno solo nella prima colonna
    int max_options; //numero delle opzioni
    int max_columns; //numero delle colonne
    int max_rows; //numero delle righe
    int max_line_length; //lunghezza massima di una riga

    char settings_filename[200];
    char strings_filename[200];

    getSettings (settings_filename, strings_filename, requested_option_list, &use_columns, &use_rows, &max_options, &max_columns, &max_rows, &max_line_length);

    do{
        printOptionsStrings(strings_filename, selected_option, use_columns, use_rows, max_options, max_columns, max_rows, max_line_length);

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
                return -1;
        }

        checkGridLimitOverflow (&x, &y, use_columns, use_rows, max_columns, max_rows);

        selected_option = verifySelectedOptionCoords(x, y, max_options, max_rows, max_columns);

    }while(key_input!=ENTER);

    return selected_option;
}

int verifySelectedOptionCoords(int x, int y, int max_options, int max_rows, int max_columns){
    int options_coords[max_options];
    int selected_option;
    int converted_y;
    int converted_x;
    int cursor_pos;

    /*
     * tramite la funzione coord_generator() avviene la generazione 
     * delle coordinate rispettando la quantità di colonne e righe
     * prestabilite nelle impostazioni la memorizzazione avviene 
     * in una singola posizione del vettore nel segente modo:
     * options_coords[n] = yyy.xxx;
     */
    coord_generator(options_coords, max_rows, max_columns);

    //conversione delle coordinate di posizione del cursore nel formato yyy.xxx
    converted_y = y*1000;
    converted_x = x*1;
    cursor_pos = converted_x + converted_y;

    //confronto della posizione del cursore rispetto a quella delle opzioni
    for(selected_option=0; selected_option<max_options-1; selected_option++){
        if(cursor_pos == options_coords[selected_option]) return selected_option;
    }

    return -2;
}

void checkGridLimitOverflow (int* p_x, int* p_y, int use_columns, int use_rows, int max_columns, int max_rows){
    int x = *p_x;
    int y = *p_y;
    /*
     * nella parte del codice che segue imposto
     * x e y diversamente se i loro valori
     * eccedono i valori della pseudo-griglia
     * che contiene le opzioni
     */
    if(use_columns == true && use_rows == true){
        if(x > max_columns-1) {x=0; y++;}
        if(x < 0) {x=max_columns-1; y--;}
        if(y > max_rows-1) {y=0; x=0;}
        if(y < 0) {y=max_rows-1; x=0;}
    }

    if(use_columns == true && use_rows == false){
        if(y < 0){y=0; x++;}
        if(y > 0){y=0; x--;}
        if(x < 0) x=max_columns-1;
        if(x > max_columns-1) x=0;
    }

    if(use_columns == false && use_rows == true){
        if(x < 0){x=0; y--;}
        if(x > 0){x=0; y++;}
        if(y < 0) y=max_rows-1;
        if(y > max_rows-1) y=0;
    }
}

void printOptionsStrings(char strings_filename[], int selected_option, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_line_length){
    //elimino le opzioni stampate precedentemente
    printf("\x1b[%d;%dH", 8, 0);
    printf("%s", DEL_CRS_TO_ENDSCR);
    
    char **options_strings = getStrings(strings_filename, max_options, max_line_length);

    if (use_columns == true && use_rows == false) {
        printOnOnlyColumnsGrid(options_strings, selected_option, max_columns);
    }

    else if (use_columns == false && use_rows == true) {
        printOnOnlyRowsGrid(options_strings, selected_option, max_rows);
    }

    else if (use_columns == true && use_rows == true) {
        printOnGrid(options_strings, selected_option, max_options, max_columns);
    }
}

void printOnOnlyColumnsGrid (char **options_strings, int selected_option, int max_columns){
    int j;

    for(j=0; j<max_columns; j++){
        printf("     ");
        if(j == selected_option) printf(">> %s%s%s", CHR_INV_T, options_strings[selected_option], CHR_INV_F);
        else printf("-- %s", options_strings[j]);
    }
}

void printOnOnlyRowsGrid (char **options_strings, int selected_option, int max_rows){
    int j;

    for(j=0; j<max_rows; j++){
        printf("\n     ");
        if(j == selected_option){
            printf(">> %s%s%s", CHR_INV_T, options_strings[selected_option], CHR_INV_F);
        }
        else printf("-- %s", options_strings[j]);
    }
}

void printOnGrid (char **options_strings, int selected_option, int max_options, int max_columns){
    int j;
    int count;
    for(j=0; j<max_options; j++){
        for(j=0; count<max_options && j<max_columns; j++){
            printf("     ");
            if(count == selected_option) {
                printf(">> %s%s%s", CHR_INV_T, options_strings[selected_option], CHR_INV_F);
            }
            else {
                printf("-- %s", options_strings[count]);
            }
            count++;
        }
        printf("\n");
    }
    count = 0;
}

void getSettings(char settings_filename[], char strings_filename[], int list_choice, int *p_use_columns, int *p_use_rows, int *p_max_options, int *p_max_columns, int *p_max_rows, int *p_max_line_length){
    int use_columns = *p_use_columns;
    int use_rows = *p_use_rows;
    int max_options = *p_max_options;
    int max_columns = *p_max_columns;
    int max_rows = *p_max_rows;
    int max_line_length = *p_max_line_length;

    FILE *file;

    switch(list_choice){
        case 1:
            strcpy(settings_filename, "resources/selection_one/optiffons_settings.txt");
            strcpy(strings_filename, "resources/selection_one/options_strings.txt");
            break;
        case 2:
            strcpy(settings_filename, "resources/selection_two/options_settings.txt");
            strcpy(strings_filename, "resources/selection_two/options_strings.txt");
            break;
    }

    file  = fopen (settings_filename, "r");
    fscanf (file, "use_columns:%d use_rows:%d max_options:%d max_columns:%d max_rows:%d max_line_length:%d",&use_columns, &use_rows, &max_options, &max_columns, &max_rows, &max_line_length);

    fclose (file);
}

char **getStrings(char strings_filename[], int max_options, int max_line_length){
    int i=0;
    FILE *file;
    char string[max_line_length];
    char **options_strings;

    options_strings = malloc(sizeof(char*) * max_options);
    for (i=0; i<max_options; i++) {
        options_strings[i] = malloc(sizeof(char) * max_line_length);
    }
    
    file = fopen(strings_filename, "r"); //apro l'accesso al file

        //stampo a schermo un eventuale errore nell' apertura del file
        if(file == NULL) perror("[ERRORE]");


        while(!feof(file) && !ferror(file)){

            //sposto temporaneamente la riga di testo nel vettore "string" solo se non ritorna NULL
            if (fgets(string, max_line_length, file) != NULL) i++;

        //scambio il "\n" alla fine della riga con "\0" (\0: codice ASCII di fine stringa)
            size_t len = strlen(string);
            if (len > 0 && string[len - 1] == '\n') {
                string[len - 1] = '\0';
            }
        //---

            strcpy(options_strings[i-1], string); //conservo la stringa in nel vettore "optionStrings"
        }

    fclose(file); //chiudo l'accesso al file

    return options_strings;
}

void coord_generator(int options_coords[], int max_rows, int max_columns){
    int x, y, option=0;

    for(y=0; y<max_rows; y++){
        for(x=0; x<max_columns; x++){
            options_coords[option] = x + y*1000;
            option++;
        }
    }
}
