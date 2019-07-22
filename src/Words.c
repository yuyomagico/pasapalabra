#include "Words.h"
#include "TestWords.h"

WordEntry** MyDictionary;


int LoadDictionary(){
    //TODO: Load file with format word;definition;, luego tomar primera letra de word, convertirla en minuscula, etc. Ingresarlo todo al objeto MyDictionary; 
    return 0;
}


//Test data Dictionary
WordEntry* LoadTestDictionary(int players){
    WordEntry* MyNewDictionary = (WordEntry*) malloc(CANTIDAD_LETRAS*sizeof(WordEntry));
    for(int i=0;i<CANTIDAD_LETRAS;i++){
        if(players == 0){
            strcpy(MyNewDictionary[i].word, testWords[i]);
            strcpy(MyNewDictionary[i].meaning , testDefs[i]);
        }else{
            strcpy(MyNewDictionary[i].word , testWords2[i]);
            strcpy(MyNewDictionary[i].meaning , testDefs2[i]);
        }
        printf("%s: %s\n", MyNewDictionary[i].word, MyNewDictionary[i].meaning);
    }
    return MyNewDictionary;
}

WordEntry** GetSampleDictionary(){
    return MyDictionary;
}
