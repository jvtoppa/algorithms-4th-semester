#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

//V2: comentários um pouco mais explicativos. Mudança no nome de algumas variáveis
//(muito longos). 

int main(void)
{
    //VARIÁVEIS
    char maxOuAtualizar = 0;
    int i = 0;
    int j = 0;
    int *vetorV = NULL; // ----> Uso do realloc (null)
    int *vetorR = NULL;
    int tamanhoVetor = 0;
    int tamanhoVetorSqrt = 0;
    //VARIÁVEIS

    while (1)
    {
        if (scanf("%d", &tamanhoVetor) != 1)
        {

            break;
        
        }

        getchar();

        int tamanhoVetorSqrt = ceil(sqrt(tamanhoVetor)); //se nao usarmos o teto os valores nao vao caber no array

        vetorV = realloc(vetorV, sizeof(int) * tamanhoVetor);
        vetorR = realloc(vetorR, sizeof(int) * tamanhoVetorSqrt); 

        //leitura dos valores do vetor
        for (int it = 0; it < tamanhoVetor; it++)
        {
            if (scanf("%d", &vetorV[it]) != 1)
            {
              
                free(vetorV);
                free(vetorR);
                return 1;
           
            }
        }
        getchar();

        while (scanf(" %c %d %d", &maxOuAtualizar, &i, &j) == 3)
        {

        for (int idx = 0; idx < tamanhoVetorSqrt; idx++)
        
        {
         
            vetorR[idx] = 0;
        
        }

        //atualiza vetorR com o máximo de cada bloco
        for (int indBl = 0; indBl < (tamanhoVetor + tamanhoVetorSqrt - 1) / tamanhoVetorSqrt; indBl++)
        {
           
            int inicioBl = indBl * tamanhoVetorSqrt;
            int fimBl = (indBl + 1) * tamanhoVetorSqrt < tamanhoVetor ? (indBl + 1) * tamanhoVetorSqrt : tamanhoVetor; //explicado lá embaixo

            vetorR[indBl] = vetorV[inicioBl];
            for (int k = inicioBl + 1; k < fimBl; k++)
           
            {
                if (vetorV[k] > vetorR[indBl])
                {
                
                    vetorR[indBl] = vetorV[k];
                
                }
            
            }
        
        }

        if (maxOuAtualizar == 109) 
        {
            int valorMaximo = 0;

            int blInicio = i / tamanhoVetorSqrt;
            int blocoFim = j / tamanhoVetorSqrt;

            if (blInicio == blocoFim)
            {

                for (int indice = i; indice <= j; indice++)
                {

                    if (vetorV[indice] > valorMaximo)
                    {

                        valorMaximo = vetorV[indice];
                    
                    }
                }
            }
            else
            {

                //máximo no bloco da esquerda
                int fimBlEsquerdo = (blInicio + 1) * tamanhoVetorSqrt - 1;
                for (int indice = i; indice <= fimBlEsquerdo; indice++)
                {

                    if (vetorV[indice] > valorMaximo)
                    {

                        valorMaximo = vetorV[indice];
                    
                    }
                }

                //máximo nos blocos completos do meio
                for (int indBl = blInicio + 1; indBl < blocoFim; indBl++)
                {

                    if (vetorR[indBl] > valorMaximo)
                    {

                        valorMaximo = vetorR[indBl];
                    
                    }
                }

                //máximo no bloco da direita
                int inicioBlDireito = blocoFim * tamanhoVetorSqrt;
                for (int indice = inicioBlDireito; indice <= j; indice++)
                {

                    if (vetorV[indice] > valorMaximo)
                    {

                        valorMaximo = vetorV[indice];
                    
                    }
                }
            }

            printf("%d\n", valorMaximo);
        }
        else if (maxOuAtualizar == 97) 
        {
            vetorV[i] = j;

            int indexBl = i / tamanhoVetorSqrt;
            int inicioBl = indexBl * tamanhoVetorSqrt;
            int fimBl = (indexBl + 1) * tamanhoVetorSqrt < tamanhoVetor ? (indexBl + 1) * tamanhoVetorSqrt : tamanhoVetor; //essa expressão ficou meio longa, mas significa
                                                                                                                                    //que se o indice nao for maior que o vetor definimos fimbl como a outra expressao 
            
            
            
            
            vetorR[indexBl] = vetorV[inicioBl];
            
            for (int k = inicioBl; k < fimBl; k++)
            {

                if (vetorV[k] > vetorR[indexBl])
                {

                    vetorR[indexBl] = vetorV[k];
                
                }
            }
        }
    }
}

    free(vetorV);
    free(vetorR);

    return 0;
}