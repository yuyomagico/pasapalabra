/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

#include "./graphics.h"
int estado_palabras[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int estado_palabras2[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int turnoPlayer = 0;
int playerPassed = 0;
int player1Status = 0;
int player2Status = 0;
char player1Clock[50] = "2:00";
char player2Clock[50] = "2:00";
//The window we'll be rendering to
SDL_Window* gWindow = NULL;


//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress. 
//(usa un Truco con KEY_PRESS_SURFACE_TOTAL, si se mantiene al final del enum, siempre tendra un valor igual a la cantidad de elmentos en el enum
SDL_Texture* gTexturasLetras[ CANTIDAD_LETRAS ];

//The window renderer
SDL_Renderer* gRenderer = NULL;
//Current displayed texture
SDL_Texture* gCurrentTexture = NULL;	
SDL_Texture* gBackgroundTexture = NULL;


//INPUT RELATED
SDL_Surface* gIngresedWord = NULL;
SDL_Surface* gIngresedWord2 = NULL;
SDL_Texture* gIngresedWordTex = NULL;
SDL_Texture* gIngresedWordTex2 = NULL;

SDL_Surface* gCurrentLetter = NULL;
SDL_Surface* gCurrentLetter2 = NULL;
SDL_Texture* gCurrentLetterTex = NULL;
SDL_Texture* gCurrentLetterTex2 = NULL;

SDL_Surface* gDescripcion = NULL;
SDL_Surface* gDescripcion2 = NULL;
SDL_Texture* gDescripcionTex = NULL;
SDL_Texture* gDescripcionTex2 = NULL;

SDL_Surface* gBuenasMalasWord = NULL;
SDL_Surface* gBuenasMalasWord2 = NULL;
SDL_Texture* gBuenasMalasWordTex = NULL;
SDL_Texture* gBuenasMalasWordTex2 = NULL;


SDL_Surface* gTimer1Sur = NULL;
SDL_Texture* gTimer1Tex = NULL;
SDL_Surface* gTimer2Sur = NULL;
SDL_Texture* gTimer2Tex = NULL;

TTF_Font* Sans = NULL;
char inputText1[MAX_INPUT_LENGTH] = "";
int inputText1Pos = 0;
int readyToEvaluate = 0;

SDL_Rect rectBuenasMalas,rectBuenasMalas2;
SDL_Rect rectCurrentLetterText,rectCurrentLetterText2;
SDL_Rect rectDescripcion,rectDescripcion2;
SDL_Rect rectIngresedText,rectIngresedText2;
SDL_Rect rectTimer1,rectTimer2;


int initSDL()
{	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}
	else
	{
		//Create renderer for window
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return 0;
		}
		else
		{			
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return 0;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Initialize Used Textures (background and font)
				loadTextures();
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    return 0;
                }else{
					return 1;
				}
            }
		}
	}
}

char* getInputText(){
	return inputText1;
}

SDL_Texture* loadTexture( char* path )
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

int loadMedia()
{
	//Loading success flag
	int success = 1;

	//Load default surface
	for(int i=0; i<CANTIDAD_LETRAS;i++){
		char path[50];
		sprintf(path, "res/img/letras/%c.png", (char)(97+i));

		gTexturasLetras[ i ] = loadTexture( path );
		if( gTexturasLetras[ i ] == NULL )
		{
			printf( "Failed to load default image of letter %c!\n", (char)(97+i) );
			success = 0;
		}
	}

	return success;
}


