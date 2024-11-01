#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "dequef.h"

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) 
{

    dequef* D = malloc(sizeof(dequef));
    
    if (!D) {

        return NULL;

    }

    if (capacity > LONG_MAX / sizeof(float)) {

        return NULL;

    }

    D->data = malloc(sizeof(float) * capacity);

    if (!D->data) 
    {

        free(D);
        return NULL;
    
    }

    D->first = 0;
    D->size = 0;
    D->cap = capacity;
    D->mincap = capacity;
    D->factor = factor;

    return D;
}

/**
  Release a dequef and its data.
**/

void df_free(dequef* D) 
{

    if (D) {

        free(D->data);
        free(D);

    }
}


/**
   The size of the deque.
**/
long df_size(dequef* D) 
{
    return D->size;

}

/**
Função Auxiliar: cria um novo vetor de capacidade dada pela função e substitui data na deque
**/
int df_resize(dequef* D, long capacidaden) 
{
    if (D == NULL || capacidaden < D->mincap)
    {
        return 0;
    }
    

    float* dadosn = malloc(capacidaden * sizeof(float));

    if (dadosn == NULL) //malloc falha 
    {
        return 0;
    }

    for (long i = 0; i < D->size; i++) 
    {
        
        dadosn[i] = D->data[(D->first + i) % D->cap];
    
    }

    free(D->data);
    D->data = dadosn;
    D->first = 0;
    D->cap = capacidaden;

    return 1;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
    if (D->size == D->cap) 
    {
        long novacap = D->cap * D->factor;

        if (!df_resize(D, novacap)) 
        {
            printf("Unable to resize.\n");
            return 0;
        }
    }

    long id = (D->first + D->size) % D->cap;

    D->data[id] = x;
    
    D->size++;
    
    return 1;
}

/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_pop(dequef* D) 
{
    if (D == NULL) 
    {

        return 0;
    }

    long id = (D->first + D->size - 1) % D->cap;

    float val = D->data[id];

    D->size--;

    if (D->size < D->cap / (D->factor * D->factor)) 
    {
        
        long capacidaden = D->cap / D->factor;
        
        if (!df_resize(D, capacidaden)) {
        
            return val;
        
        }
    }

    return val;
}

/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
    
    if (D->size == D->cap) 
    {

        long novacap = (long)(D->cap * D->factor);

        if (!df_resize(D, novacap)) 
        {
            
            printf("Unable to resize.\n");
            
            return 0;
        }
    }

    D->first = (D->first - 1 + D->cap) % D->cap;
    D->data[D->first] = x;
    D->size++;
    return 1;
}

/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_eject(dequef* D) {
    if (D->size == 0)
    {

        return 0;
    
    } 

    float val = D->data[D->first];
    D->first = (D->first + 1) % D->cap;
    D->size--;

    if (D->size < D->cap / (D->factor * D->factor)) 
    {

        long novacap = (long)(D->cap / D->factor);
    
    }

    return val;
}

/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef* D, long i) {
    if (i < 0 || i >= D->size)
    {

        return 0;
    
    }

    return D->data[(D->first + i) % D->cap];
}

/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef* D, long i, float x) 
{

    if (D == NULL || i < 0 || i >= D->size)
    {
        return;
    }

    long ri = (D->first + i) % D->cap;
    
    D->data[ri] = x;

}

/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
    
    printf("deque (%ld):", D->size);
    
    for (long i = 0; i < D->size; i++)
    {

        printf(" ");
        printf("%.1f", D->data[(D->first + i) % D->cap]);

    }
    printf("\n");
}
