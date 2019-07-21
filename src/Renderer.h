#ifndef _RENDERERH
#define _RENDERERH

#include <stdio.h>
#include "Words.h"

#ifdef __linux__ 
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <stdio.h>
#elif _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
	#include <stdio.h>
#else
#endif

#define PLAYER_SCREEN_WIDTH			640
#define PLAYER_SCREEN_HEIGHT		480
#define FONT_SIZE					24

//## Variable Declarations (extern es para evitar que tome la definicion de la variable en el header, y sepa que se definira en el .c)



//## Functions
//Renderer Initializes SDL Library
int InitSDL();
//Closes SDL
void CloseSDL();

//Creates Graphics Resources (Textures & Fonts)
int CreateResources();
//Cleans Graphic Resources
void CleanResources();
//Loads all used Textures
int LoadTextures();
//Loads all used Fonts
int LoadFonts();

//Loads a single Texture
SDL_Texture* LoadTexture( char* );

//Renders Text as Texture using renderer: gRenderer, starting at top left X, Y
void RenderText(const char*, int, int);
//Renders Text as Texture using renderer: gRenderer, centered at X,Y
void RenderTextCentered(const char* , int, int );

//Renders Scroes for all Players
void RenderScores();
//Renders Status for all Players
void RenderStatus();
//Renders Clocks for all Players
void RenderClocks();
//Renders Description for active Player
void RenderDescription();
//Render current input
void RenderInput();

//Update GUI
int UpdateGUI();

#endif