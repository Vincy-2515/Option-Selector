#include <stdio.h>
#include <string.h>


/*
 * una struct è una collezione di attributi 
 * accessibili a tutte le funzioni, sono
 * molto simili alle classi di altri linguaggi
*/
struct Player {
    char name[20];
    int score;
};

int main () {
    struct Player player1;
    struct Player player2;

    //impostazione dei valori del primo player
    strcpy(player1.name, "primo_giocatore"); // ---> nomeStruct.variabile
    player1.score = 4;

    //impostazione dei valori del primo player
    strcpy(player2.name, "secondo_giocatore");
    player2.score = 5;

    //visualizzazione
    printf("\ngiocatore:%s", player1.name);
    printf("\npunteggio:%d", player1.score);

    printf("\n\ngiocatore:%s", player2.name);
    printf("\npunteggio:%d", player2.score);
}