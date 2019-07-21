#include "Renderer.h"
#include "GameManager.h"

// Variable Definitions
SDL_Window* gWindow;
SDL_Renderer* gRenderer;

//Textures
SDL_Texture* gBackgroundTexture;
SDL_Texture* gTexturasLetras[CANTIDAD_LETRAS];

SDL_Rect gScoresRects[MAX_PLAYERS];
SDL_Rect gCurrentLetterRects[MAX_PLAYERS];
SDL_Rect gDescriptionsRects[MAX_PLAYERS];

//TTF
TTF_Font* Sans = NULL;


int InitSDL()
{	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}
	else
	{
		//Create renderer for window
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PLAYER_SCREEN_WIDTH*MAX_PLAYERS, PLAYER_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return 1;
		}
		else
		{			
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return 1;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    return 1;
                }else{
					return 0;
				}
            }
		}
	}
}

void CloseSDL(){
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int CreateResources(){
	if(LoadTextures() != 0 || LoadFonts() != 0){
		return 1;
	}else{

		for(int i = 0; i<MAX_PLAYERS; i++){
			gScoresRects[i] = (SDL_Rect) {PLAYER_SCREEN_WIDTH*i, 0, 100, FONT_SIZE};
			gCurrentLetterRects[i] = (SDL_Rect){PLAYER_SCREEN_WIDTH*i, FONT_SIZE*i, 100, FONT_SIZE};
			gDescriptionsRects[i] = (SDL_Rect){PLAYER_SCREEN_WIDTH*i, PLAYER_SCREEN_HEIGHT-FONT_SIZE, 100, FONT_SIZE};
		}

		return 0;
	}
}

int LoadTextures(){
	int success = 0;

	//Load Background
	gBackgroundTexture = LoadTexture("res/img/fondo.png");
	if(gBackgroundTexture == NULL){
		printf( "Failed to load background image");
	}

	//Load Letters
	for(int i=0; i<CANTIDAD_LETRAS;i++){
		char path[50];
		sprintf(path, "res/img/letras/%c.png", (char)(97+i));

		gTexturasLetras[ i ] = LoadTexture( path );
		if( gTexturasLetras[ i ] == NULL )
		{
			printf( "Failed to load image of letter %c!\n", (char)(97+i) );
			success = 1;
		}
	}

	return success;
}

int LoadFonts(){
	TTF_Init();
	Sans = TTF_OpenFont("res/open-sans/OpenSans-Regular.ttf", FONT_SIZE);
	if (Sans == NULL) {
		fprintf(stderr, "%s", TTF_GetError());
		return 1;
	}
	return 0;
}

void CleanResources(){
	
	//Free Letter Textures
	for( int i = 0; i < CANTIDAD_LETRAS; i++ )
	{
		SDL_DestroyTexture( gTexturasLetras[ i ] );
		gTexturasLetras[ i ] = NULL;
	}
	//Free Dictionaries
	for( int p = 0; p < MAX_PLAYERS; p++ )
	{
		free(players[p].myDictionary);
	}

	SDL_DestroyTexture(gBackgroundTexture);
	gBackgroundTexture = NULL;
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
}

SDL_Texture* LoadTexture( char* path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void RenderText(const char* text, int x, int y){
	SDL_Color Black = {0, 0, 0}; 
	if(strcmp("", text) != 0){
		SDL_Surface* mySurface = TTF_RenderText_Solid(Sans, text, Black);
		SDL_Texture* myTexture = SDL_CreateTextureFromSurface(gRenderer, mySurface);
		
		SDL_Rect renderQuad = { x, y, mySurface->w, mySurface->h };
		SDL_RenderCopy( gRenderer, myTexture, NULL, &renderQuad);

		SDL_FreeSurface(mySurface);
		SDL_DestroyTexture(myTexture);
	}
}
void RenderTextCentered(const char* text, int x, int y){
	if(strcmp("", text) != 0){
		SDL_Color Black = {0, 0, 0}; 
		SDL_Surface* mySurface = TTF_RenderText_Solid(Sans, text, Black);
		SDL_Texture* myTexture = SDL_CreateTextureFromSurface(gRenderer, mySurface);
		
		SDL_Rect renderQuad = { x-(mySurface->w)/2, y-(mySurface->h)/2, mySurface->w, mySurface->h };
		SDL_RenderCopy( gRenderer, myTexture, NULL, &renderQuad);

		SDL_FreeSurface(mySurface);
		SDL_DestroyTexture(myTexture);
	}
}


void RenderLetters(){
	for(int p = 0; p<MAX_PLAYERS;p++){
		SDL_Rect renderQuad = {p*PLAYER_SCREEN_WIDTH, 0, PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT-FONT_SIZE};
		for(int i = 0; i<CANTIDAD_LETRAS; i++){
			//Puede acceder a players a traves de "GameManager.h" 
			if(players[p].estadoPalabras[i]==PALABRA_MALA){
				SDL_SetTextureColorMod( gTexturasLetras[i], 0xFF, 0x00, 0x00 );
			}else if(players[p].estadoPalabras[i]==PALABRA_BUENA){
				SDL_SetTextureColorMod( gTexturasLetras[i], 0x00, 0xFF, 0x00 );
			}else if(players[p].estadoPalabras[i]==PALABRA_ACTUAL){
				SDL_SetTextureColorMod( gTexturasLetras[i], 0xFF, 0xFF, 0xFF );
			}else{
				SDL_SetTextureColorMod( gTexturasLetras[i], 0x80, 0x80, 0x80 );
			}
			SDL_RenderCopy( gRenderer, gTexturasLetras[i], NULL, &renderQuad );
		}
	}
}

void RenderScores(){
	for(int p=0;p<MAX_PLAYERS;p++){
		char text[50];
		sprintf(text, "Buenas: %d, Malas: %d", players[p].buenas, players[p].malas);
		RenderText(text, p*PLAYER_SCREEN_WIDTH, 0);
	}
}
void RenderStatus(){
	for(int p=0;p<MAX_PLAYERS;p++){
		char text[50];
		sprintf(text, "Letra Actual: %c", players[p].letraActualIndex+65);
		RenderText(text, p*PLAYER_SCREEN_WIDTH, FONT_SIZE);
	}
}
void RenderClocks(){
	for(int p=0;p<MAX_PLAYERS;p++){
		char text[50];
		sprintf(text, "%s", players[p].clock);
		RenderText(text, (p+1)*(PLAYER_SCREEN_WIDTH)-150, 0);
	}
}

void RenderDescription(){
	char text[50];
	sprintf(text, "%s", (char*)players[GetCurrentPlayerTurn()].myDictionary[players[GetCurrentPlayerTurn()].letraActualIndex].meaning);
	RenderText(text, GetCurrentPlayerTurn()*PLAYER_SCREEN_WIDTH, PLAYER_SCREEN_HEIGHT-FONT_SIZE);
}

void RenderInput(){
	char text[50];
	sprintf(text, "%s", GetInputText());//
	RenderTextCentered(text, GetCurrentPlayerTurn()*PLAYER_SCREEN_WIDTH + PLAYER_SCREEN_WIDTH/2, (int)PLAYER_SCREEN_HEIGHT/2);
}

int UpdateGUI(){
	//Clear screen                
	SDL_RenderClear( gRenderer );

	//Render Background
	SDL_Rect bckgndRect = { 0, 0, PLAYER_SCREEN_WIDTH*MAX_PLAYERS, PLAYER_SCREEN_HEIGHT};
	SDL_RenderCopy( gRenderer, gBackgroundTexture, NULL, &bckgndRect );
	
	//Render Rosco
	RenderLetters();

	//Render Stuff
	RenderScores();
	RenderStatus();
	RenderClocks();
	if(gameOver != 1){
		RenderInput();
		RenderDescription();
	}

	//Update screen
	SDL_RenderPresent( gRenderer );
}
