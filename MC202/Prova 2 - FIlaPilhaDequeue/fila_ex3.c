/*
Considere uma fila F que, al ́em das opera ̧c ̃oes push e eject tamb ́em tem uma opera ̧c ̃ao jump,
que faz o elemento na posi ̧c ̃ao i da fila ser movido para a posi ̧c ̃ao i − k.
Compare a eficiˆencia de tempo para realizar uma opera ̧c ̃ao jump em F implementada de forma
circularizada em um vetor contra F implementada como uma lista encadeada.
*/

#include <stdlib.h>
//queue tem que ter size+1

typedef struct queue
{

    int data;
}queue;


int push(int* top, int* bottom, int data, queue* queue, int size)
{

if((*top + 1) % size == *bottom)
{
    return -1;
}

queue[*top].data = data;

*top = (*top + 1) % size;
return 1;
} //queue

int eject(int* top, int* bottom, int size)
{
    if(*top == *bottom)
    {
        return -1;
    }

*bottom = (*bottom + 1 ) % size;

}

int jump(int* top, int* bottom, queue* q, int size, int k, int i)
{

queue transpose = q[i];

for(int count = k; count < size; count++)
{
    q[count + 1] = q[count];
}


q[i - k] = transpose;


}