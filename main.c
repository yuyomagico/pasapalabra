//Ya que usan las mismas librerias definidas en "funciones_juego.h", no hay para que repetirlas aca.
#include "./src/graphics.h"
#include "./src/funciones_juego_1p.h"

int main(){
	int n,buenas=0,malas=0;
    int index_palabra=0;
	char palabra[20];
	int t_pal=25;

	if(initSDL() == 0){
		printf( "Failed to initialize SDL!\n" );
		return 1;
	}

	if(loadMedia() == 0){
		printf( "Failed to load Graphic Resources!\n" );
		return 1;
	}

	do{
		printf("1.Jugar\n");
		printf("2.Salir\n");
		filtrar_entrada_numerica(&n);
		if(n==1){
            int i=0;
            do{
				updateGUI();
				system("clear");
                printf("Nivel: %d\n", index_palabra+1);
                printf("Buenas: %d. Malas: %d\n", buenas, malas);
                mostrar_palabra(palabra, &buenas, &malas, &t_pal, &index_palabra, estado_palabras);
            }while(index_palabra < CANTIDAD_LETRAS);

            if(buenas==CANTIDAD_LETRAS)printf("GANASTE WACHO QLO LOCO\n");
            else printf("Te faltan sioh malo qlo\n");	
			printf("Buenas: %d. Malas: %d\n", buenas, malas);
		}
	}while(n!=2);
	return 0;
}