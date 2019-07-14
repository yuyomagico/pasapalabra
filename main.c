//Ya que usan las mismas librerias definidas en "funciones_juego.h", no hay para que repetirlas aca.
#include "src/graphics.h"
#include "src/funciones_juego_1p.h"

int main(){
	int buenas=0,malas=0;//Status del juego
    int index_palabra=0;//Palabra actual
	int t_pal=26;//Total palabras

	if(initSDL() == 0){
		printf( "Failed to initialize SDL!\n" );
		return 1;
	}

	if(loadMedia() == 0){
		printf( "Failed to load Graphic Resources!\n" );
		return 1;
	}

	// Main Loop
	do{
		char buenasMalasLabel[40];
		char letraActualLabel[40];
		char descripcion[200];
		sprintf(buenasMalasLabel, "Buenas: %d, Malas: %d", buenas, malas);
		sprintf(letraActualLabel, "Letra Actual: %c", index_palabra+65);
		sprintf(descripcion, "%s", getDescripcion(index_palabra));
		//FIN JUEGO
		if(buenas + malas == t_pal){
			initInput();
			if(buenas == t_pal){
				updateTexts(buenasMalasLabel, letraActualLabel, "HAS GANADO!", inputText1);
			}else{
				char texto[200];
				sprintf(texto, "Te han faltado %d palabras!", malas);
				updateTexts(buenasMalasLabel, letraActualLabel, texto, inputText1);
			}
		}else{
			estado_palabras[index_palabra] = PALABRA_ACTUAL;

			if(isReadyToEvaluate() == 1){

				//getInputText y estado_palabras definidos en graphics.1.c
				buena_mala(getInputText(),&buenas, &malas, &t_pal, index_palabra, estado_palabras);
				setReadyToEvaluate(0);
				initInput();
				index_palabra = (index_palabra +1) % t_pal;

			}else{
				updateTexts(buenasMalasLabel, letraActualLabel, descripcion, inputText1);
			}
		}
	}while(updateGUI() == 0);
	
	return 0;
}