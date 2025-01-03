#include <stdio.h>
#include <conio.h>

#define ERASE_SCREEN "\033[2J"

// CURSORE:
#define MOVE_CUROSOR_TO_HOME "\033[H"

// COLORE DEL TESTO
#define TEXT_COLOR_RED "\033[1;31m"
#define TEXT_COLOR_RESET "\033[0;0m"

int checkOption(int error_code);
void printError(int error_code);

int checkOption(int error_code){
    printf("%s", MOVE_CUROSOR_TO_HOME);
    printf("%s", ERASE_SCREEN);
    int return_value = 0;

    if (error_code < 0){
        return_value = 1;
        printError(error_code);
    }

    return return_value;
}

void printError(int error_code){
    printf ("%s", TEXT_COLOR_RED);
    
    if (error_code <= -100 && error_code > -200) {
        printf("[ERRORE][COORDINATE]: ");
    }
    else if (error_code <= -200 && error_code > -300) {
        printf("[ERRORE][IMPOSTAZIONI]: ");
    }
    else if (error_code <= -300 && error_code > -400) {
        printf("[ERRORE][INPUT]: ");
    }
    else if (error_code <= -400 && error_code > -500 ) {
        printf("[ERRORE][FILE]: ");
    }
    else {
        printf("[ERRORE]: ");
    }

    /*
     * codice errore = da -100 a -199: problemi generici
     * codice errore = da -200 a -299: problemi relativi alle impostazioni
     * codice errore = da -300 a -399: problemi relativi all'input
     * codice errore = da -400 a -499: problemi relativi ai file
     * codice errore = da -500 in poi: errori imprevisti
     */
    switch (error_code){
        case -100:
            printf("confronto delle coordinate non riuscito");
            break;
        case -200:
            printf("almeno una tra le opzioni 'use_rows'/'use_columns' deve essere attiva");
            break;
        case -201:
            printf("devono essere possibili almeno 2 opzioni");
            break;
        case -202:
            printf("deve essere presente almeno una riga/colonna e piu' di una colonna/riga");
            break;
        case -203:
            printf("('max_columns' * 'max_rows') < 'max_options': impossibile contenere tutte le opzioni");
            break;
        case -204:
            printf("valori di 'use_columns'/'use_rows' errati, accattati solo 1/0 (true/false)");
            break;
        case -205:
            printf("'use_columns'/'use_rows' disattivato, quindi il numero di esso non puo' essere maggiore di 1");
            break;
        case -206:
            printf("valore di 'max_option_string_length' insufficente: max_option_string_length = {lunghezza_stringa}+2");
            break;
        case -207:
            printf("'max_columns'>'max_options' numero di colonne maggiore delle opzioni da contenere");
            break;
        case -208:
            printf("'max_rows'>'max_options' numero di righe maggiore delle opzioni da contenere");
            break;
        case -209:
            printf("'use_columns'/'use_rows' attivato quindi il valore di esso deve essere maggiore di 1");
            break;
        case -210:
            printf("troppe righe e/o colonne per contenere un numero di opzioni decisamente inferiore");
            break;
        case -211:
            printf("'start_x'/'start_y' non puo' essere minore di zero");
            break;
        case -300:
            printf("tasto premuto non valido");
            break;
        case -400:
            printf("file delle stringhe delle opzioni non terminato, rivedere i valori assegnati a 'max_options'/'max_option_string_length'");
            break;
        case -401:
            printf("almeno una stringa di un'opzione non e' stata dichiarata in modo corretto, ricontrollare il file e le impostazioni fornite");
            break;
        case -404:
            printf("file delle stringhe delle opzioni inesistente o percorso incorretto");
            break;
        default:
            printf("non definito");
            break;
    }

    printf(" (codice errore: %d)%s", error_code, TEXT_COLOR_RESET);

    printf("\n\n-- PREMERE [INVIO] PER PROSEGUIRE --");
    while(_getch() != '\r') continue;
}
