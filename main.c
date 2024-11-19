#include <stdio.h>
#include <windows.h>
#include "src/selection.h"

int main () {
    int option1;
    int option2;

    system("clear");
    system("cls");

    option1 = initializeSelection(1);
    option2 = initializeSelection(2);

    //FARE IN MODO DA POTER ASSEGNARE ALLE FUNZIONI LE IMPOSTAZIONI
    //USA LE STRUCT

    printf("op1: %d", option1);
    printf("op2: %d", option2);

    return 0;
}