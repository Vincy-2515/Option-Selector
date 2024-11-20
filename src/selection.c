#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//IMPOSTAZIONI (modificabili solo da "getSettings()"):
struct Settings {
    int use_columns; //"true" se le opzioni vanno solo nella prima riga
    int use_rows; //"true" se le opzioni vanno solo nella prima colonna
    int max_options; //numero delle opzioni
    int max_columns; //numero delle colonne
    int max_rows; //numero delle righe
    int max_line_length; //lunghezza massima di una riga

    //percorso dei file di impostazioni
    char strings_filename[200];
    char settings_filename[200];
};

struct Settings settings;

//TASTI:
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define ENTER '\r'

//ESCAPE CODES:
#define ERASE_FROM_CURSOR_TO_ENDSCREEN "\x1B[0J" //cancella dalla posizione del cursore fino alla fine della finestra
#define INVERT_COLORS_TRUE "\x1B[7m" //inverte colori carattere: true
#define INVERT_COLORS_FALSE "\x1B[27m" //inverte colori carattere: false

//DICHIARAZIONE FUNZIONI:
int initializeSelection(int requested_option_list);
void getSettings(int list_choice);
int verifySelectedOptionCoords(int x, int y);
void checkGridLimitOverflow (int* p_x, int* p_y);
void printOptionsStrings(int selected_option);
void printOnOnlyColumnsGrid (char **options_strings, int selected_option);
void printOnOnlyRowsGrid (char **options_strings, int selected_option);
void printOnGrid (char **options_strings, int selected_option);
char **getStrings();
void coord_generator(int options_coords[]);

int initializeSelection(int requested_option_list){
    char key_input;
    int x = 0; 
    int y = 0;
    int selected_option = 0;

    getSettings (requested_option_list);

    do{
        printOptionsStrings(selected_option);

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

        checkGridLimitOverflow (&x, &y);

        selected_option = verifySelectedOptionCoords(x, y);
        if (selected_option < 0) return selected_option;

    }while(key_input!=ENTER);

    return selected_option;
}

void getSettings(int list_choice){
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
}

int verifySelectedOptionCoords(int x, int y){
    int options_coords[settings.max_options];
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
    coord_generator(options_coords);

    //conversione delle coordinate di posizione del cursore nel formato yyy.xxx
    converted_y = y*1000;
    converted_x = x*1;
    cursor_pos = converted_x + converted_y;

    //confronto della posizione del cursore rispetto a quella delle opzioni
    for(selected_option=0; selected_option < settings.max_options - 1; selected_option++){
        if(cursor_pos == options_coords[selected_option]) return selected_option;
    }

    return -2;
}

void checkGridLimitOverflow (int* p_x, int* p_y){
    int x = *p_x;
    int y = *p_y;
    /*
     * nella parte del codice che segue imposto
     * x e y diversamente se i loro valori
     * eccedono i valori della pseudo-griglia
     * che contiene le opzioni
     */
    if(settings.use_columns == true && settings.use_rows == true){
        if(x > settings.max_columns-1) {x=0; y++;}
        if(x < 0) {x=settings.max_columns-1; y--;}
        if(y > settings.max_rows-1) {y=0; x=0;}
        if(y < 0) {y=settings.max_rows-1; x=0;}
    }

    if(settings.use_columns == true && settings.use_rows == false){
        if(y < 0){y=0; x++;}
        if(y > 0){y=0; x--;}
        if(x < 0) x=settings.max_columns-1;
        if(x > settings.max_columns-1) x=0;
    }

    if(settings.use_columns == false && settings.use_rows == true){
        if(x < 0){x=0; y--;}
        if(x > 0){x=0; y++;}
        if(y < 0) y=settings.max_rows-1;
        if(y > settings.max_rows-1) y=0;
    }
}

void printOptionsStrings(int selected_option){
    //elimino le opzioni stampate precedentemente
    printf("\x1b[%d;%dH", 0, 0);
    printf("%s", ERASE_FROM_CURSOR_TO_ENDSCREEN);
    
    char **options_strings = getStrings(); //contiene \r\r\r\r\r\r\r\r\r\r\r\r RISOLVERE

    if (settings.use_columns == true && settings.use_rows == false) {
        printOnOnlyColumnsGrid(options_strings, selected_option);
    }

    else if (settings.use_columns == false && settings.use_rows == true) {
        printOnOnlyRowsGrid(options_strings, selected_option);
    }

    else if (settings.use_columns == true && settings.use_rows == true) {
        printOnGrid(options_strings, selected_option);
    }
}

void printOnOnlyColumnsGrid (char **options_strings, int selected_option){
    int j;

    for(j=0; j<settings.max_columns; j++){
        printf("     ");
        if(j == selected_option) printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[selected_option], INVERT_COLORS_FALSE);
        else printf("-- %s", options_strings[j]);
    }
}

void printOnOnlyRowsGrid (char **options_strings, int selected_option){
    int j;

    for(j=0; j<settings.max_rows; j++){
        printf("\n     ");
        if(j == selected_option){
            printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[selected_option], INVERT_COLORS_FALSE);
        }
        else printf("-- %s", options_strings[j]);
    }
}

void printOnGrid (char **options_strings, int selected_option){
    int j;
    int count = 0;
    for(j=0; j<settings.max_options; j++){
        for(j=0; count<settings.max_options && j<settings.max_columns; j++){
            printf("     ");
            if(count == selected_option) {
                printf(">> %s%s%s", INVERT_COLORS_TRUE, options_strings[selected_option], INVERT_COLORS_FALSE);
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

char **getStrings(){
    int i=0;
    FILE *file;
    char string[settings.max_line_length];
    char **options_strings;

    options_strings = malloc(sizeof(char*) * settings.max_options);
    for (i=0; i < settings.max_options; i++) {
        options_strings[i] = malloc(sizeof(char) * settings.max_line_length);
    }
    
    file = fopen(settings.strings_filename, "r");

    if(file == NULL) perror("[ERRORE]");
    
    i=0;
    while (fgets(string, settings.max_line_length, file) != NULL) {
        // Scambio il "\n" alla fine della riga con "\0"
        size_t len = strlen(string);
        if (len > 0 && string[len - 1] == '\n') {
            string[len - 1] = '\0';
        }

        if (i < settings.max_options) {
            strcpy(options_strings[i], string);
            i++;
        } else {
            break;
        }
    }


    fclose(file); //chiudo l'accesso al file

    return options_strings;
}

void coord_generator(int options_coords[]){
    int x, y, option=0;

    for(y=0; y<settings.max_rows; y++){
        for(x=0; x<settings.max_columns; x++){
            options_coords[option] = x + y*1000;
            option++;
        }
    }
}
