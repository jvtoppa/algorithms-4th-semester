#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int key;
    char nome[100];
    float pontos;
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

int inserir(arvore* arvor, int chave, char nome[], float pontos)
{

    
    no* novo = malloc(sizeof(no));
    if(!novo)
    {
        printf("memoria insuficiente\n");
        return 0;
    }
    novo->key = chave;
    novo->pontos = pontos;
    strcpy(novo->nome, nome);
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
            temp = temp->right;
        }
        if(temp->key == chave)
        {
            return 0;
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
        if(temp->key > k)
        {
            temp = temp->left;
        }
        else if(temp->key < k)
        {
            ant = temp;
            temp = temp->right;
        }
        else
        {

        if(temp->left)
        {
            temp = temp->left;
            while(temp->right)
            {
                temp = temp->right;
            }
            return temp;
        }
        return ant;
        }
        
    }
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
        if(temp->key > k)
        {
            ant = temp;
            temp = temp->left;
        }
        else if(temp->key < k)
        {
            ant = temp;
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
        int temp_key = succ->key;
        float temp_pontos = succ->pontos;
        char temp_nome[100];
        strcpy(temp_nome, succ->nome);
        
        remover(A, succ->key);
        
        temp->key = temp_key;
        temp->pontos = temp_pontos;
        strcpy(temp->nome, temp_nome);
        return 1;
    }
    //Se é folha
    if(!temp->left && !temp->right)
    {
        if(!ant) // Se é a cabeça
        {
            A->cabeca = NULL;
        }
        else if(ant->left == temp)
        {
            ant->left = NULL;
        }
        else
        {
            ant->right = NULL;
        }
        free(temp);
        return 1;
    }

    // Se tem nó esquerdo mas não tem nó direito
    if(temp->left && !temp->right)
    {
        // Se é a cabeça
        if(!ant)
        {
            A->cabeca = temp->left;
        }
        else if(ant->left == temp)
        {
            ant->left = temp->left;
        }
        else
        {
            ant->right = temp->left;
        }
        free(temp);
        return 1;
    }
    // Se tem nó direito mas não tem nó esquerdo
    else if(!temp->left && temp->right)
    {
        // Se é a cabeça
        if(!ant)
        {
            A->cabeca = temp->right;
        }
        else if(ant->left == temp)
        {
            ant->left = temp->right;
        }
        else
        {
            ant->right = temp->right;
        }
        free(temp);
        return 1;
    }

    return 1;
}

no* findK(arvore* A, int k)
{
    no* temp = A->cabeca;
    while(temp)
    {
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
            
            return temp;
        }
    }
    return NULL;
}

void print_inorder(no* A)
{
    if(A == NULL)
    {
        return;
    }

    print_inorder(A->left);
    printf("%s (%d) ", A->nome, A->key);
    print_inorder(A->right);

}

no* maximum(arvore* A)
{
    if(A->cabeca)
    {
        no* temp = A->cabeca;
        while(1)
        {
            if(temp->right)
            {
                temp = temp->right;
            }
            else return temp;
        }
    }
    return NULL;
}
no* minimum(arvore* A)
{
    if(A->cabeca)
    {
        no* temp = A->cabeca;
        while(1)
        {
            if(temp->left)
            {
                temp = temp->left;
            }
            else return temp;
        }
    }
    return NULL;
}

