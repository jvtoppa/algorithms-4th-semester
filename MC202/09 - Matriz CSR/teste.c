#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coordenadas {
    int i;
    int j;
    int val;
} coordenadas;

/* Debug */
void print_coords(coordenadas coords) {
    printf("i = %d\n", coords.i);
    printf("j = %d\n", coords.j);
    printf("x = %d\n\n", coords.val);
}

/* Para qsort */
int compare(const void* a, const void* b) {
    coordenadas* c1 = (coordenadas*) a;
    coordenadas* c2 = (coordenadas*) b;

    if (c1->i < c2->i) {
        return -1;
    } else if (c1->i > c2->i) {
        return 1;
    } else {
        if (c1->j < c2->j) {
            return -1;
        } else if (c1->j > c2->j) {
            return 1;
        } else {
            return 0;
        }
    }
}

int main(void) {
    int elems_matriz = 0;
    int maior_i = 0;
    int maior_j = 0;

    /* Leitura do número de elementos */
    scanf("%d", &elems_matriz);
    getchar();

    /* Alocação de memória para as coordenadas */
    coordenadas* vet = malloc(sizeof(coordenadas) * elems_matriz);

    /* Leitura das coordenadas */
    for (int j = 0; j < elems_matriz; j++) {
        int pos1 = 0;
        int pos2 = 0;
        int val = 0;
        scanf("%d %d %d", &pos1, &pos2, &val);
        getchar();

        vet[j].i = pos1;
        vet[j].j = pos2;
        vet[j].val = val;

        /* Atualizando o maior valor de i e j */
        if (vet[j].i > maior_i) {
            maior_i = vet[j].i;
        }
        if (vet[j].j > maior_j) {
            maior_j = vet[j].j;
        }
    }

    /* Ordenando as coordenadas */
    qsort(vet, elems_matriz, sizeof(coordenadas), compare);

    /* Vetores CSR */
    int A[elems_matriz];         // Valores
    int C[elems_matriz];         // Colunas
    int R[maior_i + 2];          // Pontos de início das linhas

    /* Inicializando o vetor R[] */
    for (int i = 0; i <= maior_i + 1; i++) {
        R[i] = 0;
    }

    /* Populando A[], C[], e contando as entradas para R[] */
    for (int i = 0; i < elems_matriz; i++) {
        A[i] = vet[i].val;
        C[i] = vet[i].j;
        R[vet[i].i + 1]++;
    }

    /* Construção cumulativa do vetor R[] */
    for (int k = 1; k <= maior_i + 1; k++) {
        R[k] += R[k - 1];
    }

    /* Impressão das coordenadas (debug) */
    for (int j = 0; j < elems_matriz; j++) {
        print_coords(vet[j]);
    }

    /* Impressão do vetor R[] */
    printf("\nR = ");
    for (int j = 0; j <= maior_i + 1; j++) {
        printf("%d, ", R[j]);
    }
    printf("\n");

    /* Liberação de memória */
    free(vet);
    return 1;
}