#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Inicializador
double** initJagged(int n)
{
double** colunaJagged =  malloc(sizeof(int*) * n);

for(int i = 0; i < n; i++)
{
 colunaJagged[i] =  malloc(sizeof(double) * (i + 1));
}

return colunaJagged;

}


//Limpa o Jagged
void limpaJagged(double** array, int m)
{

for(int i = 0; i < m; i++)
{ 
        free(array[i]);
}

free(array);

}

//Insere elementos no Jagged
int insert(double** array, int o)
{

double element = 0;

for(int i = 0; i < o; i++)
{
    for(int j = 0; j <= i; j++)
    {
        if(scanf("%lf", &element) != 1)
        {
            return 0;
        }
        getchar();

        array[i][j] = element;

    }
}

return 1;
}

double mediaJagged(double** array, int q)
{

double media = 0;
int counter = 0;

for(int i = 0; i < q; i++)
{
    for(int j = 0; j <= i; j++)
    {
        media = (media + array[i][j]);
        counter++;

    }
}

return media/counter;
}

double desviopJagged(double** array, int r, double media)
{
    double desvioP = 0;
    int counter = 0;
    for(int i = 0; i < r; i++)
        {
        for(int j = 0; j <= i; j++)
        {

        desvioP = desvioP + pow((array[i][j] - media), 2);
        counter++;
        }
    }
    return sqrt(desvioP/counter);
}

//Printa os elementos do Jagged de acordo com o enunciado
void printJagged(double** array, int p, double media, double desviopadrao)
{
      for(int i = 0; i < p; i++)
        {
        
        for(int j = 0; j <= i; j++)
        {
            printf("%.4f", ((array[i][j] - media)/desviopadrao));
            
            if (j < i)
            {
                printf(" ");
            }
        }
        
        printf("\n");
    }
}


//Main
int main(void)
{

int ordem = 0;

scanf("%d", &ordem);

double** jaggedArray = initJagged(ordem);

insert(jaggedArray, ordem);
double media = mediaJagged(jaggedArray, ordem);
double dp = desviopJagged(jaggedArray, ordem, media);

/*
PRINTA O ARRAY ---- DEBUG

for(int i = 0; i < ordem; i++)
{
    for(int j = 0; j < i; j++)
    {
    printf("%f ", jaggedArray[i][j]);
    }
    printf("\n");
}*/
printJagged(jaggedArray, ordem, media, dp);
printf("\n");
printf("%.4f %.4f\n", media, dp);

limpaJagged(jaggedArray, ordem);



}