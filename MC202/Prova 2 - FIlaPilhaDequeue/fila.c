/*
FIFO - First in, First out.
Possui as operações Queue, Dequeue, Peek, Rear, isFull, isEmpty, size.

Todas as operações são O(1).



*/

#include <stdio.h>
#include <stdlib.h>

typedef struct fila
{

int data;

}fila;


fila* create(int size)
{

fila* q = malloc(sizeof(fila)*size);

return q;
}

int queue(fila* q, int* top, int data, int size)
{
if(*top == size)
{
    printf("Overflow!\n");
    return 0;
}
q[*top].data = data;
*top = (*top + 1) % size;

return 1;

}
int dequeue(fila* q, int* bot, int size, int* top)
{
if(*bot == *top)
{
    printf("Underflow!\n");
    return 0;
}

*bot = (*bot + 1) % size;

return q[*bot - 1].data;

}
int front(fila* q, int* bot)
{
    return q[*bot].data;
}
int rear(fila* q, int* top)
{
    return q[*top].data;
}
int isFull(fila* q, int* top, int* bot, int size)
{
    return ((*top + 1) % size == *bot);
}
int isEmpty(fila* q, int* top, int* bot)
{
    return *bot == *top;
}
int size(fila* q)
{

}
void printQ(fila* q)
{
    
}

int main()
{


}