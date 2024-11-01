/*
A pilha segue LIFO - Last In First Out (último a entrar é o primeiro a sair)

Possui as operações push (adiciona) pop (retira do topo) peek (visita) size (ta-
manho da pilha) e isEmpty (vazia/nao vazia)

Todas as operações são O(1)

*/
#include <stdio.h>
#include <stdlib.h>

int top = 0;

typedef struct pilha
{

char data;

}pilha;

pilha* create(int size)
{

pilha* stack = malloc(sizeof(pilha) * size);

return stack;

}
int isEmpty(pilha* stack)
{
if(top == 0)
{
    return 1;
}
else
{
    return 0;
}
}

int push(pilha* stack, char val, int size)
{

if(size == top)
{
    printf("Overflow.\n");
    return 0;
}

stack[top].data = val;
top++;

return 1;

}
int pop(pilha* stack)
{
if(isEmpty(stack))
{
    printf("Erro. Pilha vazia.\n");
    return 0;
}

top--;

return stack[top].data;

}

int peek(pilha* stack)
{

return stack[top - 1].data;

}

int size()
{

return top;

}

int printStack(pilha* stack)
{
printf("[");
for(int i = 0; i < top; i++)
{
    printf("%d", stack[i].data);

    if(i < top - 1)
    {
        printf(", ");
    }
}
printf("]\n");
}



int main()
{

}