#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
unsigned val;
struct no* prox;
unsigned peso;

} no;

typedef struct lista
{
unsigned tamanho;
no* start;

} lista;

lista* criar_lista(void)
{

lista* L = malloc(sizeof(lista));
if(L == NULL)
{
    return 0;
}

L->tamanho = 0;
L->start = NULL;

return L;

}

int inserir(lista* L, unsigned val, unsigned posicao)
{

    no* novo = malloc(sizeof(no));
    if(!novo)
    {
        return 0;
    }

    if (posicao < 1)
    {
        return 0;
    }
    
    if(posicao > L->tamanho + 1)
    {
        posicao = L->tamanho + 1;
    }

    novo->val = val;
    novo->prox = NULL;
    novo->peso = 0;

    if(posicao == 1) 
    {
        novo->prox = L->start;
        L->start = novo;

    }

    else
    {
        no* p = L->start;
        for (int i=1; i < posicao - 1; i++)
        {
            p = p->prox;
        }
        novo->prox = p->prox;
        p->prox = novo;   

    }
    L->tamanho++;
    
    return 1;
}

int remover(lista* L, unsigned pos)
{
    if(L->start == NULL)
    {
        return 0;
    }
    if(pos < 1 || pos > L->tamanho)
    {
        return 0;
    }


    no* p = L->start;

    if(pos == 1)
    {
        L->start = p->prox;
        free(p);
    }
    else
    {
        no* anterior = L->start;
        for(int i = 1; i < pos - 1; i++)
        {

        anterior = anterior->prox;
        
        }
        p = anterior->prox;
        anterior->prox = p->prox;
        free(p);
        

    }

L->tamanho--;

return 1;
}

int libera(lista* L)
{

    no* p = L->start;
    while (p != NULL)
    {
        no* temporario = p; 
        p = p->prox; 
        free(temporario); 
    }
    
    free(L); 
    return 1;
}

unsigned sequencial(lista* lst, unsigned key)
{

unsigned counterSequencial = 0;
no* p = lst->start;

for(int i = 0; i < lst->tamanho; i++)
{
    counterSequencial++;
    if(p->val == key)
    {
        return counterSequencial;
    }
    p = p->prox;
}

inserir(lst, key,lst->tamanho);
return counterSequencial - 1;
}

unsigned mtf(lista* lst, unsigned key)
{
unsigned counterMTF = 0;
no* p = lst->start;
for(int i = 0; i < lst->tamanho; i++)
{
    counterMTF++;
    if(p->val == key)
    {
        int found = p->val;
        remover(lst, counterMTF);  
        inserir(lst, found, 1);
        return counterMTF;
    }
    p = p->prox;
}
inserir(lst, key, 1);
return counterMTF;
}

unsigned transpose(lista* lst, unsigned key)
{
unsigned counterTranspose = 0;
no* p = lst->start;
no* ant = NULL;
int pos = 1;
for(int i = 0; i < lst->tamanho; i++)
{
counterTranspose++;
if(p->val == key)
{
    if(ant)
    {
        int valor = p->val;
        remover(lst, pos);
        inserir(lst, valor, pos - 1);
        return counterTranspose;
    }
    else
    {
        return counterTranspose;
    }
}
pos++;
ant = p;
p = p->prox;
}
inserir(lst, key, 1);
return counterTranspose;
}

void count(lista* lst, unsigned key, unsigned* counterCount) {
    no* p = lst->start;
    no* anterior = NULL;
    *counterCount = 0;

    while (p) {
        (*counterCount)++;
        
        if (p->val == key) {
            p->peso++;

            // Remove o nó da posição atual
            if (anterior) {
                anterior->prox = p->prox;
            } else {
                lst->start = p->prox;
            }

            // Reinsere o nó na posição correta baseado no peso atualizado
            no* pIns = lst->start;
            no* prev = NULL;

            while (pIns && pIns->peso > p->peso) {
                prev = pIns;
                pIns = pIns->prox;
            }

            if (prev == NULL) {
                p->prox = lst->start;
                lst->start = p;
            } else {
                p->prox = prev->prox;
                prev->prox = p;
            }
            return;
        }

        anterior = p;
        p = p->prox;
    }

    // Insere o elemento na lista, pois ele não foi encontrado
    no* novo = malloc(sizeof(no));
    if (!novo) return;

    novo->val = key;
    novo->peso = 1;  // Inicia com peso 1
    novo->prox = lst->start;
    lst->start = novo;

    (*counterCount)++;
    lst->tamanho++;
}
int main(void)
{

int n = 0; 
int r = 0; 


scanf("%d", &n);
scanf("%d", &r);

int guardaNums;
unsigned seqSum = 0;
unsigned mtfSum = 0;
unsigned transSum = 0;
unsigned counterCount = 0;
unsigned countSum = 0;

lista* Lsequencial;
lista* Lmtf;
lista* Ltranspose;
lista* Lcount;

Lsequencial = criar_lista();
Lmtf = criar_lista();
Ltranspose = criar_lista();
Lcount = criar_lista();
for(int i = 0; i < n; i++)
{
    inserir(Lsequencial, i + 1, i + 1);
    inserir(Lmtf, i + 1, i + 1);
    inserir(Ltranspose, i + 1, i + 1);
    inserir(Lcount, i + 1, i + 1);
}

for(int j = 0; j < r; j++)
{
    scanf("%d", &guardaNums);
    seqSum = seqSum + sequencial(Lsequencial, guardaNums);
    mtfSum = mtfSum + mtf(Lmtf, guardaNums);
    transSum = transSum + transpose(Ltranspose, guardaNums);
    count(Lcount, guardaNums, &counterCount);
    countSum += counterCount;
}

libera(Lsequencial);
libera(Ltranspose);
libera(Lcount);
libera(Lmtf);
printf("Sequencial: %d\n", seqSum);
printf("MTF: %d\n", mtfSum);
printf("Transpose: %d\n", transSum);
printf("Count: %d\n", countSum);

}