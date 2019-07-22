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
    printf("poop\n");
    for(int i=0;i<CANTIDAD_LETRAS;i++){
        if(players == 0){
            MyNewDictionary[i].word = testWords[i];
            MyNewDictionary[i].meaning = testDefs[i];
        }else{
            MyNewDictionary[i].word = testWords2[i];
            MyNewDictionary[i].meaning = testDefs2[i];
        }
        printf("%s: %s\n", MyNewDictionary[i].word, MyNewDictionary[i].meaning);
    }
    printf("poop1\n");
    return MyNewDictionary;
}

WordEntry** GetSampleDictionary(){
    return MyDictionary;
}
