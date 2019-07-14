#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_PLAYERS 2
#define CANTIDAD_LETRAS 26

//Declaracion de funciones, definiciones en funciones_juego_1p.c
int buena_mala(char* palabra, int* buenas, int* malas, int* t_pal, int index_palabra, int* estado_palabras);
int mostrar_palabra(char* palabra, int* buenas, int* malas, int* t_pal, int* index_palabra, int* estado_palabras);
void filtrar_entrada_numerica(int*);
char* getDescripcion(int);
