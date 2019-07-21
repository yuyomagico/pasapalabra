#ifndef _GAMEMANAGERH
#define _GAMEMANAGERH

#include <stdio.h>
#include "Player.h"
#include "Words.h"
#include "Renderer.h"
#include "InputManager.h"

#define MAX_PLAYERS 2
#define MAX_TIME    12000

extern Player players[MAX_PLAYERS];
extern int gameOver;

int LoadGame();
int PlayGame();

void InitPlayers();
void SetCurrentPlayerTurn(int);
int GetCurrentPlayerTurn();
void ProcessInputs();
void UpdateTimers();
void GetNextActivePlayer();
int IndexOfNextPendingWord();
void FinishGame();
void SetWinner(int);

#endif