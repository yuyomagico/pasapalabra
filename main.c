//Ya que usan las mismas librerias definidas en "funciones_juego.h", no hay para que repetirlas aca.
#include "src/graphics.h"
#include "src/funciones_juego_1p.h"

//TIMERS
/* Start the timer; the callback below will be executed after the delay */
Uint32 startGame;  /* To round it down to the nearest 10 ms */
Uint32 lastTicksP1 = 0;
Uint32 lastTicksP2 = 0;
Uint32 elapsedP1 = 0;
Uint32 elapsedP2 = 0;
Uint32 MAX_TIME = 120000;
int playerWon = -1;

int main(){
	int buenas=0,malas=0;//Status del juego
    int index_palabra=0;//Palabra actual
	int buenas2=0,malas2=0;//Status del juego
    int index_palabra2=0;//Palabra actual
	int t_pal=26;//Total palabras

	if(initSDL() == 0){
		printf( "Failed to initialize SDL!\n" );
		return 1;
	}

	if(loadMedia() == 0){
		printf( "Failed to load Graphic Resources!\n" );
		return 1;
	}

	startGame = SDL_GetTicks();
	// Main Loop
	do{
		char buenasMalasLabel[40];
		char letraActualLabel[40];
		char descripcion[200];
		//Check Timers
		if(getTurnoPLayer() == 0){
			if(elapsedP1 > MAX_TIME){
				player1Status = 1;
				sprintf(player1Clock, "TimeOut");
			}else{
				elapsedP1 = SDL_GetTicks()- startGame - elapsedP2;
				int t_secs = (MAX_TIME-elapsedP1)/1000;
				int minutes = t_secs/60;
				int tenth_secs = t_secs%60/10;
				int secs = (t_secs%60)%10;
				sprintf(player1Clock, "%d:%d%d",minutes, tenth_secs, secs);
			}
		}else{
			if(elapsedP2 > MAX_TIME){
				player2Status = 1;
				sprintf(player2Clock, "TimeOut");
			}else{
				elapsedP2 = SDL_GetTicks()- startGame - elapsedP1;
				int t_secs = (MAX_TIME-elapsedP2)/1000;
				int minutes = t_secs/60;
				int tenth_secs = t_secs%60/10;
				int secs = (t_secs%60)%10;
				sprintf(player2Clock, "%d:%d%d",minutes, tenth_secs, secs);
			}
		}

		//Revisar si el jugador hizo paso
		if(getPlayerPassed() == 1){
			setPlayerPassed(0);
			if(getTurnoPLayer() == 0){
				if(buenas2 + malas2 != t_pal && player2Status == 0)//si otro player aun esta en juego
				{
					estado_palabras[index_palabra] = PALABRA_PENDIENTE;//Palabra actual ya no es la activa
					int next_index = (index_palabra +1) % t_pal;
					while(estado_palabras[next_index] != PALABRA_PENDIENTE){
						next_index = (next_index +1) % t_pal;
					}
					index_palabra = next_index;
					changeTurnoPlayer();
					lastTicksP1 = SDL_GetTicks();
				}
			}else{
				if(buenas + malas != t_pal  && player1Status == 0)//si otro player aun esta en juego
				{
					estado_palabras2[index_palabra2] = PALABRA_PENDIENTE;
					int next_index = (index_palabra2 +1) % t_pal;
					while(estado_palabras2[next_index] != PALABRA_PENDIENTE){
						next_index = (next_index +1) % t_pal;
					}
					index_palabra2 = next_index;
					changeTurnoPlayer();
					lastTicksP2 = SDL_GetTicks();
				}
			}
		}
		if(playerWon == -1)
		if(getTurnoPLayer() == 0){
			sprintf(buenasMalasLabel, "Buenas: %d, Malas: %d", buenas, malas);
			sprintf(letraActualLabel, "Letra Actual: %c", index_palabra+65);
			sprintf(descripcion, "%s", getDescripcion(index_palabra));
			//CHECK FIN JUEGO PX
			if(buenas + malas == t_pal || player1Status == 1){
				initInput();
				if(buenas == t_pal){
					updateTexts(buenasMalasLabel, letraActualLabel, "HAS GANADO!", inputText1);
					playerWon = 0;
				}else if (buenas > buenas2){
					updateTexts(buenasMalasLabel, letraActualLabel, "HAS GANADO!", inputText1);
					playerWon = 0;
				}
				else{
					char texto[200];
					sprintf(texto, "Te han faltado %d palabras!", malas);
					updateTexts(buenasMalasLabel, letraActualLabel, texto, inputText1);
					changeTurnoPlayer();
				}
			}else{
				estado_palabras[index_palabra] = PALABRA_ACTUAL;

				if(isReadyToEvaluate() == 1){

					//getInputText y estado_palabras definidos en graphics.1.c
					if(buena_mala(getInputText(),&buenas, &malas, &t_pal, index_palabra, estado_palabras) != 0){
						if(buenas2 + malas2 != t_pal){//check player 2
							changeTurnoPlayer();
							lastTicksP1 = SDL_GetTicks();
						}
					}
					setReadyToEvaluate(0);
					initInput();
					if(buenas + malas != t_pal  && player1Status == 0){
						int next_index = (index_palabra +1) % t_pal;
						while(estado_palabras[next_index] != PALABRA_PENDIENTE){
							next_index = (next_index +1) % t_pal;
						}
						index_palabra = next_index;
					}

				}else{
					updateTexts(buenasMalasLabel, letraActualLabel, descripcion, inputText1);
				}
			}
		}else{
			sprintf(buenasMalasLabel, "Buenas: %d, Malas: %d", buenas2, malas2);
			sprintf(letraActualLabel, "Letra Actual: %c", index_palabra2+65);
			sprintf(descripcion, "%s", getDescripcion(index_palabra2));
			//CHECK FIN JUEGO PX
			if(buenas2 + malas2 == t_pal || player2Status == 1){
				initInput();
				if(buenas2 == t_pal){
					updateTexts(buenasMalasLabel, letraActualLabel, "HAS GANADO!", inputText1);
					playerWon = 1;
				}else if (buenas2 > buenas){
					updateTexts(buenasMalasLabel, letraActualLabel, "HAS GANADO!", inputText1);
					playerWon = 1;
				}
				else{
					char texto[200];
					sprintf(texto, "Te han faltado %d palabras!", malas);
					updateTexts(buenasMalasLabel, letraActualLabel, texto, inputText1);
					changeTurnoPlayer();
				}
			}else{
				estado_palabras2[index_palabra2] = PALABRA_ACTUAL;

				if(isReadyToEvaluate() == 1){

					//getInputText y estado_palabras definidos en graphics.1.c
					if(buena_mala(getInputText(),&buenas2, &malas2, &t_pal, index_palabra2, estado_palabras2) != 0){
						if(buenas + malas != t_pal){
							changeTurnoPlayer();
							lastTicksP2 = SDL_GetTicks();
						}
					}
					setReadyToEvaluate(0);
					initInput();
					if(buenas2 + malas2 != t_pal  && player2Status == 0){
						int next_index = (index_palabra2 +1) % t_pal;
						while(estado_palabras2[next_index] != PALABRA_PENDIENTE){
							next_index = (next_index +1) % t_pal;
						}
						index_palabra2 = next_index;
					}//si aun esta en juego
				}else{
					updateTexts(buenasMalasLabel, letraActualLabel, descripcion, inputText1);
				}
			}
		}
	}while(updateGUI() == 0);
	
	return 0;
}