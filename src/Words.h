#ifndef _WORDSH
#define _WORDSH

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef CANTIDAD_LETRAS
  #define CANTIDAD_LETRAS 26
#endif
#define MAX_WORD_LENGTH 	50
#define MAX_DESCR_LENGTH 	500

//Posibles estados de una palabra
enum EstadosPalabra
{
	PALABRA_PENDIENTE,
	PALABRA_BUENA,
	PALABRA_MALA,
	PALABRA_ACTUAL
};

typedef struct wordEntry {
  char* word;
  char* meaning;
} WordEntry;

extern WordEntry** MyDictionary;

int LoadDictionary();
WordEntry* LoadTestDictionary(int);
WordEntry** GetSampleDictionary();

#endif
