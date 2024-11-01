//O objetivo é comparar um array de sufixos feito de forma ingênua O(nlogn) com
//o método SA-IS (suffix array induced sorting). Baseado em 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SA
{
    char* suffix;
    int indice;
} SA;

typedef struct SAIS
{
    char carac;
    int index;
    char type;
} SAIS;

SA* criarSufixo(char* fonte, int sizeFonte)
{
    SA* vetorSufixo = malloc(sizeof(SA) * sizeFonte);
    for (int i = 0; i < sizeFonte; i++)
    {
        vetorSufixo[i].suffix = malloc(sizeof(char) * (sizeFonte - i + 1));
        strcpy(vetorSufixo[i].suffix, &fonte[i]);
        vetorSufixo[i].indice = i + 1;
    }
    return vetorSufixo;
}

int compare(const void* a, const void* b)
{
    SA* suffixA = (SA*)a;
    SA* suffixB = (SA*)b;
    return strcmp(suffixA->suffix, suffixB->suffix);
}

SA* SArr(char* fonte, int sizeFonte)
{
    SA* sufixo = criarSufixo(fonte, sizeFonte);
    qsort(sufixo, sizeFonte, sizeof(SA), compare);
    return sufixo;
}
//----------------------------------#-----------------------------------------//
SAIS* buildLMS(char* data, int dataSize)
{
    SAIS* LMS = malloc(sizeof(SAIS) * dataSize);
    for(int i = 0; i < dataSize; i++)
    {
        LMS[i].carac = data[i];
        LMS[i].index = i;
        LMS[i].type = 'S';
    }

    LMS[dataSize - 1].type = 'S';
    for(int j = dataSize - 2; j >= 0; j--)
    {
        if(LMS[j].carac > LMS[j + 1].carac)
        {
            LMS[j].type = 'L';
        }
        else if(LMS[j].carac == LMS[j + 1].carac && LMS[j + 1].carac == 'L')
        {
            LMS[j].type = 'L';
        }
        else
        {
            LMS[j].type = 'S';
        }
    }
    return LMS;

}
int isLMSChar(SAIS* LMSFunction, int index)
{
    if(LMSFunction[index].type == 'S' && LMSFunction[index - 1].type == 'L')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isLMSEqual(SAIS* LMSFunction, int tam, int index1, int index2)
{
    if(index1 == tam || index2 == tam)
    {
        return 0;
    }

    for(int i = 0; i < tam; i++)
    {
        int aIsLMS = isLMSChar(LMSFunction, i + index1);
        int bIsLMS = isLMSChar(LMSFunction, i + index2);

        if(i > 0 && aIsLMS && bIsLMS)
        {
            return 1;
        }
        if(aIsLMS != bIsLMS)
        {
            return 0;
        }
        if(LMSFunction[i + index1].carac != LMSFunction[i + index2].carac)
        {
            return 0;
        }
    }
}

//Debug.
int printLMS(SAIS* LMSFunction, int tam)
{
    printf("Vetor LMS:\n");
    for(int i = 0; i < tam; i++)
    {
        printf("%c", LMSFunction[i].carac);
    }
    printf("\n");
    for(int i = 0; i < tam; i++)
    {
        printf("%c", LMSFunction[i].type);
    }
    printf("\n");
    for(int i = 0; i < tam; i++)
    {
        if(isLMSChar(LMSFunction, i))
        {
            printf("^");
        }
        else
        {
            printf(" ");
        }
        
    }

}



int main(void)
{
    char frase[1000000];
    scanf("%s", frase);
    int tam = strlen(frase);
    frase[tam] = '$';
    frase[tam + 1] = '\0';
    tam = tam + 1;
    SA* exemp = SArr(frase, tam);
    SAIS* exemp2 = buildLMS(frase, tam);

    printf("Forma ingenua:\n");
    for (int i = 0; i < tam; i++)
    {
        printf("%s (%d)\n", exemp[i].suffix, exemp[i].indice);
    }
    printf("\n\n");
    printLMS(exemp2, tam);
    free(exemp);
    free(exemp2);
}