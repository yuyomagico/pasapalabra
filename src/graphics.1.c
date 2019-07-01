/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

#include "./graphics.h"
int estado_palabras[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void handleKeyboard(SDL_Event e, SDL_Texture** gCurrentTExture){
	//Select surfaces based on key press

	/*switch( e.key.keysym.sym )
	{
		case SDLK_UP:
		printf( "up!\n" );
		*gCurrentTExture = gTexturasLetras[ KEY_PRESS_SURFACE_UP ];
		break;

		case SDLK_DOWN:
		printf( "down!\n" );
		*gCurrentTExture = gTexturasLetras[ KEY_PRESS_SURFACE_DOWN ];
		break;

		case SDLK_LEFT:
		printf( "left!\n" );
		*gCurrentTExture = gTexturasLetras[ KEY_PRESS_SURFACE_LEFT ];
		break;

		case SDLK_RIGHT:
		printf( "right!\n" );
		*gCurrentTExture = gTexturasLetras[ KEY_PRESS_SURFACE_RIGHT ];
		break;

		default:
		printf( "otro!\n" );
		*gCurrentTExture = gTexturasLetras[ KEY_PRESS_SURFACE_DEFAULT ];
		break;
	}*/
}

void updateGUI()
{
	int quit = 0;

	//SDL Event handler
	SDL_Event e;

	gBackgroundTexture = loadTexture("res/img/fondo.png");
	//While application window is running
	//while( quit == 0 )
	//{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = 1;
			}
			/* else if( e.type == SDL_KEYDOWN){
				handleKeyboard(e, &gCurrentTexture);
			}*/
		}
		//Apply the image stretch parameters
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		//Clear screen                
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0x00 );
		SDL_RenderClear( gRenderer );

		//Render texture to screen
		SDL_Rect renderQuad = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy( gRenderer, gBackgroundTexture, NULL, &renderQuad );
		//TODO: loop over all letters and check if good or bad to change color

		for(int i = 0; i<CANTIDAD_LETRAS;i++){
			gCurrentTexture = gTexturasLetras[i];
			if(estado_palabras[i]==PALABRA_MALA){
				SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0x00, 0x00 );
			}else if(estado_palabras[i]==PALABRA_BUENA){
				SDL_SetTextureColorMod( gCurrentTexture, 0x00, 0xFF, 0x00 );
			}else{
				SDL_SetTextureColorMod( gCurrentTexture, 0xFF, 0xFF, 0xFF );
			}
			SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, &renderQuad );
		}

		//Update screen
		SDL_RenderPresent( gRenderer );
	//}
}