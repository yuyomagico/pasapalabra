#ifndef _WORDSH
#define _WORDSH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef CANTIDAD_LETRAS
  #define CANTIDAD_LETRAS 26
#endif
#define MAX_WORD_LENGTH 100
#define MAX_DESCR_LENGTH 500

//Posibles estados de una palabra
enum EstadosPalabra
{
	PALABRA_PENDIENTE,
	PALABRA_BUENA,
	PALABRA_MALA,
	PALABRA_ACTUAL
};

typedef struct wordEntry {
  char word[MAX_WORD_LENGTH];
  char meaning[MAX_DESCR_LENGTH];
} WordEntry;

extern WordEntry MyDictionary[CANTIDAD_LETRAS][2];

int LoadDictionary();
int LoadTestDictionary();
void AssignSampleWords(char*[CANTIDAD_LETRAS], char*[CANTIDAD_LETRAS], int);

#endif