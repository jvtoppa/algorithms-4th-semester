#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no {

  int nome_conj;
  int conj[127];
  int arrsize;
  struct no *prox;
  struct no *ant;

} no;

typedef struct lista {

  no *head;
  int tam;

} lista;

lista *criar() //
{

  lista *L = malloc(sizeof(lista));
  if (!L) {
    return NULL;
  }

  L->head = NULL;
  L->tam = 0;

  no *dummy = malloc(sizeof(no));

  dummy->ant = L->head;
  dummy->prox = NULL;

  for (int i = 0; i < 127; i++) {
    dummy->conj[i] = 1;
  }
  L->head = dummy;

  return L;
}

int gerar_conjunto(lista *L, int nomeC)
{
    no *novo = malloc(sizeof(no));
    if (!novo) {
        return 0;
    }
    novo->arrsize = 0;
    novo->nome_conj = nomeC;
    novo->prox = L->head->prox;
    novo->ant = L->head;
    L->head->prox = novo;
    L->tam++;
    
    return 1;
}

int inserir_elementos(lista *L, int arrval[], int nomeC, int sizeArr)
{
    for (no *p = L->head->prox; p != NULL; p = p->prox) 
    {
        if (p->nome_conj == nomeC) 
        {
            for (int i = p->arrsize; i < sizeArr; i++) 
            {
                p->conj[i] = arrval[i];
                p->arrsize++;
            }
        }
    }
}

void imprimir_lista(lista *L, int nomeC) //
{
  printf("C%d = {", nomeC);

  for (no *p = L->head->prox; p != NULL; p = p->prox) {
    if (p->nome_conj == nomeC) {
      for (int i = 0; i < p->arrsize; i++) {
        printf("%d", p->conj[i]);
        if ((i < p->arrsize - 1)) {
          printf(", ");
        }
      }
      break;
    }
  }

  printf("}\n");
}

int libera(lista *L) //
{

  no *p = L->head;
  while (p != NULL) {
    no *temporario = p;
    p = p->prox;
    free(temporario);
  }

  free(L);
  return 1;
}

int bubblesort(int vetor[], int arrsize) {
  for (int i = 0; i < arrsize; i++) {
    for (int j = 0; j < arrsize - 1; j++) {
      int x = vetor[j];
      int y = vetor[j + 1];
      if (y < x) {
        vetor[j] = y;
        vetor[j + 1] = x;
      }
    }
  }
}

int remove_elemento(lista *L, int nomeC, int remove_elem[], int size_remove) {
  for (no *p = L->head->prox; p != NULL; p = p->prox) {
    if (p->nome_conj == nomeC) {
      for (int i = 0; i < p->arrsize; i++) {
        for (int j = 0; j < size_remove; j++) {
          if (p->conj[i] == remove_elem[j]) {
            for (int k = i + 1; k < p->arrsize; k++) {
              p->conj[k-1] = p->conj[k];
            }
            p->arrsize--;
            i--;
            break;
          }
        }
      }
    }
  }

  return 1;
}

int uniao(lista* L, int nomeC1, int nomeC2, int nomeC3)
{
no* p = L->head->prox;
no* C1 = NULL;
no* C2 = NULL;
no* C3 = NULL;
while(p != NULL){
    if (p->nome_conj == nomeC1)
    {
        C1 = p;

    }
    if(p->nome_conj == nomeC2)
    {

        C2 = p;
    }
    if(p->nome_conj == nomeC3)
    {

        C3 = p;
    }

p = p->prox;
}
int arruniao[127];
int tamarr = 0;
for(int i = 0; i < C2->arrsize; i++)
{
    arruniao[tamarr] = C2->conj[i];
    tamarr++;
}
for(int i = 0; i < C3->arrsize; i++)
{
    arruniao[tamarr] = C3->conj[i];
    tamarr++;
}
for(int i = 0; i < tamarr; i++)
{
    for(int j = i + 1; j < tamarr; j++)
    {
        if(arruniao[j] == arruniao[i] && j != i)
        {
            for (int k = j; k < tamarr - 1; k++) {
                arruniao[k] = arruniao[k + 1];
            }
            tamarr--; 
            j--;
        }
    }    
}


if (C1 == NULL)
{
    gerar_conjunto(L,nomeC1);
    for(no* p = L->head->prox; p != NULL; p->prox)
    {
        if (p->nome_conj == nomeC1)
        {
            p->arrsize = 0;
            for(int i = 0; i < tamarr; i++){
                p->conj[i] = arruniao[i];
                p->arrsize++;
            }
            break;
        }
    }
}
else
{
    C1->arrsize = 0;
    for(int i = 0; i < tamarr; i++)
    {
        C1->conj[i] = arruniao[i];
        C1->arrsize++;    
    }
}

return 1;
}

int main(void) {
    lista *L = criar();

    int val;
    int tam = 0;
    int i = 0;
    int valores[127];

    while (scanf("%d", &val) == 1) {

        valores[i] = val;
        i++;
        tam++;
    }
    bubblesort(valores, tam);
    gerar_conjunto(L, 1);
    gerar_conjunto(L, 2);

    int conj1[] = {1,2,3,4,5};
    int conj2[] = {6,7,8,9,10};
    inserir_elementos(L, conj1, 1, 5);
    inserir_elementos(L, conj2, 2, 5);
    uniao(L, 3, 1, 2);

    imprimir_lista(L, 3);

    return 0;
}
