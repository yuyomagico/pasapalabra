#include "./funciones_juego_1p.h"
#include "./textos.h"


int buena_mala(char* palabra, int* buenas, int* malas, int* t_pal, int index_palabra, int* estado_palabras){
	if(strncmp(palabras[index_palabra],palabra,200)==0){
		printf("Correcto!!!\n");
		*buenas=*buenas+1;
		estado_palabras[index_palabra] = 1;
		return 0;
	}else{
		printf("Incorrecto\n");
		*malas=*malas+1;
		estado_palabras[index_palabra] = 2;
		return 1;
	}
}
char* getDescripcion(int index){
	return descripciones[index];
}