int* interval(arvore* A, int bot, int top, int* tamanho)
{
    int* ervalo = malloc(1000 * sizeof(int)); 
    if (ervalo == NULL) 
    {
        *tamanho = 0;
        return NULL;
    }

    *tamanho = 0;
    no* temp = A->cabeca;
    no* ant = NULL;

    while (temp)
    {
        if (!temp->left)
        {
            if (temp->key >= bot && temp->key <= top)
            {
                ervalo[*tamanho] = temp->key;
                (*tamanho)++;
            }
            temp = temp->right;
        }
        else
        {
            ant = temp->left;
            while (ant->right && ant->right != temp)
            {
                ant = ant->right;
            }
            if (!ant->right)
            {
                ant->right = temp; 
                temp = temp->left;
            }
            else
            {
                ant->right = NULL;
                if (temp->key >= bot && temp->key <= top)
                {
                    ervalo[*tamanho] = temp->key;
                    (*tamanho)++;
                }
                temp = temp->right;
            }
        }
    }

    if (*tamanho == 0)
    {
        free(ervalo);
        return NULL;
    }
    
    ervalo = realloc(ervalo, (*tamanho) * sizeof(int));
    return ervalo;
}
void libera(no* cabeca) {
    if (cabeca == NULL) {
        return;
    }
    libera(cabeca->left);
    libera(cabeca->right);
    free(cabeca);
}
int main()
{
    char nome[100];
    float pontos = 0;
    int chave = 0;
    int ervalo1 = 0;
    int ervalo2 = 0;
    char frase[100];
    arvore* A = NULL;
    
    while(1)
    {
        scanf("%s", frase);
        
        if(strcmp(frase, "criar") == 0)
        {
            if(A)
            {
                libera(A->cabeca);
                free(A);
            }
            A = arvore_criar();
        }
        else if(strcmp(frase, "inserir") == 0)
        {
            scanf("%d, %99[^,], %f", &chave, nome, &pontos);
            inserir(A, chave, nome, pontos);
        }
        else if(strcmp(frase, "buscar-intervalo") == 0)
        {
            int tamanho;
            scanf("%d %d", &ervalo1, &ervalo2);
            printf("clientes no intervalo [%d,%d]: ", ervalo1, ervalo2);
            int* erval = interval(A, ervalo1, ervalo2, &tamanho);
            if(erval)
            {
            for(int i = 0; i < tamanho; i++)
            {
                printf("%d ", erval[i]);
            }
            printf("\n");
            }
            else
            {
            printf("nenhum\n");
            }
        }
        else if(strcmp(frase, "remover") == 0)
        {
            scanf("%d", &chave);
            remover(A, chave);
        }
        else if(strcmp(frase, "minimo") == 0)
        {
            no* mini = minimum(A);
            if(mini)
            {
                printf("minimo: %d\n", mini->key);
            }
            else
            {
                printf("arvore vazia\n");
            }
        }
        else if(strcmp(frase, "maximo") == 0)
        {
            no* maxi = maximum(A);
            if(maxi)
            {
                printf("maximo: %d\n", maxi->key);
            }
            else
            {
                printf("arvore vazia\n");
            }
        }
        else if(strcmp(frase, "predecessor") == 0)
        {
            scanf("%d", &chave);
            no* ke = findK(A, chave);
            no* pred = findPredecessor(A, chave);
            if(pred && ke)
            {
                printf("predecessor de %d: %d\n", chave, pred->key);
            }
            else if(ke)
            {
                printf("predecessor de %d: nao ha\n", chave);
            }
            else
            {
                printf("nao ha cliente %d\n", chave);
            }
        }
        else if(strcmp(frase, "sucessor") == 0)
        {
            scanf("%d", &chave);
            no* succ = findSuccessor(A, chave);
            no* ke = findK(A, chave);
            if(succ && ke)
            {
                printf("sucessor de %d: %d\n", chave, succ->key);
            }
            else if(ke)
            {
                printf("sucessor de %d: nao ha\n", chave);
            }
            else
            {
                printf("nao ha cliente %d\n", chave);
            }
        }
        else if(strcmp(frase, "imprimir") == 0)
        {
            if(A->cabeca)
            {
            printf("clientes: ");
            print_inorder(A->cabeca);
            printf("\n");
            }
            else
            {
            printf("arvore vazia\n");
            }
            
        }
        else if(strcmp(frase, "buscar") == 0)
        {
            scanf("%d", &chave);
            no* temp = findK(A, chave);
            if(temp)
            {
            printf("cliente %d: %s, %.2f pontos\n", temp->key, temp->nome, temp->pontos);
            }
            else
            {
            printf("nao ha cliente %d\n", chave);
            }
        }
        else if(strcmp(frase, "terminar") == 0)
        {
            if(A)
            {
                libera(A->cabeca);
                free(A);
            }
            return 1;
        }
    }
}