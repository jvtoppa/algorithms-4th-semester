#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    double val;
    struct no* prox;
} no;

typedef struct lista {
    int tamanho;
    no* start;
} lista;

lista* criar_lista(void) {
    lista* L = malloc(sizeof(lista));
    if(L == NULL) {
        return NULL;
    }
    L->tamanho = 0;
    L->start = NULL;
    return L;
}

int inserir(lista* L, double val, int posicao) {
    if (L == NULL || posicao < 0) {
        return 0;
    }

    no* novo = malloc(sizeof(no));
    if(!novo) {
        return 0;
    }

    novo->val = val;
    novo->prox = NULL;

    if (posicao == 0 || L->start == NULL) {
        novo->prox = L->start;
        L->start = novo;
    } else {
        no* atual = L->start;
        int i;
        for (i = 0; i < posicao - 1 && atual->prox != NULL; i++) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    L->tamanho++;
    return 1;
}

int remover(lista* L, int pos) {
    if (L == NULL || L->start == NULL || pos < 0 || pos >= L->tamanho) {
        return 0;
    }

    no* removido;
    if (pos == 0) {
        removido = L->start;
        L->start = removido->prox;
    } else {
        no* atual = L->start;
        for (int i = 0; i < pos - 1; i++) {
            atual = atual->prox;
        }
        removido = atual->prox;
        atual->prox = removido->prox;
    }

    free(removido);
    L->tamanho--;
    return 1;
}

int reverte(lista* L, int pos1, int pos2) {
    if (L == NULL || pos1 < 0 || pos2 >= L->tamanho || pos1 >= pos2) {
        return 0;
    }

    no dummy;
    dummy.prox = L->start;
    no* prev = &dummy;

    for (int i = 0; i < pos1; i++) {
        prev = prev->prox;
    }

    no* start = prev->prox;
    no* then = start->prox;

    for (int i = 0; i < pos2 - pos1; i++) {
        start->prox = then->prox;
        then->prox = prev->prox;
        prev->prox = then;
        then = start->prox;
    }

    L->start = dummy.prox;
    return 1;
}

int move(lista* L, int pos1, int pos2, int pos3) {
    if (L == NULL || pos1 < 0 || pos2 < pos1 || pos2 >= L->tamanho || pos3 < 0 || pos3 > L->tamanho) {
        return 0;
    }

    // Se a posição de destino está dentro do intervalo a ser movido, não fazemos nada
    if (pos3 > pos1 && pos3 <= pos2 + 1) {
        return 1;
    }

    no dummy;
    dummy.prox = L->start;
    no* prev_start = &dummy;

    // Encontrar o nó anterior ao início do segmento a ser movido
    for (int i = 0; i < pos1; i++) {
        prev_start = prev_start->prox;
    }

    // Encontrar o último nó do segmento a ser movido
    no* end = prev_start->prox;
    for (int i = pos1; i < pos2; i++) {
        end = end->prox;
    }

    // Remover o segmento da posição original
    no* start = prev_start->prox;
    prev_start->prox = end->prox;

    // Encontrar a nova posição para inserção
    no* prev_insert = &dummy;
    if (pos3 > pos2) {
        pos3 -= (pos2 - pos1 + 1);
    }
    for (int i = 0; i < pos3; i++) {
        prev_insert = prev_insert->prox;
    }

    // Inserir o segmento na nova posição
    end->prox = prev_insert->prox;
    prev_insert->prox = start;

    L->start = dummy.prox;
    return 1;
}

void imprimir(lista* L) {
    if (L == NULL) return;
    for (no* p = L->start; p != NULL; p = p->prox) {
        printf("%.2f ", p->val);
    }
    printf("\n");
}

int libera(lista* L) {
    if (L == NULL) return 0;
    no* atual = L->start;
    while (atual != NULL) {
        no* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(L);
    return 1;
}

int main(void) {
    lista* lst = NULL;

    while (1) {
        char let;
        if (scanf(" %c", &let) != 1) break;

        switch (let) {
            case 'c':
                if (lst != NULL) libera(lst);
                lst = criar_lista();
                break;
            case 'p':
                if (lst != NULL) imprimir(lst);
                break;
            case 'i': {
                int pos;
                double val;
                if (scanf("%d %lf", &pos, &val) == 2 && lst != NULL) {
                    inserir(lst, val, pos);
                }
                break;
            }
            case 'r': {
                int pos;
                if (scanf("%d", &pos) == 1 && lst != NULL) {
                    remover(lst, pos);
                }
                break;
            }
            case 'v': {
                int pos1, pos2;
                if (scanf("%d %d", &pos1, &pos2) == 2 && lst != NULL) {
                    reverte(lst, pos1, pos2);
                }
                break;
            }
            case 'x': {
                int pos1, pos2, pos3;
                if (scanf("%d %d %d", &pos1, &pos2, &pos3) == 3 && lst != NULL) {
                    move(lst, pos1, pos2, pos3);
                }
                break;
            }
            case 't':
                if (lst != NULL) {
                    libera(lst);
                    return 0;
                }
                break;
        }
    }

    if (lst != NULL) {
        libera(lst);
    }
    return 0;
}