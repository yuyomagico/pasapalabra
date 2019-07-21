#include "InputManager.h"

int readyToEvaluateFlag;
int playerPassedFlag;

char inputText[MAX_INPUT_LENGTH] = "";
int inputTextPos = 0; 
Uint32 startGameTicks;

void HandleKeyboard(SDL_Event e){
	switch( e.key.keysym.sym )
	{
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
		case SDLK_RETURN2:
			readyToEvaluateFlag = 1;
			inputText[inputTextPos] = '\0';
			inputTextPos = 0;
		break;
		case SDLK_BACKSPACE:
			if(inputTextPos > 0)
				inputTextPos--;
				
			inputText[inputTextPos] = '\0';
		break;
		case SDLK_SPACE:
			SetPlayerPassed(1);
		break;
		default:
			//printf("otra tecla %c\n", e.key.keysym.sym);
			if(e.key.keysym.sym >= 65 && e.key.keysym.sym <= 122){
				if(inputTextPos < MAX_INPUT_LENGTH){
					inputText[inputTextPos] = e.key.keysym.sym;
					inputTextPos++;
				}
			}
		break;
	}
}

int PollEvents(){
    SDL_Event e;

	//Handle all events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			return 1;
		}
		else if( e.type == SDL_KEYDOWN){
			HandleKeyboard(e);
		}
	}
    return 0;
}

void SetPlayerPassed(int i){
	playerPassedFlag = i;
}

int GetPlayerPassed(){
	return playerPassedFlag;
}


void SetReadyToEvaluate(int value){
	readyToEvaluateFlag = value;
}

int GetReadyToEvaluate(){
	return readyToEvaluateFlag;
}

char* GetInputText(){
    return inputText;
}

void InitInput(){
	for(int i=0;i<MAX_INPUT_LENGTH;i++){
		inputText[i] = '\0';
	}
}

void StartTimer(){
    startGameTicks = SDL_GetTicks();
}