//Ya que usan las mismas librerias definidas en "funciones_juego.h", no hay para que repetirlas aca.
#include "src/GameManager.h"

// Nada mas en main que Cargar y Jugar.
int main(){
	if(LoadGame() != 0){
		return 1;
	}else{
		while(PlayGame() == 0);
		return 0;
	}
	return 0;
}