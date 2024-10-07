#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no {

  int val;
  struct no *prox;

} no;

typedef struct lista {

  no *head;
  int tam;
  int nome;

} lista;

lista *criar(int nomeC) //
{

  lista *L = malloc(sizeof(lista));
  if (!L) {
    return NULL;
  }

  L->head = NULL;
  L->tam = 0;
  L->nome = nomeC;

  no *dummy = malloc(sizeof(no));

  dummy->prox = NULL;

  L->head = dummy;

  return L;
}

int gerar_node(lista *L, int val_conj) {
  no *novo = malloc(sizeof(no));
  if (!novo) {
    return 0;
  }
  novo->val = val_conj;
  novo->prox = L->head->prox;
  L->head->prox = novo;
  L->tam++;

  return 1;
}

int inserir_elementos(lista *arrval[], int nomeC, int val_conj) {
  for (int i = 0; i < 127; i++) {
    if (arrval[i]->nome == nomeC) {
      gerar_node(arrval[i], val_conj);
      return 1;
    }
  }
  return 0;
}
int remover(lista *arrayLista[], int nomeC, int val) {
  for (int i = 0; i < 127; i++) {
    if (arrayLista[i]->nome == nomeC) {
      no *ant = arrayLista[i]->head;

      no *p = arrayLista[i]->head->prox;
      while (p != NULL) {

        if (p->val == val) {
          p = ant->prox;
          ant->prox = p->prox;
          free(p);
          arrayLista[i]->tam--;
          return 1;
        }
        ant = p;
        p = p->prox;
      }
      return 0;
    }
  }

  return 1;
}

lista *clone(lista *L) {
  lista *Li = malloc(sizeof(lista));
  if (!Li) {
    return NULL;
  }

  Li->head = malloc(sizeof(no));
  Li->tam = 0;
  Li->nome = 0;

  Li->head->prox = NULL;

  no *ultimop = Li->head;
  no *p = L->head->prox;
  while (p != NULL) {
    no *novo = malloc(sizeof(no));
    if (!novo) {
      no *temp = Li->head;
      no *pr = NULL;
      while (temp != NULL) {
        pr = temp->prox;
        free(temp);
        temp = pr;
      }
      free(Li);
      return NULL;
    }

    novo->val = p->val;
    novo->prox = NULL;
    ultimop->prox = novo;
    ultimop = novo;
    p = p->prox;
  }
  Li->tam = L->tam;
  return Li;
}

int libera(lista *L) {
  if (L == NULL)
    return 0;

  no *p = L->head;
  while (p != NULL) {
    no *temporario = p;
    p = p->prox;
    free(temporario);
  }

  free(L);
  return 1;
}
lista *uniao(lista *arrList[], int nomeC1, int nomeC2, int nomeC3) {
  lista *conj1 = NULL;
  lista *conj2 = NULL;
  lista *conj3 = NULL;

  for (int i = 0; i < 127; i++) {
    if (arrList[i]->nome == nomeC1) {
      conj1 = arrList[i];
    }
    if (arrList[i]->nome == nomeC2) {
      conj2 = clone(arrList[i]);
    }
    if (arrList[i]->nome == nomeC3) {
      conj3 = clone(arrList[i]);
    }
  }

  if (!conj2 || !conj3) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  lista *res = malloc(sizeof(lista));
  if (!res) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  res->head = malloc(sizeof(no));
  if (!res->head) {
    free(res);
    libera(conj2);
    libera(conj3);
    return NULL;
  }
  res->head->prox = NULL;
  res->tam = 0;
  res->nome = nomeC1;

  no *ultimo = res->head;
  no *p = conj2->head->prox;
  while (p != NULL) {
    no *novo = malloc(sizeof(no));
    if (!novo) {
      libera(res);
      libera(conj2);
      libera(conj3);
      return NULL;
    }
    novo->val = p->val;
    novo->prox = NULL;
    ultimo->prox = novo;
    ultimo = novo;
    res->tam++;
    p = p->prox;
  }

  p = conj3->head->prox;
  while (p != NULL) {
    no *novo = malloc(sizeof(no));
    if (!novo) {
      libera(res);
      libera(conj2);
      libera(conj3);
      return NULL;
    }
    novo->val = p->val;
    novo->prox = NULL;
    ultimo->prox = novo;
    ultimo = novo;
    res->tam++;
    p = p->prox;
  }

  libera(conj2);
  libera(conj3);

  return res;
}
lista *interseccao(lista *arrList[], int nomeC1, int nomeC2, int nomeC3) {
  lista *conj1 = NULL;
  lista *conj2 = NULL;
  lista *conj3 = NULL;
  for (int i = 0; i < 127; i++) {
    if (arrList[i]->nome == nomeC1) {
      conj1 = arrList[i];
    }
    if (arrList[i]->nome == nomeC2) {
      conj2 = clone(arrList[i]);
    }
    if (arrList[i]->nome == nomeC3) {
      conj3 = clone(arrList[i]);
    }
  }

  if (!conj2 || !conj3) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  lista *res = malloc(sizeof(lista));
  if (!res) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  res->head = malloc(sizeof(no));
  if (!res->head) {
    free(res);
    libera(conj2);
    libera(conj3);
    return NULL;
  }
  res->head->prox = NULL;
  res->tam = 0;
  res->nome = nomeC1;

  no* ultimo = res->head;
  
for(no* p = conj2->head->prox; p != NULL; p = p->prox)
  {
    no* novo = malloc(sizeof(no));
    if(novo == NULL)
    {
      libera(conj2);
      libera(conj3);
      libera(res);
      return NULL;
    }
    for(no* q = conj3->head->prox; q != NULL; q = q->prox)
    {
    if(q->val == p->val)
    {
      novo->prox = NULL;
      novo->val = p->val;
      ultimo->prox = novo;
      ultimo = novo;
      res->tam++;
    }
    }
  }

  libera(conj2);
  libera(conj3);
  return res;
}
lista *diferenca(lista *arrList[], int nomeC1, int nomeC2, int nomeC3) {
  lista *conj1 = NULL;
  lista *conj2 = NULL;
  lista *conj3 = NULL;
  for (int i = 0; i < 127; i++) {
    if (arrList[i]->nome == nomeC1) {
      conj1 = arrList[i];
    }
    if (arrList[i]->nome == nomeC2) {
      conj2 = clone(arrList[i]);
    }
    if (arrList[i]->nome == nomeC3) {
      conj3 = clone(arrList[i]);
    }
  }

  if (!conj2 || !conj3) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  lista *res = malloc(sizeof(lista));
  if (!res) {
    libera(conj2);
    libera(conj3);
    return NULL;
  }

  res->head = malloc(sizeof(no));
  if (!res->head) {
    free(res);
    libera(conj2);
    libera(conj3);
    return NULL;
  }
  res->head->prox = NULL;
  res->tam = 0;
  res->nome = nomeC1;

  no* q = conj3->head->prox;
  no* ultimo = res->head;

for(no* p = conj2->head->prox; p != NULL; p = p->prox)
  {
    int fl = 0;
    no* novo = malloc(sizeof(no));
    if(novo == NULL)
    {
      libera(conj2);
      libera(conj3);
      libera(res);
      return NULL;
    }
    for(no* q = conj3->head->prox; q != NULL; q = q->prox)
    {
      if(q->val == p->val)
      {
        fl = 1;
        break;
      }
    }
    if(!fl)
      {
        novo->prox = NULL;
        novo->val = p->val;
        ultimo->prox = novo;
        ultimo = novo;
        res->tam++;
    }

  
  
}
libera(conj2);
libera(conj3);   
return res;    
}

