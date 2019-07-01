//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//Screen dimension constants
#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

#ifndef CANTIDAD_LETRAS
	#define CANTIDAD_LETRAS		26
#endif

//Key press surfaces constants
enum EstadoPalabra
{
	PALABRA_PENDIENTE,
	PALABRA_BUENA,
	PALABRA_MALA
};


//Starts up SDL and creates window
int initSDL();

//Loads media
int loadMedia();

//Update GUI
void updateGUI();

extern int estado_palabras[];// = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//Frees media and shuts down SDL
void closeSDL();

//The window we'll be rendering to
extern SDL_Window* gWindow;
	
//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The images that correspond to a keypress. 
//(usa un Truco con KEY_PRESS_SURFACE_TOTAL, si se mantiene al final del enum, siempre tendra un valor igual a la cantidad de elmentos en el enum
extern SDL_Texture* gTexturasLetras[];

//The window renderer
extern SDL_Renderer* gRenderer;
//Current displayed texture
extern SDL_Texture* gCurrentTexture;	
extern SDL_Texture* gBackgroundTexture;