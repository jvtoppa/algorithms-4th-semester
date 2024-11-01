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

int findMin(int vector[], int esq, int dir) {
    int minIndex = esq;
    for (int i = esq + 1; i <= dir; i++) {
        if (vector[i] < vector[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

arvore* createTree() {
    arvore* tree = malloc(sizeof(arvore));
    if (tree == NULL) {
        return NULL;
    }
    tree->cabeca = NULL;
    return tree;
}

no* criar(int data) {
    no* novo = malloc(sizeof(no));
    if (novo == NULL) {
        return NULL;
    }
    novo->data = data;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

no* cartesianTree(int vector[], int esq, int dir) { //mergeSort ;)
    if (esq > dir) {
        return NULL; 
    }
    int minIndex = findMin(vector, esq, dir);
    no* cabeca = criar(minIndex);


    cabeca->left = cartesianTree(vector, esq, minIndex - 1);
    cabeca->right = cartesianTree(vector, minIndex + 1, dir);
    return cabeca;
}

int altura(no* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = altura(root->left);
    int right_height = altura(root->right);
    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
}

void printNivel(no* root, int nivel, int vector[]) {
    if (root == NULL) {
        return;
    }
    if (nivel == 1) {
        printf("%d ", root->data);
    } else if (nivel > 1) {
        printNivel(root->left, nivel - 1, vector);
        printNivel(root->right, nivel - 1, vector);
    }
}

void bfsRecursivo(no* root, int vector[]) {
    int h = altura(root);
    for (int i = 1; i <= h; i++) {
        printNivel(root, i, vector);
        printf("\n");
    }
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

        arvore* tree = createTree();
        tree->cabeca = cartesianTree(vector, 0, val - 1);
        bfsRecursivo(tree->cabeca, vector);
        printf("\n");
        libera(tree->cabeca);
        free(tree);
    }

    return 0;
}