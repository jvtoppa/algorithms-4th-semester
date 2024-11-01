#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int data;
    struct no* right;
    struct no* left;
} no;

typedef struct arvore {
    no* cabeca;
} arvore;

typedef struct fila {
    no* node_arvore;
} fila;

fila* create(int size) {
    fila* q = malloc(sizeof(fila) * size);
    return q;
}

int queue(fila* q, int* top, no* data, int size) {
    if ((*top + 1) % size == 0) {
        return 0;  // Fila cheia
    }
    q[*top].node_arvore = data;
    *top = (*top + 1) % size;
    return 1;
}

int dequeue(fila* q, int* bot, int size, int* top) {
    if (*bot == *top) {
        return 0;  // Fila vazia
    }
    *bot = (*bot + 1) % size;
    return 1;
}

no* front(fila* q, int* bot) {
    return q[*bot].node_arvore;
}

int isEmpty(fila* q, int* top, int* bot) {
    return *bot == *top;
}

int minimo(int vector[], int esq, int dir) {
    int minv = vector[esq];
    int index = esq;
    for (int i = esq + 1; i <= dir; i++) {
        if (vector[i] < minv) {
            minv = vector[i];
            index = i;
        }
    }
    return index;
}

arvore* criarvore() {
    arvore* tree = malloc(sizeof(arvore));
    if (tree == NULL) {
        return NULL;
    }
    tree->cabeca = NULL;
    return tree;
}

no* criano(int data) {
    no* novo = malloc(sizeof(no));
    if (novo == NULL) {
        return NULL;
    }
    novo->data = data;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

no* arvorecartesiana(int vector[], int esq, int dir) {
    if (esq > dir) {
        return NULL;
    }
    
    int minIndex = minimo(vector, esq, dir);
    no* cabeca = criano(vector[minIndex]);

    cabeca->left = arvorecartesiana(vector, esq, minIndex - 1);
    cabeca->right = arvorecartesiana(vector, minIndex + 1, dir);

    return cabeca;
}

void BFS(no* root) {
    if (root == NULL) {
        return;
    }
    
    int size = 100;  // Tamanho da fila (pode ajustar conforme necessário)
    fila* q = create(size);
    int top = 0, bot = 0;

    queue(q, &top, root, size);

    while (!isEmpty(q, &top, &bot)) {
        no* current = front(q, &bot);
        dequeue(q, &bot, size, &top);

        printf("%d ", current->data);

        if (current->left != NULL) {
            queue(q, &top, current->left, size);
        }
        if (current->right != NULL) {
            queue(q, &top, current->right, size);
        }
    }

    free(q);  // Liberar a fila após o uso
}

void libera(no* cabeca) {
    if (cabeca == NULL) {
        return;
    }
    libera(cabeca->left);
    libera(cabeca->right);
    free(cabeca);
}

int main() {
    int vector[1000000];
    int val, val2;

    while (1) {
        scanf("%d", &val);
        if (val == 0) {
            break;
        }

        for (int i = 0; i < val; i++) {
            scanf("%d", &val2);
            vector[i] = val2;
        }

        arvore* tree = criarvore();
        tree->cabeca = arvorecartesiana(vector, 0, val - 1);

        // Imprimir a BFS
        printf("BFS: ");
        BFS(tree->cabeca);
        printf("\n");

        libera(tree->cabeca);
        free(tree);
    }

    return 0;
}