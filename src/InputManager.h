#ifndef _INPUTMANAGERH
#define _INPUTMANAGERH

#ifdef __linux__ 
	#include <SDL2/SDL.h>
	#include <stdio.h>
#elif _WIN32
	#include <SDL.h>
	#include <stdio.h>
#else
#endif

#define MAX_INPUT_LENGTH    200

extern Uint32 startGameTicks;

void HandleKeyboard(SDL_Event);
int PollEvents();

void SetPlayerPassed(int);
int GetPlayerPassed();

void SetReadyToEvaluate(int);
int GetReadyToEvaluate();

char* GetInputText();

void InitInput();
void StartTimer();

#endif