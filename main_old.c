#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char pal_var[]="arreglo byte compilador double estrutura float gigabyte hardware int java kilobyte lag malware navegador octal password qwerty ram stack teclado ubuntu variable web x youtube zip";
int buscarPal(char* pal_var, char* buscador){
	int tam_pal=strlen(pal_var);
	int tam_bus=strlen(buscador);
	int i=0;
	char buscar,c;
	if (tam_pal>tam_bus){
		c=buscador[0];  
		while (i<tam_pal){
			if (pal_var[i]==c){
				if (strncmp(&pal_var[i],buscador,tam_bus)==0){
					return 1;
				}
			}
			++i;
		}
		return 0;
	}
}

void buena_mala(int m, char* palabra, int* buenas, int* malas, int* t_pal){
	switch(m){
		case 1: printf("La palabra es:\n");	
				scanf("%s",palabra);
				if(buscarPal(pal_var,palabra)==1){
					printf("Correcto!!!\n");
					*buenas=*buenas+1;
					*t_pal=*t_pal-1;
				}else{
					printf("Incorrecto\n");
					*malas=*malas+1;
					*t_pal=*t_pal-1;
				}
				break;

		case 2: break;
	}
}

int main(){
	int n,m,buenas=0,malas=0;
	char palabra[20];
	int t_pal=25;
	do{
		printf("1.Jugar\n");
		printf("2.Salir\n");
		//loop hasta encontrar opcion valida
		while(scanf("%d",&n) != 1)
		{
			while(getchar() != '\n');
		}
		if(n==1){

				printf("Coleccion de elementos del mismo tipo ordenados de manera secuencial\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [B]\n");
				printf("Unidad de informacion compuesta generalmente de 8 bits\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);


				system("clear");
				printf("Empieza con la letra [C]\n");
				printf("Que compila\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);


				system("clear");
				printf("Empieza con la letra [D]\n");
				printf("Declaracion flotante de presicion doble\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);


				system("clear");
				printf("Empieza con la letra [E]\n");
				printf("Agrupacion de datos de diferente tipo\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);


				system("clear");
				printf("Empieza con la letra [F]\n");
				printf("Numero de punto flotante\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [G]\n");
				printf("Conjunto de 1024 MB\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [H]\n");
				printf("Las partes fisicas de un ordenador\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [I]\n");
				printf("Declaracion de numero entero\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [J]\n");
				printf("Lenguaje de programacion orientado a objetos\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [K]\n");
				printf("Conjunto de 1024 bytes\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [L]\n");
				printf("Retraso de informacion\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [M]\n");
				printf("Programa malulo uwu\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [N]\n");
				printf("Programa para visualizar paginas web\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [O]\n");
				printf("Sistema de enumeracon de base 8\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [P]\n");
				printf("Metodo de seguridad para identificar a un usuario\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [Q]\n");
				printf("Disposicion del teclado mas usual en celulares y coputadores\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [R]\n");
				printf("Memoria de acceso aleatorio\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [S]\n");
				printf("Estructura de datos usada para almacenar objetos\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [T]\n");
				printf("Dispositivo de entrada de datos al computador\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [U]\n");
				printf("Distribucion de linux\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [V]\n");
				printf("Estructura de programacion que contiene datos\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [W]\n");
				printf("Se conoce como World Wide Web\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [X]\n");
				printf("Indicador de extendido\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [Y]\n");
				printf("Sitio web que permite compartir videos\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				system("clear");
				printf("Empieza con la letra [Z]\n");
				printf("Archivo comprimido\n");
				printf("1.Escribir palabra\n");
				printf("2.Pasapalabra\n");
				scanf("%d",&m);
				buena_mala(m,palabra,&buenas,&malas,&t_pal);

				if(buenas==25)printf("GANASTE WACHO QLO LOCO\n");
				else printf("Te faltan sioh malo qlo\n");	
				printf("%d\n",buenas);	
		}
	}while(n!=2);
	return 0;
}