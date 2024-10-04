#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no
{

int nome_conj;
int conj[127];
int arrsize;
struct no* prox;
struct no* ant;

}no;

typedef struct lista
{

no* head;
int tam;

}lista;

lista* criar()//
{

lista* L = malloc(sizeof(lista));
if(!L)
{
    return NULL;
}

L->head = NULL;
L->tam = 0;

no* dummy = malloc(sizeof(no));

dummy->ant = L->head;
dummy->prox = NULL;

for(int i = 0; i < 127; i++)
{
    dummy->conj[i] = 1;
}
L->head = dummy;



return L;
}

int insert_conjunto(lista* L, int arrval[127], int nomeC, int sizeArr)//
{
    no* novo = malloc(sizeof(no));
    if(!novo)
    {
        return 0;
    }
    novo->arrsize = 0;
    for (int i = 0; i < sizeArr; i++)
    {
        novo->conj[i] = arrval[i];
    }
    novo->arrsize = sizeArr;
    novo->nome_conj = nomeC;
    
    novo->prox = L->head->prox;
    novo->ant = L->head;
    L->head->prox = novo;
    
    

    L->tam++;
    return 1;
}

void imprimir_lista(lista* L, int nomeC) //
{
printf("C%d = {", nomeC);

for(no* p = L->head->prox; p != NULL; p = p->prox)
{
    if(p->nome_conj == nomeC)
    {
        for(int i = 0; i < p->arrsize; i++)
        {
            printf("%d", p->conj[i]);
            if((i < p->arrsize - 1))
            {
                printf(", ");
            }
        }
        break;
    }

}

printf("}\n");

}


int libera(lista* L)//
{

    no* p = L->head;
    while (p != NULL)
    {
        no* temporario = p; 
        p = p->prox; 
        free(temporario); 
    }
    
    free(L); 
    return 1;
}

int merge(int* vetorsort, int inicio, int m, int tamvetor)
{
    //int arr[tamvetor];


}

int merge_sort(int* vetorsort, int tamvetor)
{
    int inicio = 0;
    int m;
    if(inicio < tamvetor)
    {
        m = floor((inicio + tamvetor)/2);
        merge_sort(vetorsort, inicio, m);
        merge_sort(vetorsort, m + 1, tamvetor);
        merge(vetorsort, inicio, m, tamvetor);
    }
    return 1;
}

int remove_elemento(lista* L)
{
    return 1;
}


int main(void)
{
    lista* L = criar();

    int val;
    int tam = 0;
    int i = 0;
    int valores[127];

    while(scanf("%d", &val) == 1)
    {
        
        valores[i] = val;
        i++;
        tam++;
    }

    insert_conjunto(L, valores, 999, tam);
    tam = 0;
    for (int i = 0; i < 127; i++) {
        valores[i] = i;
        tam++;
    }
    insert_conjunto(L, valores, 77, tam);

    imprimir_lista(L, 999);
    imprimir_lista(L, 77);

    return 0;

}

