#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
char caract;
struct no* next;

} no;

typedef struct list
{
    int tam;
    no* lista;
} list;

list* criar(void)
{
    list* L = malloc(sizeof(list));
    L->lista = NULL;
    L->tam = 0;
    return L;

}

int insertB(list* lst, char caractere)
{
    no* novo = malloc(sizeof(no));
    if(!novo)
    {
        return 0;
    }
    novo->caract = caractere;
    novo->next = NULL;
    
    novo->next = lst->lista;
    lst->lista = novo;
    lst->tam++;

    return 1;
}

int removePos(list* lst, int pos)
{
    if(pos > lst->tam)
    {
        return 0;
    }
    no* p = lst->lista;
    no* ant = NULL;
    for(int i = 0; i < pos; i++)
    {
        ant = p;
        p = p->next;
    }
    if(pos == 0)
    {
    lst->lista = p->next;
    free(p);
    }
    else
    {
        ant->next = NULL;
    }
    free(p);
}

void print(list* lst)
{
    for(no* p = lst->lista; p != NULL; p = p->next)
    {
        printf("%c\n", p->caract);
    }
}

int main()
{
    list* L = criar();
    insertB(L, 'C');
    insertB(L, 'B');
    insertB(L, 'A');
    removePos(L, 0);
    //removePos(L, 1);
    print(L);
}