void closeSDL()
{
	//Deallocate surfaces
	for( int i = 0; i < CANTIDAD_LETRAS; ++i )
	{
		SDL_DestroyTexture( gTexturasLetras[ i ] );
		gTexturasLetras[ i ] = NULL;
	}
	gCurrentTexture = NULL;


	//Limpiamos la superficie usada para crear el texto
	SDL_FreeSurface(gBuenasMalasWord);
	SDL_FreeSurface(gCurrentLetter);
	SDL_FreeSurface(gDescripcion);
	SDL_FreeSurface(gIngresedWord);

	SDL_FreeSurface(gBuenasMalasWord2);
	SDL_FreeSurface(gCurrentLetter2);
	SDL_FreeSurface(gDescripcion2);
	SDL_FreeSurface(gIngresedWord2);

	SDL_FreeSurface(gTimer1Sur);
	SDL_FreeSurface(gTimer2Sur);

	SDL_DestroyTexture( gBuenasMalasWordTex );
	gBuenasMalasWordTex = NULL;
	SDL_DestroyTexture( gCurrentLetterTex );
	gCurrentLetterTex = NULL;
	SDL_DestroyTexture( gDescripcionTex );
	gDescripcionTex = NULL;
	SDL_DestroyTexture( gIngresedWordTex );
	gIngresedWordTex = NULL;

	SDL_DestroyTexture( gBuenasMalasWordTex2 );
	gBuenasMalasWordTex2 = NULL;
	SDL_DestroyTexture( gCurrentLetterTex2 );
	gCurrentLetterTex2 = NULL;
	SDL_DestroyTexture( gDescripcionTex2 );
	gDescripcionTex2 = NULL;
	SDL_DestroyTexture( gIngresedWordTex2 );
	gIngresedWordTex2 = NULL;

	SDL_DestroyTexture( gTimer1Tex );
	gTimer1Tex = NULL;
	SDL_DestroyTexture( gTimer2Tex );
	gTimer2Tex = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void handleKeyboard(SDL_Event e){
	//Select surfaces based on key press

	switch( e.key.keysym.sym )
	{
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
		case SDLK_RETURN2:
			printf("enter\n");
			//TODO: Procesar palabra
			// strcmp con palabra, VER COMO ACCEDER A LA PALABRA
			readyToEvaluate = 1;
			inputText1[inputText1Pos] = '\0';
			inputText1Pos = 0;
		break;
		case SDLK_BACKSPACE:
			inputText1Pos--;
			inputText1[inputText1Pos] = '\0';
		break;
		case SDLK_SPACE:
			setPlayerPassed(1);
		break;
		default:
			printf("otra tecla %c\n", e.key.keysym.sym);
			if(e.key.keysym.sym >= 65 && e.key.keysym.sym <= 122){
				if(inputText1Pos < MAX_INPUT_LENGTH){
					inputText1[inputText1Pos] = e.key.keysym.sym;
					inputText1Pos++;
				}
			}
		break;
	}
}

void setPlayerPassed(int i){
	playerPassed = i;
}

int getPlayerPassed(){
	return playerPassed;
}

int isReadyToEvaluate(){
	return readyToEvaluate;
}

void setReadyToEvaluate(int value){
	readyToEvaluate = value;
}

void initInput(){
	for(int i=0;i<MAX_INPUT_LENGTH;i++){
		inputText1[i] = '\0';
	}
}

void updateTexts(char* buenasMalas, char* letraActual, char* descripcion, char* textoIngresado){
	SDL_Color Black = {0, 0, 0}; 
	//Primero se crea una SDL_Surface*, con tipo de fuente, texto y color
	gBuenasMalasWord = TTF_RenderText_Solid(Sans, buenasMalas, Black);
	gCurrentLetter = TTF_RenderText_Solid(Sans, letraActual, Black);
	gDescripcion = TTF_RenderText_Solid(Sans, descripcion, Black);
	gIngresedWord = TTF_RenderText_Solid(Sans, textoIngresado, Black);

	gTimer1Sur = TTF_RenderText_Solid(Sans, player1Clock, Black);
	//Primero se crea una SDL_Surface*, con tipo de fuente, texto y color
	gBuenasMalasWord2 = TTF_RenderText_Solid(Sans, buenasMalas, Black);
	gCurrentLetter2 = TTF_RenderText_Solid(Sans, letraActual, Black);
	gDescripcion2 = TTF_RenderText_Solid(Sans, descripcion, Black);
	gIngresedWord2 = TTF_RenderText_Solid(Sans, textoIngresado, Black);

	gTimer2Sur = TTF_RenderText_Solid(Sans, player2Clock, Black);
	if(getTurnoPLayer() == 0){
		//Luego se crea una SDL_Texture a partir de la SDL_Surface creada en el paso anterior.
		gBuenasMalasWordTex = SDL_CreateTextureFromSurface(gRenderer, gBuenasMalasWord);
		gCurrentLetterTex = SDL_CreateTextureFromSurface(gRenderer, gCurrentLetter);
		gDescripcionTex = SDL_CreateTextureFromSurface(gRenderer, gDescripcion);
		gIngresedWordTex = SDL_CreateTextureFromSurface(gRenderer, gIngresedWord);

		gTimer1Tex = SDL_CreateTextureFromSurface(gRenderer, gTimer1Sur);
	}else{

		gBuenasMalasWordTex2 = SDL_CreateTextureFromSurface(gRenderer, gBuenasMalasWord2);
		gCurrentLetterTex2 = SDL_CreateTextureFromSurface(gRenderer, gCurrentLetter2);
		gDescripcionTex2 = SDL_CreateTextureFromSurface(gRenderer, gDescripcion2);
		gIngresedWordTex2 = SDL_CreateTextureFromSurface(gRenderer, gIngresedWord2);

		gTimer2Tex = SDL_CreateTextureFromSurface(gRenderer, gTimer2Sur);
	}
	
}

void loadTextures(){
	gBackgroundTexture = loadTexture("res/img/fondo.png");

	TTF_Init();
	Sans = TTF_OpenFont("./src/open-sans/OpenSans-Regular.ttf", 24);
	if (Sans == NULL) {
		fprintf(stderr, "%s", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	updateTexts("Puntaje...", "Letra actual...", "Descripcion....", "Texto Ingresado...");
	// Setear los rectangulos donde se hara el render
	rectBuenasMalas = (SDL_Rect){.x = 0,.y = 0,.w = 150,.h = gBuenasMalasWord->h};
	rectCurrentLetterText = (SDL_Rect){.x = 0,.y = 24,.w = gCurrentLetter->w,.h = gCurrentLetter->h};
	rectDescripcion = (SDL_Rect){.x = 0,.y = 480,.w = SCREEN_WIDTH/2,.h = gDescripcion->h};
	rectIngresedText = (SDL_Rect){.x = SCREEN_WIDTH/4-(gIngresedWord->w)/2,
		.y = SCREEN_HEIGHT/2-(gIngresedWord->h)/2,.w = gIngresedWord->w,.h = gIngresedWord->h
	};	//P2
	rectBuenasMalas2 = (SDL_Rect){.x = 640,.y = 0,.w = 150,.h = gBuenasMalasWord->h};
	rectCurrentLetterText2 = (SDL_Rect){.x = 640,.y = 24,.w = gCurrentLetter->w,.h = gCurrentLetter->h};
	rectDescripcion2 = (SDL_Rect){.x = 640,.y = 480,.w = SCREEN_WIDTH/2,.h = gDescripcion->h};
	rectIngresedText2 = (SDL_Rect){.x = SCREEN_WIDTH/4*3-(gIngresedWord->w)/2,
		.y = SCREEN_HEIGHT/2-(gIngresedWord->h)/2,.w = gIngresedWord->w,.h = gIngresedWord->h
	};	

	rectTimer1 = (SDL_Rect){.x = SCREEN_WIDTH/2-(gTimer1Sur->w),
		.y = 0,.w = gTimer1Sur->w,.h = gTimer1Sur->h
	};
	rectTimer2 = (SDL_Rect){.x = SCREEN_WIDTH-(gTimer2Sur->w),
		.y = 0,.w = gTimer2Sur->w,.h = gTimer2Sur->h
	};
}

int getTurnoPLayer(){
	return turnoPlayer;
}
void changeTurnoPlayer(){
	turnoPlayer = (turnoPlayer+1)%2;
}

int updateGUI()
{
	int quit = 0;

	//SDL Event handler
	SDL_Event e;

	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			quit = 1;
		}
		else if( e.type == SDL_KEYDOWN){
			handleKeyboard(e);
		}
	}

	//Clear screen                
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0x00 );
	SDL_RenderClear( gRenderer );

	SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT-48 };
	SDL_Rect renderQuad2 = { 640, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT-48 };
	//RENDER BACKGROUNDS
	SDL_RenderCopy( gRenderer, gBackgroundTexture, NULL, &renderQuad );
	SDL_RenderCopy( gRenderer, gBackgroundTexture, NULL, &renderQuad2 );

	//RENDER CADA LETRA DE FORMA INDIVIDUAL, SI ES QUE YA FUE EVALUADA, APLICAR COLORMOD
	for(int i = 0; i<CANTIDAD_LETRAS;i++){
		gCurrentTexture = gTexturasLetras[i];
		if(estado_palabras[i]==PALABRA_MALA){
			SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0x00, 0x00 );
		}else if(estado_palabras[i]==PALABRA_BUENA){
			SDL_SetTextureColorMod( gCurrentTexture, 0x00, 0xFF, 0x00 );
		}else if(estado_palabras[i]==PALABRA_ACTUAL){
			SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0xFF, 0xFF );
		}else{
			SDL_SetTextureColorMod( gCurrentTexture, 0x80, 0x80, 0x80 );
		}
		SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, &renderQuad );
	}
	//LETRAS PLAYER2
	for(int i = 0; i<CANTIDAD_LETRAS;i++){
		gCurrentTexture = gTexturasLetras[i];
		if(estado_palabras2[i]==PALABRA_MALA){
			SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0x00, 0x00 );
		}else if(estado_palabras2[i]==PALABRA_BUENA){
			SDL_SetTextureColorMod( gCurrentTexture, 0x00, 0xFF, 0x00 );
		}else if(estado_palabras2[i]==PALABRA_ACTUAL){
			SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0xFF, 0xFF );
		}else{
			SDL_SetTextureColorMod( gCurrentTexture, 0x80, 0x80, 0x80 );
		}
		SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, &renderQuad2 );
	}

	//RENDER TEXTS P1
	SDL_RenderCopy(gRenderer, gBuenasMalasWordTex, NULL, &rectBuenasMalas);
	SDL_RenderCopy(gRenderer, gCurrentLetterTex, NULL, &rectCurrentLetterText);
	SDL_RenderCopy(gRenderer, gIngresedWordTex, NULL, &rectIngresedText);

	SDL_RenderCopy(gRenderer, gTimer1Tex, NULL, &rectTimer1);
	//TEXT P2
	SDL_RenderCopy(gRenderer, gBuenasMalasWordTex2, NULL, &rectBuenasMalas2);
	SDL_RenderCopy(gRenderer, gCurrentLetterTex2, NULL, &rectCurrentLetterText2);
	SDL_RenderCopy(gRenderer, gIngresedWordTex2, NULL, &rectIngresedText2);
	
	SDL_RenderCopy(gRenderer, gTimer2Tex, NULL, &rectTimer2);

	if(getTurnoPLayer()==0){
		SDL_RenderCopy(gRenderer, gDescripcionTex, NULL, &rectDescripcion);
	}
	else{
		SDL_RenderCopy(gRenderer, gDescripcionTex2, NULL, &rectDescripcion2);
	}

	//Update screen
	SDL_RenderPresent( gRenderer );
	return quit;
}