#include <stdlib.h>

typedef struct no
{
int data;
struct no* esq;
struct no* dir;

}no;

no* createTree(int data)
{
    no* prim = malloc(sizeof(no));
    prim->esq = NULL;
    prim->dir = NULL;
    prim->data = data;
    return prim;
}

no* insert_par_impar(int vec[], int vecSize, int* counter)
{
int top = vecSize;
if (*counter >= top)
{
    return NULL;
}
no* novo = createTree(vec[(*counter)]);
if(*counter % 2 == 0)
{
novo->esq = insert_par_impar(vec, vecSize, (*counter)++);
}
else{
novo->dir = insert_par_impar(vec, vecSize, (*counter)++);
}
return novo;
}

int numero_nos(no* cabeca, int* num)
{
    if(cabeca == NULL)
    {
        return 0;
    }

    numero_nos(cabeca->esq, num);
    numero_nos(cabeca->dir, num);
    (*num)++;
}

int numero_folhas(no* cabeca, int* num)
{
    if(cabeca == NULL)
    {
        return 1;
    }
    if(cabeca->esq == NULL && cabeca->dir == NULL)
    {
        (*num)++;
    }
    numero_folhas(cabeca->esq, num);
    numero_folhas(cabeca->dir, num);
    
}

int altura(no* cabeca)
{
    if(cabeca == NULL)
    {
        return 0;
    }
    
    int he = altura(cabeca->esq);
    int hd = altura(cabeca->dir);

    if(he > hd)
    {
        return he + 1;
    }
    return hd + 1;
}

void traverse(no* cabeca, int* returnSize, no* pai)
{
    if(cabeca == NULL)
    {
    return;
    }

        traverse(cabeca->esq, *returnSize, cabeca);
        if(pai != NULL){
            printf("%d (%d pai)",cabeca->data, pai->data);
        }
        
        traverse(cabeca->dir, *returnSize, cabeca);
}

int isEnraizada(no* cabeca)
{   
    int counter1 = 0;
    int counter2 = 0;
    numero_nos(cabeca->esq, &counter1);
    numero_nos(cabeca->dir, &counter2);
    if(counter1 == counter2)
    {
        return 1;
    }
    else
    {
        return 0;
    }


}

void inOrder(no* cabeca)
{
    if(cabeca == NULL)
    {
        return;
    }
    inOrder(cabeca->esq);
    if(cabeca->esq != NULL)
    {
        cabeca->data = cabeca->data + cabeca->esq->data;
    }
    if(cabeca->dir != NULL)
    {
        cabeca->data = cabeca->data + cabeca->dir->data;
    }
    printf("%d ", cabeca->data);
    inOrder(cabeca->dir);
}