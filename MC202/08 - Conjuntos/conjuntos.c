#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no {

<<<<<<< HEAD
  int val;
  struct no *prox;
=======
  int nome_conj;
  int conj[127];
  int arrsize;
  struct no *prox;
  struct no *ant;
>>>>>>> 7e3fe16996041694d3d76bf8f5ded5cb4ae11f27

} no;

typedef struct lista {

  no *head;
  int tam;
<<<<<<< HEAD
  int nome;

} lista;

lista *criar(int nomeC) //
=======

} lista;

lista *criar() //
>>>>>>> 7e3fe16996041694d3d76bf8f5ded5cb4ae11f27
{

  lista *L = malloc(sizeof(lista));
  if (!L) {
    return NULL;
  }
<<<<<<< HEAD

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
    //printf("feito");
    if (arrval[i] != NULL && arrval[i]->nome == nomeC) {
        
         no* p = NULL;
         for(p = arrval[i]->head->prox; p != NULL; p = p->prox)
        {
            if(p->val == val_conj)
            {
                return 0;
            }
        }
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
    lista *conj2 = NULL;
    lista *conj3 = NULL;

    if (nomeC2 == nomeC3) {
        for (int i = 0; i < 127; i++) {
            if (arrList[i] != NULL && arrList[i]->nome == nomeC2) {
                conj2 = clone(arrList[i]);
                conj3 = conj2; 
                break;
            }
        }
    } else {
        for (int i = 0; i < 127; i++) {
            if (arrList[i] != NULL) {
                if (arrList[i]->nome == nomeC2) {
                    conj2 = clone(arrList[i]);
                } else if (arrList[i]->nome == nomeC3) {
                    conj3 = clone(arrList[i]);
                }
            }
        }
    }

    if (!conj2 || !conj3) {
        if (conj2) libera(conj2);
        if (conj3 && nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }

    lista *res = malloc(sizeof(lista));
    if (!res) {
        libera(conj2);
        if (nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }

    res->head = malloc(sizeof(no));
    if (!res->head) {
        free(res);
        libera(conj2);
        if (nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }
    res->head->prox = NULL;
    res->tam = 0;
    res->nome = nomeC1;

    no *ultimo = res->head;

    for (no *p = conj2->head->prox; p != NULL; p = p->prox) {
        no *novo = malloc(sizeof(no));
        if (!novo) {
            libera(res);
            libera(conj2);
            if (nomeC2 != nomeC3) libera(conj3);
            return NULL;
        }
        novo->val = p->val;
        novo->prox = NULL;
        ultimo->prox = novo;
        ultimo = novo;
        res->tam++;
    }

    for (no *p = conj3->head->prox; p != NULL; p = p->prox) {
        int encontrado = 0;

   
        for (no *q = res->head->prox; q != NULL; q = q->prox) {
            if (q->val == p->val) {
                encontrado = 1;
                break;
            }
        }

       
        if (!encontrado) {
            no *novo = malloc(sizeof(no));
            if (!novo) {
                libera(res);
                libera(conj2);
                if (nomeC2 != nomeC3) libera(conj3);  
                return NULL;
            }
            novo->val = p->val;
            novo->prox = NULL;
            ultimo->prox = novo;
            ultimo = novo;
            res->tam++;
        }
    }

    
    libera(conj2);
    if (nomeC2 != nomeC3) libera(conj3);

    return res;
}
lista *interseccao(lista *arrList[], int nomeC1, int nomeC2, int nomeC3) {
  lista *conj2 = NULL;
  lista *conj3 = NULL;
    for (int i = 0; i < 127; i++) {
      if (arrList[i] != NULL) {
        if (arrList[i]->nome == nomeC2 && arrList[i]->nome == nomeC3) {
            conj2 = clone(arrList[i]);
            conj3 = conj2; 
            break;
        }
        if (arrList[i]->nome == nomeC2) {
          conj2 = clone(arrList[i]);
        }
        else if (arrList[i]->nome == nomeC3) {
          conj3 = clone(arrList[i]);
        }
      }
    }

 
  if (!conj2 || !conj3) {
    if (conj2) libera(conj2);
    if (conj3 && nomeC2 != nomeC3) libera(conj3);
    return NULL;
  }

  lista *res = malloc(sizeof(lista));
  if (!res) {
    libera(conj2);
    if (nomeC2 != nomeC3) libera(conj3);
    return NULL;
  }

  res->head = malloc(sizeof(no));
  if (!res->head) {
    free(res);
    libera(conj2);
    if (nomeC2 != nomeC3) libera(conj3);
    return NULL;
  }
  res->head->prox = NULL;
  res->tam = 0;
  res->nome = nomeC1;

  no *ultimo = res->head;

  for (no *p = conj2->head->prox; p != NULL; p = p->prox) {
    for (no *q = conj3->head->prox; q != NULL; q = q->prox) {
      if (q->val == p->val) {
        int encontrado = 0;
        for (no *r = res->head->prox; r != NULL; r = r->prox) {
          if (r->val == p->val) {
            encontrado = 1;
            break;
          }
        }
        
        if (!encontrado) {
          no *novo = malloc(sizeof(no));
          if (!novo) {
            libera(res);
            libera(conj2);
            if (nomeC2 != nomeC3) libera(conj3);
            return NULL;
          }
          novo->val = p->val;
          novo->prox = NULL;
          ultimo->prox = novo;
          ultimo = novo;
          res->tam++;
        }
        break;
      }
    }
  }

  libera(conj2);
  if (nomeC2 != nomeC3) libera(conj3);
  return res;
}


lista *diferenca(lista *arrList[], int nomeC1, int nomeC2, int nomeC3) {
    lista *conj2 = NULL;
    lista *conj3 = NULL;

    if (nomeC2 == nomeC3) {
        for (int i = 0; i < 127; i++) {
            if (arrList[i] != NULL && arrList[i]->nome == nomeC2) {
                conj2 = clone(arrList[i]);
                conj3 = conj2;
                break;
            }
        }
    } else {
        for (int i = 0; i < 127; i++) {
            if (arrList[i] != NULL) {
                if (arrList[i]->nome == nomeC2) {
                    conj2 = clone(arrList[i]);
                } else if (arrList[i]->nome == nomeC3) {
                    conj3 = clone(arrList[i]);
                }
            }
        }
    }

    if (!conj2 || !conj3) {
        if (conj2) libera(conj2);
        if (conj3 && nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }

    lista *res = malloc(sizeof(lista));
    if (!res) {
        libera(conj2);
        if (nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }

    res->head = malloc(sizeof(no));
    if (!res->head) {
        free(res);
        libera(conj2);
        if (nomeC2 != nomeC3) libera(conj3);
        return NULL;
    }
    res->head->prox = NULL;
    res->tam = 0;
    res->nome = nomeC1;

    no *ultimo = res->head;

    for (no *p = conj2->head->prox; p != NULL; p = p->prox) {
        int encontrado = 0;
        for (no *q = conj3->head->prox; q != NULL; q = q->prox) {
            if (q->val == p->val) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            no *novo = malloc(sizeof(no));
            if (!novo) {
                libera(res);
                libera(conj2);
                if (nomeC2 != nomeC3) libera(conj3);
                return NULL;
            }
            novo->val = p->val;
            novo->prox = NULL;
            ultimo->prox = novo;
            ultimo = novo;
            res->tam++;
        }
    }

    libera(conj2);
    if (nomeC2 != nomeC3) libera(conj3);
    return res;
}

void x_esta_em_c(lista *arrList[], int nomeC1, int valor) {
  lista *conj1 = NULL;
  for (int i = 0; i < 127; i++) {
    if (arrList[i] != NULL && arrList[i]->nome == nomeC1) 
    {
      conj1 = arrList[i];
      break;
    }
  }
int fl = 0;
 if (conj1 == NULL) {
    return;
  }
for(no* p = conj1->head->prox; p != NULL; p = p->prox)
  {
    if(p->val == valor)
    {
      fl = 1;
      break;
    }
    
    }

if(fl == 1)
{
  printf("%d esta em C%d\n", valor, nomeC1);
}
else
{
  printf("%d nao esta em C%d\n", valor, nomeC1);
}   
}

void bubblesort(int vetor[], int arrsize) {
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


void imprimir_lista(lista *arrayLista[], int nomeC) 
{
  printf("C%d = {", nomeC);
  for (int i = 0; i < 127; i++) {
    if (arrayLista[i] != NULL && arrayLista[i]->nome == nomeC) {
        int* tam = malloc(sizeof(int)*arrayLista[i]->tam);
        int x = 0;
        for (no *p = arrayLista[i]->head->prox; p != NULL; p = p->prox) 
        {
            tam[x] = p->val;
            x++;
        }
        bubblesort(tam, arrayLista[i]->tam);
        for(int j = 0; j < arrayLista[i]->tam; j++)
        {
            printf("%d", tam[j]);
            if(j < arrayLista[i]->tam - 1)
=======

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
>>>>>>> 7e3fe16996041694d3d76bf8f5ded5cb4ae11f27
            {
                p->conj[i] = arrval[i];
                p->arrsize++;
            }
        }
<<<<<<< HEAD
        free(tam);
         break;
    }
   
    }

  printf("}\n");
}

int main(void) {

    lista *arrayLista[127] = {NULL};
    char let;
    int dump;
    int nomeC, nomeC2, nomeC3, val;
    int i = 0; 

    while(scanf(" %c", &let) == 1) {

        if (i == 128)
        {
            i = 0;
        }



        if(let == 'c') {
            if(scanf("%d", &nomeC) != 1) {
                break;
            }
    
            int existe = 0;
            int posicao_existente = 0;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    existe = 1;
                    posicao_existente = j;
                    break;
                }
            }

            if(existe) {
                libera(arrayLista[posicao_existente]);
                arrayLista[posicao_existente] = criar(nomeC);
                continue;
            }

            int posliv = -1;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] == NULL) {
                    posliv = j;
                    break;
                }
            }
            if(posliv != -1) {
                arrayLista[posliv] = criar(nomeC);
            }
        }
         else if (let == 'i')
        {
            if(scanf("%d", &nomeC) == 1)
            {
                if(scanf("%d", &dump) == 1)
               while(scanf("%d", &val) == 1)
                {
                    inserir_elementos(arrayLista, nomeC, val);
                } 
            }
            
        }
         else if (let == 'r')
        {
            if(scanf("%d", &nomeC) == 1)
            {
                if(scanf("%d", &dump) == 1)
               while(scanf("%d", &val) == 1)
                {
                    remover(arrayLista, nomeC, val);
                } 
            }
            
        }
        else if(let == 'p') {
            if(scanf("%d", &nomeC) != 1) {
                continue;
            }
        
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    imprimir_lista(arrayLista, nomeC);
                    break;
                }
            }
        }
        else if(let == 'e') {
            if(scanf("%d %d", &nomeC, &val) != 2) {
                break;
            }
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    x_esta_em_c(arrayLista, nomeC, val);
                    break;
                }
            }
        }
        else if(let == 't') {
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL) {
                    libera(arrayLista[j]);
                    arrayLista[j] = NULL;
                }
            }
            return 1;
        }
        else if(let == 'u') {
            if(scanf("%d %d %d", &nomeC, &nomeC2, &nomeC3) != 3) {
                continue;
            }

            int conj2_existe = 0;
            int conj3_existe = 0;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL) {
                    if(arrayLista[j]->nome == nomeC2) conj2_existe = 1;
                    if(arrayLista[j]->nome == nomeC3) conj3_existe = 1;
                }
            }

            if(!conj2_existe || !conj3_existe) {
                continue;
            }

            int pos = -1;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1) {
                for(int j = 0; j < 127; j++) {
                    if(arrayLista[j] == NULL) {
                        pos = j;
                        break;
                    }
                }
            }

            if(pos != -1) {
                lista *resultado = uniao(arrayLista, nomeC, nomeC2, nomeC3);
                if(resultado != NULL) {
                    if(arrayLista[pos] != NULL) {
                        libera(arrayLista[pos]);
                    }
                    arrayLista[pos] = resultado;
                }
            }
        }

        else if(let == 'n') {
            if(scanf("%d %d %d", &nomeC, &nomeC2, &nomeC3) != 3) {
                continue;
            }

            int conj2_existe = 0;
            int conj3_existe = 0;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL) {
                    if(arrayLista[j]->nome == nomeC2) conj2_existe = 1;
                    if(arrayLista[j]->nome == nomeC3) conj3_existe = 1;
                }
            }

            if(!conj2_existe || !conj3_existe) {
                continue;
            }

            int pos = -1;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1) {
                for(int j = 0; j < 127; j++) {
                    if(arrayLista[j] == NULL) {
                        pos = j;
                        break;
                    }
                }
            }

            if(pos != -1) {
                lista *resultado = interseccao(arrayLista, nomeC, nomeC2, nomeC3);
                if(resultado != NULL) {
                    if(arrayLista[pos] != NULL) {
                        libera(arrayLista[pos]);
                    }
                    arrayLista[pos] = resultado;
                }
            }
        }

        else if(let == 'm') {
            if(scanf("%d %d %d", &nomeC, &nomeC2, &nomeC3) != 3) {
                continue;
            }

            int conj2_existe = 0;
            int conj3_existe = 0;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL) {
                    if(arrayLista[j]->nome == nomeC2) conj2_existe = 1;
                    if(arrayLista[j]->nome == nomeC3) conj3_existe = 1;
                }
            }

            if(!conj2_existe || !conj3_existe) {
                continue;
            }

            int pos = -1;
            for(int j = 0; j < 127; j++) {
                if(arrayLista[j] != NULL && arrayLista[j]->nome == nomeC) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1) {
                for(int j = 0; j < 127; j++) {
                    if(arrayLista[j] == NULL) {
                        pos = j;
                        break;
                    }
                }
            }

            if(pos != -1) {
                lista *resultado = diferenca(arrayLista, nomeC, nomeC2, nomeC3);
                if(resultado != NULL) {
                    if(arrayLista[pos] != NULL) {
                        libera(arrayLista[pos]);
                    }
                    arrayLista[pos] = resultado;
                }
            }
        }
    }
    for(int j = 0; j < 127; j++) {
        if(arrayLista[j] != NULL) {
            libera(arrayLista[j]);
            arrayLista[j] = NULL;
        }
    }
    
    return 0;
}
/*TODO:

-Comandos
-União não pode ter elementos repetidos X
-Interseção precisa garantir que não hajam elementos repetidos entrando no programa X
-Print em ordem crescente X

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
=======
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
>>>>>>> 7e3fe16996041694d3d76bf8f5ded5cb4ae11f27
