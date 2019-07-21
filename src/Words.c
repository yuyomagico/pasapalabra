#include "Words.h"

WordEntry MyDictionary[CANTIDAD_LETRAS][2];

int LoadDictionary(){
    //TODO: Load file with format word;definition;, luego tomar primera letra de word, convertirla en minuscula, etc. Ingresarlo todo al objeto MyDictionary; 
    return 0;
}


//Test data Dictionary
int LoadTestDictionary(){
    MyDictionary[0] [0]=(WordEntry) {"aa","daa"}; MyDictionary[0] [1]=(WordEntry) {"aa","daa"};
    MyDictionary[1] [0]=(WordEntry) {"bb","dbb"}; MyDictionary[1] [1]=(WordEntry) {"bb","dbb"};
    MyDictionary[2] [0]=(WordEntry) {"cc","dcc"}; MyDictionary[2] [1]=(WordEntry) {"cc","dcc"};
    MyDictionary[3] [0]=(WordEntry) {"de","dde"}; MyDictionary[3] [1]=(WordEntry) {"de","dde"};
    MyDictionary[4] [0]=(WordEntry) {"ee","dee"}; MyDictionary[4] [1]=(WordEntry) {"ee","dee"};
    MyDictionary[5] [0]=(WordEntry) {"ff","dff"}; MyDictionary[5] [1]=(WordEntry) {"ff","dff"};
    MyDictionary[6] [0]=(WordEntry) {"gg","dgg"}; MyDictionary[6] [1]=(WordEntry) {"gg","dgg"};
    MyDictionary[7] [0]=(WordEntry) {"hh","dhh"}; MyDictionary[7] [1]=(WordEntry) {"hh","dhh"};
    MyDictionary[8] [0]=(WordEntry) {"ii","dii"}; MyDictionary[8] [1]=(WordEntry) {"ii","dii"};
    MyDictionary[9] [0]=(WordEntry) {"jj","djj"}; MyDictionary[9] [1]=(WordEntry) {"jj","djj"};
    MyDictionary[10][0]=(WordEntry) {"kk","dkk"}; MyDictionary[10][1]=(WordEntry) {"kk","dkk"};
    MyDictionary[11][0]=(WordEntry) {"ll","dll"}; MyDictionary[11][1]=(WordEntry) {"ll","dll"};
    MyDictionary[12][0]=(WordEntry) {"mm","dmm"}; MyDictionary[12][1]=(WordEntry) {"mm","dmm"};
    MyDictionary[13][0]=(WordEntry) {"nn","dnn"}; MyDictionary[13][1]=(WordEntry) {"nn","dnn"};
    MyDictionary[14][0]=(WordEntry) {"oo","doo"}; MyDictionary[14][1]=(WordEntry) {"oo","doo"};
    MyDictionary[15][0]=(WordEntry) {"pp","dpp"}; MyDictionary[15][1]=(WordEntry) {"pp","dpp"};
    MyDictionary[16][0]=(WordEntry) {"qq","dqq"}; MyDictionary[16][1]=(WordEntry) {"qq","dqq"};
    MyDictionary[17][0]=(WordEntry) {"rr","drr"}; MyDictionary[17][1]=(WordEntry) {"rr","drr"};
    MyDictionary[18][0]=(WordEntry) {"ss","dss"}; MyDictionary[18][1]=(WordEntry) {"ss","dss"};
    MyDictionary[19][0]=(WordEntry) {"tt","dtt"}; MyDictionary[19][1]=(WordEntry) {"tt","dtt"};
    MyDictionary[20][0]=(WordEntry) {"uu","duu"}; MyDictionary[20][1]=(WordEntry) {"uu","duu"};
    MyDictionary[21][0]=(WordEntry) {"vv","dvv"}; MyDictionary[21][1]=(WordEntry) {"vv","dvv"};
    MyDictionary[22][0]=(WordEntry) {"ww","dww"}; MyDictionary[22][1]=(WordEntry) {"ww","dww"};
    MyDictionary[23][0]=(WordEntry) {"xx","dxx"}; MyDictionary[23][1]=(WordEntry) {"xx","dxx"};
    MyDictionary[24][0]=(WordEntry) {"yy","dyy"}; MyDictionary[24][1]=(WordEntry) {"yy","dyy"};
    MyDictionary[25][0]=(WordEntry) {"zz","dzz"}; MyDictionary[25][1]=(WordEntry) {"zz","dzz"};

    return 0;
}

void AssignSampleWords(char* palabras[CANTIDAD_LETRAS], char* descripciones[CANTIDAD_LETRAS], int playerId){
    LoadTestDictionary();
    for(int i=0; i<CANTIDAD_LETRAS; i++){
        palabras[i]= MyDictionary[i][playerId].word;
        descripciones[i]= MyDictionary[i][playerId].meaning;
    }
}