#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
double val;
struct no* prox;

} no;

typedef struct lista
{
int tamanho;
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

int inserir(lista* L, double val, int posicao)
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

    if(posicao == 1) //Inserção em pos == 1
    {
        novo->prox = L->start;
        L->start = novo;

    }

    else //Inserção em outra posição
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

int remover(lista* L, int pos)
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

int reverte(lista* L, int pos1, int pos2)
{

    if(L == NULL)
    {
        return 0;
    }
    if(pos1 < 1 || pos1 > L->tamanho || pos2 < 1 || pos2 > L->tamanho)
    {
        return 0;
    }


    no* aux_inferior = L->start;
    no* prev = NULL;

    for(int i = 1; i < pos1; i++)
    {
        prev = aux_inferior;
        aux_inferior = aux_inferior->prox;
    }
    no* cauda = aux_inferior;
    no* con = prev;

    for(int i = pos1; i < pos2 + 1; i++)
    {
        no* next = aux_inferior->prox; 
        aux_inferior->prox = prev; 
        prev = aux_inferior; 
        aux_inferior = next; 
    }

    
    if (con != NULL)
    {
        con->prox = prev; 
    }
    else
    {
        L->start = prev; 
    }

    cauda->prox = aux_inferior;

    return 1;
}

int move(lista* L, int pos1, int pos2, int pos3)
{

    if (L == NULL || pos1 < 1 || pos2 < pos1 || pos2 > L->tamanho || pos3 < 1 || pos3 > L->tamanho) 
    {
        return 0; 
    }


    no* prev_start = NULL;
    no* start = L->start;


    for (int i = 1; i < pos1; i++)
    {
        prev_start = start;
        start = start->prox;
    }


    no* end = start;
    for (int i = pos1; i < pos2; i++)
    {
        end = end->prox;
    }
    
    no* next = end->prox;

    if (pos3 == 1)
    {
        L->start = start;
    }
    else
    {
        no* prev_new_pos = L->start;
        for (int i = 1; i < pos3 - 1; i++)
        {
            prev_new_pos = prev_new_pos->prox;
        }
        prev_new_pos->prox = start;
    }

    end->prox = next;

    if (prev_start != NULL)
    {
        prev_start->prox = next; 
    }

    return 1; 
}

void imprimir(lista* L)
{
    if(L->tamanho == 0)
    {
        return;
    }
    for (no* p = L->start; p != NULL; p = p->prox)
    {
        printf("%0.2lf ", p->val);
    }
    printf("\n");
}

int libera(lista* L)
{
if (L == NULL) return 0;

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

int main(void)
{

lista* lst;

while(1)
{
    char let = 0;
    int posit = 0;
    int posit2 = 0;
    int posit3 = 0;
    double val = 0;

    if((scanf(" %c", &let) == 1))
    {
        if (let == 'c')
        {
            if (lst != NULL)
            {
                libera(lst);
            }


            lst = criar_lista();
        }
        else if (let == 'p') 
        {
            if(lst != NULL)
            {
                imprimir(lst);
            }
            
        }
        else if (let == 'i')
        {
            if(scanf("%d %lf", &posit, &val) == 2)
            {
                if(lst != NULL)
                {
                    inserir(lst, val, posit + 1);
                }
                
            }
            
        }
        else if (let == 'r')
        {
            if(scanf("%d", &posit) == 1)
            {
                if(lst != NULL)
                {
                    remover(lst, posit + 1);
                }
            }
            
        }
        else if (let == 'v')
        {
            if(scanf("%d %d", &posit, &posit2) == 2)
            {
                if(lst != NULL)
                {
                    reverte(lst, posit+1, posit2+1);
                }
            }
        }
        else if(let == 't')
        {
            if(lst != NULL)
            {
                libera(lst);
                return 1;
            }
        }
        else if(let == 'x')
        {
            if(scanf("%d %d %d", &posit, &posit2, &posit3) == 3)
            {
                if(lst != NULL)
                {
                    move(lst, posit, posit2, posit3);
                }
            }
        }
    }
}

}