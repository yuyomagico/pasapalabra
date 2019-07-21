#include "Player.h"

Player InitPlayer(char* name){
    Player newPlayer;
    if(strlen(name) > PLAYER_NAME_LENGTH){
        name[PLAYER_NAME_LENGTH-1] = '\0';
    }
    strcpy(newPlayer.name, name);
    newPlayer.elapsedTime = 0;
    newPlayer.buenas = 0;
    newPlayer.malas = 0;
    newPlayer.ganador = 0;
    newPlayer.letraActualIndex = 0;
    newPlayer.isActive = 1;
    strcpy(newPlayer.clock,"");
    
    for(int i=0; i<CANTIDAD_LETRAS; i++){
        newPlayer.estadoPalabras[i]=PALABRA_PENDIENTE;
    }

    return newPlayer;
}
