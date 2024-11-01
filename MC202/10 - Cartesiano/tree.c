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
    if ((*top + 1) % size == *top) {
        return 0;
    }
    q[*top].node_arvore = data;
    *top = (*top + 1) % size;
    return 1;
}

int dequeue(fila* q, int* bot, int size, int* top) {
    if (*bot == *top) { 
        return 0;
    }
    *bot = (*bot + 1) % size;
    return 1;
}

no* front(fila* q, int* bot) {
    return q[*bot].node_arvore;
}

int isEmpty(int* top, int* bot) {
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
    no* cabeca = criano(minIndex);  

    cabeca->left = arvorecartesiana(vector, esq, minIndex - 1);
    cabeca->right = arvorecartesiana(vector, minIndex + 1, dir);

    return cabeca;
}

void BFS(no* root, int size) {
    if (root == NULL) {
        return;
    }

    
    fila* q = create(size + 1);  
    int top = 0, bot = 0;

    queue(q, &top, root, size + 1);  

    while (!isEmpty(&top, &bot)) {
        int count = top - bot; 
        if (count < 0) {
            count += size + 1;
        }

       
        while (count > 0) {
            no* current = front(q, &bot);
            dequeue(q, &bot, size + 1, &top);

            printf("%d ", current->data); 

           
            if (current->left != NULL) {
                queue(q, &top, current->left, size + 1);
            }
            if (current->right != NULL) {
                queue(q, &top, current->right, size + 1);
            }

            count--;
        }

        printf("\n"); 
    }

    free(q);  
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

        BFS(tree->cabeca, val);
        printf("\n");

        libera(tree->cabeca);
        free(tree);
    }

    return 0;
}
