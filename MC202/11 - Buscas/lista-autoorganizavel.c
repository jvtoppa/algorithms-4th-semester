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
        no* atual = L->start;
        for (int i=1; i < posicao - 1; i++)
        {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;   

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


    no* atual = L->start;

    if(pos == 1)
    {
        L->start = atual->prox;
        free(atual);
    }
    else
    {
        no* anterior = L->start;
        for(int i = 1; i < pos - 1; i++)
        {

        anterior = anterior->prox;
        
        }
        atual = anterior->prox;
        anterior->prox = atual->prox;
        free(atual);
        

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

unsigned count(lista* lst, unsigned key) {
    unsigned counterCount = 0;
    unsigned pos = 1;
    no* p = lst->start;

    for (int i = 0; i < lst->tamanho; i++) {
        counterCount++;
        if (p->val == key) {
            p->peso++;
            break;
        }
        pos++;
        p = p->prox;
    }

    if (pos > lst->tamanho) {
        no* q = lst->start;
        unsigned pos2 = 1;
        
        while (q != NULL) {
            if (q->peso == 0) {
                inserir(lst, key, pos2);
                return counterCount;
            }
            pos2++;
            q = q->prox;
        }
        
        inserir(lst, key, pos2);
        return counterCount;
    }

    unsigned novaPos = 1;
    
    for (int i = 0; i < lst->tamanho; i++) {
        no* atual = lst->start;
        for (int j = 0; j < i; j++) {
            atual = atual->prox;
        }
        if (atual->peso <= p->peso && i != pos-1) {
            novaPos = i + 1;
            break;
        }
    }

    if (novaPos < pos) {
        remover(lst, pos);
        inserir(lst, key, novaPos);
    }
    
    return counterCount;
}
int main(void)
{

int n = 0; 
int r = 0; 


scanf("%d", &n);
scanf("%d", &r);

int guardaNums;
int seqSum = 0;
int mtfSum = 0;
int transSum = 0;
int countSum = 0;


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
    countSum = countSum + count(Lcount, guardaNums);
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