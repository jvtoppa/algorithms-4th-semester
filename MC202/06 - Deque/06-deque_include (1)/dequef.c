#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

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


dequef* deque = malloc(sizeof(dequef));
if (deque == NULL)
{
   return NULL;
}

deque->cap = capacity;
deque->size = 0;
deque->factor = factor;
deque->data =  malloc(capacity*sizeof(float));
if (deque->data == NULL)
{
   return NULL;
}

deque->first = 0;
deque->mincap = capacity;

return deque;
}
/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D->data);
   free(D);
}




/**
   The size of the deque.
**/
long df_size(dequef* D) {

return D->size;

}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) 
{
   
   if (D->size == D->cap) 
   {
      long int D_incr = D->cap * D->factor;
      
      if (D_incr < D->mincap) 
      {
            D_incr = D->mincap;
      }
      float* datan = realloc(D->data, sizeof(float) * D_incr);
      if (datan == NULL) {
         printf("Unable to resize.\n");
         return 0;
      }

      D->data = datan;
      D->cap = D_incr;
      }

   D->data[(D->first + D->size) % D->cap] = x;
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
float df_pop(dequef* D) {
    if (D->size == 0) 
    {
        return 0; 
    }

    long ulti = (D->first + D->size - 1) % D->cap;
    float removido = D->data[ulti];

    D->size--;

    if (D->size <= D->cap / (D->factor * D->factor)) 
    {
        long new_cap = D->cap / D->factor;

        if (new_cap < D->mincap) 
        {
            new_cap = D->mincap;
        }

        float* datan = realloc(D->data, sizeof(float) * new_cap);
        if (datan != NULL) 
        {
            D->data = datan;
            D->cap = new_cap;
        }
    }

    return removido;
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
        long new_cap = D->cap * D->factor;

        float* datan = realloc(D->data, sizeof(float) * new_cap);
        if (datan == NULL) 
        {
            printf("Unable to resize.\n");
            return 0;
        }

        D->data = datan;
        D->cap = new_cap;
        D->first = (D->first + D->cap - 1) % D->cap;
    }

    D->data[D->first] = x;
    D->first = (D->first + D->cap - 1) % D->cap; 
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

    float removido = D->data[D->first];
    D->first = (D->first + 1) % D->cap;
    D->size--;

    if (D->size <= D->cap / (D->factor * D->factor)) 
    {
        long new_cap = D->cap / D->factor;

        if (new_cap < D->mincap) 
        {
            new_cap = D->mincap;
        }

        float* datan = realloc(D->data, sizeof(float) * new_cap);
        if (datan != NULL) 
        {
            D->data = datan;
            D->cap = new_cap;
        }
    }

    return removido;


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
void df_set(dequef* D, long i, float x) {
if (i < 0 || i >= D->size) 
{
    return; 
}

D->data[(D->first + i) % D->cap] = x;
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
if (D->size == 0) 
   {
      printf("\n");
      return;
   }

   for (long i = 0; i < D->size; i++) 
   {
      printf("%.1f", D->data[(D->first + i) % D->cap]);
      if (i < D->size - 1) 
      {
         printf(" ");
      }
   }
   printf("\n");
}
