#include "GameManager.h"

Player players[MAX_PLAYERS];
int currentPlayerTurn = 0;
int gameOver = 0;

int LoadGame(){
    if(InitSDL() != 0){
        return 1;
    }else{
        if(CreateResources() != 0){
            return 2;
        }
        InitPlayers();
        StartTimer();
        return 0;
    }
}

int PlayGame(){
    // Check all Input events
    if(PollEvents() != 0){
        CleanResources();
        CloseSDL();
        return 1;
    }else{
        if(gameOver != 1){
            UpdateTimers();
            ProcessInputs();
            UpdateGUI();
        }else{
            UpdateGUI();
        }
        return 0;
    }
}

void InitPlayers(){
    for(int p=0; p<MAX_PLAYERS;p++){
        players[p] = InitPlayer("playerX");
        //TODO: Assign Real Words
        AssignSampleWords(players[p].palabras, players[p].descripciones, p);
    }
}

void SetCurrentPlayerTurn(int i){
    currentPlayerTurn = i;
}
int GetCurrentPlayerTurn(){
    return currentPlayerTurn;
}

void ProcessInputs(){
    int playerTurn = GetCurrentPlayerTurn();
    if(GetReadyToEvaluate() == 1){
        if(strcmp(GetInputText(), players[playerTurn].palabras[players[playerTurn].letraActualIndex]) != 0){
            //mala
            players[playerTurn].malas++;
            players[playerTurn].estadoPalabras[players[playerTurn].letraActualIndex] = PALABRA_MALA;
            if(players[playerTurn].malas + players[playerTurn].buenas == CANTIDAD_LETRAS){
                players[playerTurn].isActive = 0;
            }else{
                int nextLetter = IndexOfNextPendingWord();
                if( nextLetter != -1){
                    players[playerTurn].letraActualIndex = nextLetter;
                }
            }
            GetNextActivePlayer();
        }else{
            players[playerTurn].buenas++;
            players[playerTurn].estadoPalabras[players[playerTurn].letraActualIndex] = PALABRA_BUENA;

            if(players[playerTurn].malas + players[playerTurn].buenas == CANTIDAD_LETRAS){
                players[playerTurn].isActive = 0;
            }else{
                if(players[playerTurn].buenas == CANTIDAD_LETRAS){
                    players[playerTurn].ganador = 1;
                    FinishGame();
                }else{
                    int nextLetter = IndexOfNextPendingWord();
                    if( nextLetter != -1){
                        players[playerTurn].letraActualIndex = nextLetter;
                    }else{
                        GetNextActivePlayer();
                    }
                }
            }
        }
        InitInput();
        SetReadyToEvaluate(0);
    }
    else if(GetPlayerPassed() == 1){
        players[playerTurn].estadoPalabras[players[playerTurn].letraActualIndex] = PALABRA_PENDIENTE;
        int nextLetter = IndexOfNextPendingWord();
        if( nextLetter != -1){
            players[playerTurn].letraActualIndex = nextLetter;
        }
        GetNextActivePlayer();
        
        InitInput();

        SetPlayerPassed(0);
    }else{
        if(gameOver != 1)
            players[playerTurn].estadoPalabras[players[playerTurn].letraActualIndex] = PALABRA_ACTUAL;
    }
}

void UpdateTimers(){
    int playerTurn = GetCurrentPlayerTurn();
    int totalElapsedTime = 0;

    //Calcualte total elapsed time - player time;
    for(int p=0; p<MAX_PLAYERS;p++){
        if(p != playerTurn){
            totalElapsedTime+=players[p].elapsedTime;
        }
    }

    if(players[playerTurn].elapsedTime > MAX_TIME){
        players[playerTurn].estadoPalabras[players[playerTurn].letraActualIndex] = PALABRA_PENDIENTE;
        players[playerTurn].isActive = 0;
        sprintf(players[playerTurn].clock, "TimeOut");
        GetNextActivePlayer();
    }else{
        players[playerTurn].elapsedTime = SDL_GetTicks()- startGameTicks - totalElapsedTime;
        int t_secs = (MAX_TIME-players[playerTurn].elapsedTime)/1000;
        int minutes = t_secs/60;
        int tenth_secs = t_secs%60/10;
        int secs = (t_secs%60)%10;
        sprintf(players[playerTurn].clock, "%d:%d%d",minutes, tenth_secs, secs);
    }
}

void GetNextActivePlayer(){    
    int nextValidPlayer = -1;
    int nextPlayer = GetCurrentPlayerTurn();
    for(int checks = 0; checks < MAX_PLAYERS; checks++){
        nextPlayer = (nextPlayer+1) % MAX_PLAYERS;
        if(players[nextPlayer].isActive){
            nextValidPlayer = nextPlayer;
            break;
        }
    }

    if(nextValidPlayer != -1){
        SetCurrentPlayerTurn(nextValidPlayer);
        players[nextValidPlayer].estadoPalabras[players[nextValidPlayer].letraActualIndex] = PALABRA_ACTUAL;
    }else{
        FinishGame();
    }
}

int IndexOfNextPendingWord(){
    int nextValidWord = -1;
    int playerTurn = GetCurrentPlayerTurn();
    int nextLetter = players[playerTurn].letraActualIndex;
    for(int checks = 0; checks < CANTIDAD_LETRAS; checks++){
        nextLetter = (nextLetter+1) % CANTIDAD_LETRAS;
        if(players[playerTurn].estadoPalabras[nextLetter] == PALABRA_PENDIENTE){
            nextValidWord = nextLetter;
            break;
        }
    }
    return nextValidWord;
}


void FinishGame(){
    gameOver = 1;
    //chequear por un ganador
    for(int p=0; p<MAX_PLAYERS; p++){
        if(players[p].ganador == 1){
            SetWinner(p);
            return;
        }
    }

    //si no hay ganadores, chequear el mas buenas
    int maxBuenasIndex = 0;
    int cantPlayersMax = 0;
    for(int p=0; p<MAX_PLAYERS-1; p++){
        if(players[p+1].buenas > players[maxBuenasIndex].buenas){
            maxBuenasIndex = p;
            cantPlayersMax++;
        }
    }
    if(cantPlayersMax == 1){
        SetWinner(maxBuenasIndex);
        return;
    }
    //si no hay mas buenas, chequear menos malas
    int menosMalasIndex = 0;
    int cantPlayersMin = 0;
    for(int p=0; p<MAX_PLAYERS-1; p++){
        if(players[p+1].malas < players[menosMalasIndex].malas){
            menosMalasIndex = p;
            cantPlayersMin++;
        }
    }
    if(cantPlayersMin == 1){
        SetWinner(menosMalasIndex);
        return;
    }

    //si no hay menos malas, declarar empate
    SetWinner(-1);
}

void SetWinner(int p){
    if(p != -1){
        SetCurrentPlayerTurn(p);
        strcpy(players[p].clock, "GANADOR");
    }else{
        for(int p = 0; p< MAX_PLAYERS;p++){
            SetCurrentPlayerTurn(p);
            strcpy(players[p].clock, "EMPATE");
        }
    }
}