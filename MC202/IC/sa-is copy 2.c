//O objetivo é comparar um array de sufixos feito de forma ingênua O(nlogn) com
//o método SA-IS (suffix array induced sorting). Baseado em 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int compare(const void* a, const void* b)
{

}

int* SArr(char* fonte, int sizeFonte)
{
    int* sufixo = malloc(sizeof(int)*sizeFonte);
    for(int i = 0; i < sizeFonte; i++)
    {

    }
    qsort(sufixo, sizeFonte, sizeof(int), compare);
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