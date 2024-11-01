#include <stdio.h>
#include <stdlib.h>

typedef struct  coordenadas
{

int i;
int j;
int val;

}coordenadas;

/*Debug.
void print_coords(coordenadas coords)
{
    printf("i = ");
    printf("%d ", coords.i);
    printf("\n");
    printf("j = ");
    printf("%d ",coords.j);
    printf("\n");
    printf("x = ");
    printf("%d ",coords.val);
    printf("\n\n");
}
*/
/*Para qsort*/
int compare(const void* a, const void* b)
{
    coordenadas* c1 = (coordenadas*) a;
    coordenadas* c2 = (coordenadas*) b;

    if (c1->i < c2->i)
    {
            return -1;
    }
    else if (c1->i > c2-> i)
    {
        return 1;
    }
    else
    {
        if (c1->j == c2->j)
        {
            return 0;
        }
        else if (c1->j > c2->j)
        {
            return 1;
        }
        else{
            return -1;
        }
    }

}

int recuperar(int A[], int C[], int R[], int inputx, int inputy)
{
    
if(R[inputx] == R[inputx + 1])
    {
        return 0;
    }
else
    {
    for (int idx = R[inputx]; idx <= R[inputx + 1] - 1; idx++)
        {
            if (C[idx] == inputy)
            {
                return A[idx];
            }
        }
        
    }

return 0;

}   
int main(void)
{
int elems_matriz = 0;
int maior_i = 0;
int maior_j = 0;
int x = 0;
int y = 0;

 if (scanf("%d", &elems_matriz) != 1 || elems_matriz <= 0) {
        return 1;
    }


coordenadas* vet = malloc(sizeof(coordenadas) * elems_matriz);
if(vet == NULL)
{
    return 1;
}


for(int j = 0; j < elems_matriz; j++)
{
    int pos1 = 0;
    int pos2 = 0;
    int val = 0;
    scanf("%d %d %d", &pos1, &pos2, &val);

    if(pos1 < 0 && pos2 < 0)
    {
        return 0;
    }



    vet[j].i = pos1;
    vet[j].j = pos2;
    vet[j].val = val;

    if(vet[j].i >maior_i)
    {
        maior_i = vet[j].i;
    }
    if(vet[j].j > maior_j)
    {
        maior_j = vet[j].j;
    }
    

}

qsort (vet, elems_matriz, sizeof(coordenadas), compare);

int A[elems_matriz];
int C[elems_matriz];
int R[maior_i + 2];
for (int i = 0; i <= maior_i + 1; i++) {
    R[i] = 0;
}
for(int i = 0; i < elems_matriz; i++)
{
    A[i] = vet[i].val;
    C[i] = vet[i].j;
    R[vet[i].i + 1] = R[vet[i].i + 1] + 1;
}

for(int k = 1; k <= maior_i + 1; k++)
{
    R[k] += R[k - 1 ];
}

while(1)
{
scanf("%d %d", &x, &y);
if(x == -1 && y == -1)
{
    break;
}
else if(x < 0 || y < 0)
{
    continue;
}

int rec = recuperar(A, C, R, x, y);

printf("(%d,%d) = %d\n", x, y, rec);
}

free(vet);
return 1;
}