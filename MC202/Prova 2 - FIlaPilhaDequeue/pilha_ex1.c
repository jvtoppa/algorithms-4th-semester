/*
A pilha segue LIFO - Last In First Out (último a entrar é o primeiro a sair)

Possui as operações push (adiciona) pop (retira do topo) peek (visita) size (ta-
manho da pilha) e isEmpty (vazia/nao vazia)

Todas as operações são O(1)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    return -1;
}

top--;

return stack[top].data;

}

int match(char open, char close)
{
    if(open == '(' && close == ')')
    {
        return 1;
    }
    if(open == '[' && close == ']')
    {
        return 1;
    }
    if(open == '{' && close == '}')
    {
        return 1;
    }
    return 0;
}

int main()
{
int size = 500;
char cadeia[size];
int isemp = 0;
int fl = 0;
pilha* stack = create(size);
while(1)
{
scanf("%s", cadeia);
if(strcmp(cadeia,"exit") == 0)
{
    break;
}
getchar();


for(int i = 0;i < strlen(cadeia); i++)
{
    if(cadeia[i] == '(' )
    {
        push(stack, '(', size);
    }
    else if(cadeia[i] == '[')
    {
        push(stack, '[', size);
    }
    else if(cadeia[i] == '{')
    {
        push(stack, '{', size);
    }

    if(cadeia[i] == ')' )
    {
        isemp = pop(stack);
        if(isemp == -1 || !match(isemp, cadeia[i]))
        {
            printf("Cadeia mal formada.\n");
            fl = -1;
            break;
        }
    }
    else if(cadeia[i] == ']')
    {
        isemp = pop(stack);
        if(isemp == -1 || !match(isemp, cadeia[i]))
        {
            printf("Cadeia mal formada.\n");
            fl = -1;
            break;
        }
    }
    else if(cadeia[i] == '}')
    {
        isemp = pop(stack);
        if(isemp == -1 || !match(isemp, cadeia[i]))
        {
            printf("Cadeia mal formada.\n");
            fl = -1;
            break;
        }
    }
}

if(isemp != -1 && top == 0 && fl != -1)
{
    printf("Cadeia bem formada.\n");
}
else if(fl != -1)
{
    printf("Cadeia mal formada.\n");
}


fl = 0;
}
free(stack);
}
