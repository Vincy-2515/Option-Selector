#include <stdio.h>

#define ERASE_SCREEN "\x1b[2J"

// CURSORE:
#define MOVE_CUROSOR_TO_HOME "\x1b[H"

// COLORE DEL TESTO
#define TEXT_COLOR_RED "\x1B[1;31m"
#define TEXT_COLOR_RESET "\x1B[0;0m"

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
    /*
     * codice errore = da -100 a -199: problemi generici
     * codice errore = da -200 a -299: problemi relativi alle impostazioni
     * codice errore = da -300 a -399: problemi relativi all'input
     * codice errore = da -400 a -499: problemi relativi ai file
     * codice errore = da -500 in poi: errori imprevisti
     */
    switch (error_code){

    case -404:
        printf("%s[ERRORE]: file delle stringhe delle opzioni inesistente o percorso incorretto", TEXT_COLOR_RED);
        break;
    case -400:
        printf("%s[ERRORE]: file delle stringhe delle opzioni non terminato, rivedere il numero massimo di opzioni assegnate", TEXT_COLOR_RED);
        break;
    case -200:
        printf("%s[ERRORE]: almeno una tra le opzioni righe/colonne deve essere attiva", TEXT_COLOR_RED);
        break;
    case -201:
        printf("%s[ERRORE]: devono essere possibili almeno 2 opzioni", TEXT_COLOR_RED);
        break;
    case -202:
        printf("%s[ERRORE]: deve essere presente almeno una riga/colonna e piu' di una colonna/riga", TEXT_COLOR_RED);
        break;
    case -203:
        printf("%s[ERRORE]: numero di righe/colonne insufficienti per contenere le opzioni", TEXT_COLOR_RED);
        break;
    case -204:
        printf("%s[ERRORE]: valori di 'use_columns'/'use_rows' errati, accattati solo 1/0 (true/false)", TEXT_COLOR_RED);
        break;
    case -205:
        printf("%s[ERRORE]: 'use_columns'/'use_rows' disattivato, quindi il numero di esso non puo' essere maggiore di 1 ", TEXT_COLOR_RED);
        break;
    case -300:
        printf("%s[ERRORE]: tasto premuto non valido", TEXT_COLOR_RED);
        break;
    case -100:
        printf("%s[ERRORE]: coordinate non valide", TEXT_COLOR_RED);
        break;
    default:
        printf("%s[ERRORE]: non definito", TEXT_COLOR_RED);
        break;
    }

    printf(" (codice errore: %d)%s", error_code, TEXT_COLOR_RESET);

    printf("\n\n-- PREMERE [INVIO] PER PROSEGUIRE --");
    getchar();
}
