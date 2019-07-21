#ifndef _PLAYERH
#define _PLAYERH

#include <stdio.h>
#include <string.h>
#include "Words.h"

#define PLAYER_NAME_LENGTH 20


//struct player sera llamada simplemente como Player
typedef struct player {
    char name[PLAYER_NAME_LENGTH];
    int elapsedTime;
    int estadoPalabras[CANTIDAD_LETRAS];
    int buenas;
    int malas;
    int ganador;
    int letraActualIndex;
    int isActive;
    char clock[20];
    WordEntry* myDictionary;
} Player;

Player InitPlayer(char*);

#endif
