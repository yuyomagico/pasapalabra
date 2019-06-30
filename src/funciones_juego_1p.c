#include "./funciones_juego_1p.h"
#include "./textos.h"

int buena_mala(char* palabra, int* buenas, int* malas, int* t_pal, int index_palabra){
	int m;
    printf("1.Escribir palabra\n");
    printf("2.Pasapalabra\n");
    filtrar_entrada_numerica(&m);
    switch(m){
		case 1: printf("La palabra es:\n");	
				scanf("%s",palabra);
				if(strncmp(palabras[index_palabra],palabra,30)==0){
					printf("Correcto!!!\n");
					*buenas=*buenas+1;
					*t_pal=*t_pal-1;
				}else{
					printf("Incorrecto\n");
					*malas=*malas+1;
					*t_pal=*t_pal-1;
				}
                getchar(); //El scanf de arriba agarra letras hasta el \n, con el getchar como el \n que sobra
                while(getchar() != '\n');//Esperar hasta que se ingrese un nuevo enter
				return 0;

		case 2: return 1;
	}
}

int mostrar_palabra(char* palabra, int* buenas, int* malas, int* t_pal, int* index_palabra){
    printf("Index palabra: %d\n", *index_palabra);
    printf("Empieza con la letra [%c]\n", (65+(int)(*index_palabra)));
	printf("%s", descripciones[*index_palabra]);

	if(buena_mala(palabra,buenas,malas,t_pal,*index_palabra) == 0){
		*index_palabra = *index_palabra + 1;
		return 0;
	}else{
		return 1;
	}
}

void filtrar_entrada_numerica(int* valor_ingresado){
    //loop hasta encontrar opcion valida
    while(scanf("%d",valor_ingresado) != 1)
    {
        //si lo que entro no fue un numero, come todos los caracteres hasta el \n del final
        while(getchar() != '\n');
    }
}
