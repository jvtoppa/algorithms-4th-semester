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

SA* criarSufixo(char* fonte, int sizeFonte)
{
    SA* vetorSufixo = malloc(sizeof(SA) * sizeFonte);
    for (int i = 0; i < sizeFonte; i++)
    {
        vetorSufixo[i].suffix = malloc(sizeof(char) * (sizeFonte - i + 1));  
        for (int j = 0; j < sizeFonte - i; j++)  
        {
            vetorSufixo[i].suffix[j] = fonte[i + j];
        }
        vetorSufixo[i].suffix[sizeFonte - i] = '\0'; 
        vetorSufixo[i].indice = i;
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

int main(void)
{
    char frase[1000000];
    scanf("%s", frase);
    int tam = strlen(frase);
    frase[tam] = '$';
    frase[tam + 1] = '\0';
    tam = tam + 1;
    SA* exemp = SArr(frase, tam);

    printf("[");
    for (int i = 0; i < tam; i++)
    {
        if(i < tam - 1)
        printf("%s (%d), ", exemp[i].suffix, exemp[i].indice);
        else printf("%s (%d)", exemp[i].suffix, exemp[i].indice);
    }
    printf("]\n");

    free(exemp);
}