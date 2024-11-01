#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int key;
    struct no* left;
    struct no* right;
}no;

typedef struct arvore
{
    int tam;
    no* cabeca;
}arvore;


arvore* arvore_criar()
{
    arvore* arv = malloc(sizeof(arvore));
    arv->tam = 0;
    arv->cabeca = NULL;
    return arv;

}

int inserir(arvore* arvor, int chave)
{

    
    no* novo = malloc(sizeof(no));
    novo->key = chave;
    novo->left = NULL;
    novo->right = NULL;

    if(arvor->cabeca == NULL)
    {
        arvor->cabeca = novo;
        return 1;
    }
    
    no* temp = arvor->cabeca;
    while(1)
    {
        if(temp->key > chave)
        {
            
            if(temp->left == NULL)
            {
                temp->left = novo;
                return 1;
            }
            temp = temp->left;
        }
        else if(temp->key < chave)
        {
            if(temp->right == NULL)
            {
                temp->right = novo;
                return 1;
            }
            temp = temp->left;
        }
    }
free(novo);
return 0;

}

no* findSuccessor(arvore* arv, int k)
{
    //Cabeca nula
    if(arv->cabeca == NULL)
    {
        return NULL;
    }

    no* temp = arv->cabeca;
    no* ant = NULL;
    while(1)
    {
        //Vai p/ esq. e guarda ant
        if(temp->key > k)
        {
            ant = temp;
            temp = temp->left;
        }
        //Vai p/ direita
        else if(temp->key < k)
        {
            temp = temp->right;
        }
        else
        {
        //Se tem um filho pra direita vai um pra direita e todos pra esquerda
        if(temp->right)
        {
            temp = temp->right;
            while(temp->left)
            {
                temp = temp->left;
            }
            return temp;
        }
        //Se não retorna ant
        return ant;
        }
        
    }
    //NULL se não achou na arvore
    return NULL;
}

no* findPredecessor(arvore* arv, int k)
{
    //Cabeca nula
    if(arv->cabeca == NULL)
    {
        return NULL;
    }

    no* temp = arv->cabeca;
    no* ant = NULL;
    while(temp)
    {
        //Vai p/ esq. e guarda ant
        if(temp->key > k)
        {
            temp = temp->left;
        }
        //Vai p/ direita
        else if(temp->key < k)
        {
            ant = temp;
            temp = temp->right;
        }
        else
        {
        //Se tem um filho pra direita vai um pra direita e todos pra esquerda
        if(temp->left)
        {
            temp = temp->left;
            while(temp->right)
            {
                temp = temp->right;
            }
            return temp;
        }
        //Se não retorna ant
        return ant;
        }
        
    }
    //NULL se não achou na arvore
    return NULL;
}

int remover(arvore* A, int k)
{
    if(A->cabeca == NULL)
    {
        return 0;
    }

    no* temp = A->cabeca;
    no* ant = NULL;
    //Encontrar valor e seu pai
    while(temp)
    {
        ant = temp;

        if(temp->key > k)
        {
            temp = temp->left;
        }
        else if(temp->key < k)
        {
            temp = temp->right;
        }
        else
        {
            break;
        }
    }
    //Se nao encontrou
    if(!temp)
    {
        return 0;
    }
    //Se tem nó esquerdo e direito
    if(temp->left && temp->right)
    {
        no* succ = findSuccessor(A, k);
        temp->key = succ->key;
        temp->left = succ->left;
        temp->right = succ->right;
        free(succ);
        return 1;
    }
    //Se nao tem nem nó esquerdo nem direito (folha)
    if(!temp->left && !temp->right)
    {
        if(!ant)
        {
            free(temp);
            return 1;
        }
        ant->left = NULL;
        ant->right = NULL;
        free(temp);
        return 1;
    }
    //Se tem nó esquerdo mas não tem nó direito
    if(temp->left && !temp->right)
    {
        //Se é a cabeça
        if(!ant)
        {
            A->cabeca = temp->left;
            free(temp);
            return 1;
        }
        ant->left = temp->left;
        free(temp);
    }
    //Se tem nó direito mas não tem nó esquerdo
    else if(!temp->left && temp->right)
    {
        //Se é a cabeça
        if(!ant)
        {
            A->cabeca = temp->left;
            free(temp);
            return 1;
        }
        ant->right = temp->right;
        free(temp);
    }
    
    return 1;

}

int equalTrees(arvore* A, arvore* B)
{
    no* pA = A->cabeca;
    no* pB = B->cabeca;

    while(1)
    {
        if(pA && pB)
        {
        if(pA->left && pB->left)
        {
            if(pA->key != pB->key)
            {
                return 0;
            }
            pA = pA->left;
            pB = pB->left;

        }
        else if(pA->right && pB->right)
        {
            if(pA->key != pB->key)
            {
                return 0;
            }
            pA = pA->right;
            pB = pB->right;
        }
        else if(pA->left && !pB->left)
        {
            return 0;
        }
        else if(!pA->left && pB->left)
        {
            return 0;
        }
        else if(pA->right && !pB->right)
        {
            return 0;
        }
        else if(!pA->right && pB->right)
        {
            return 0;
        }

        }
        else
        {
        return 1;
        }
    }
}

int segundaMaiorChave(arvore* a)
{
    no* temp = a->cabeca;
    no* ant = NULL;
    while(1)
    {
        if(temp->right)
        {
            ant = temp;
            temp = temp->right;
        }
        else
        {
            break;
        }
    }
    if(temp->left)
    {
    temp = temp->left;
    while(1)
    {
        if(temp->right)
        {
            temp = temp->right;
        }
        else
        {
            return temp->key;
        }
    }
    }
    else if(ant)
    {
    return ant->key;
    }
    else
    {
        return -1;
    }
    
}