void x_esta_em_c(lista *arrList[], int nomeC1, int valor) {
  lista *conj1 = NULL;
  for (int i = 0; i < 127; i++) {
    if (arrList[i]->nome == nomeC1) 
    {
      conj1 = arrList[i];
      break;
    }
  }

int fl = 0;
for(no* p = conj1->head->prox; p != NULL; p = p->prox)
  {
    fl = 0;
    if(p->val == valor)
    {
      fl = 1;
      break;
    }
    
    }

if(fl == 1)
{
  printf("%d esta em C%d", valor, nomeC1);
}
else
{
  printf("%d nao esta em C%d", valor, nomeC1);
}   
}



void imprimir_lista(lista *arrayLista[], int nomeC) {
  printf("C%d = {", nomeC);
  for (int i = 0; i < 127; i++) {
    if (arrayLista[i]->nome == nomeC) {
      for (no *p = arrayLista[i]->head->prox; p != NULL; p = p->prox) {
        printf("%d", p->val);
        if (!(p->prox == NULL)) {
          printf(", ");
        }
      }
      break;
    }
  }
  printf("}\n");
}

int main(void) {

  lista *arrayLista[127];
  for (int i = 0; i < 127; i++)
    arrayLista[i] = criar(i);

  inserir_elementos(arrayLista, 2, 1);
  for(int i = 0; i < 10; i++)
  {
    inserir_elementos(arrayLista, 3, i);
  }
  
  inserir_elementos(arrayLista, 3, 10000);
  inserir_elementos(arrayLista, 4, 10000);
  inserir_elementos(arrayLista, 2, 2);
  imprimir_lista(arrayLista, 2);
  imprimir_lista(arrayLista, 3);
  imprimir_lista(arrayLista, 4);

  arrayLista[2] = diferenca(arrayLista, 2, 3, 4);
  imprimir_lista(arrayLista, 2);
  x_esta_em_c(arrayLista, 2, 10000);
}

/*TODO:

-Comandos
-União não pode ter elementos repetidos
-Interseção precisa garantir que não hajam elementos repetidos entrando no programa
-Print em ordem crescente

 lista *temp = uniao(arrayLista, 2, 3, 4);
    if (temp != NULL) {
        libera(arrayLista[2]);  
        arrayLista[2] = temp;
    }
    
    imprimir_lista(arrayLista, 2);
    
    for (int i = 0; i < 127; i++) {
        libera(arrayLista[i]);
    }
    return 0;
*/
