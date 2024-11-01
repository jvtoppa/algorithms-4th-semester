#include <stdlib.h>
#include <string.h>

typedef struct stack
{    
    char character;

}stack;

stack* createStack(int size)
{
    stack* stk = malloc(sizeof(stack)*size);

    return stk;
}

int push(char c, int* top, stack* stk, int size)
{
if(*top == size)
{
    return 0;
}


stk[*top].character = c;
(*top)++;

return 1;
}

int pop(int* top, stack* stk)
{
if(*top == 0)
{
    return 0;
}

(*top)--;

}
stack* backspace(stack** s, int size, int* top)
{
for(int i = 0; i < size; i++)
{

if(s[i]->character != '#')
{
    push(s[i]->character, top, s, size);    
}
else
{
    pop(top, s[i]->character);
}

}
return s;
}

/*

Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.
Note that after backspacing an empty text, the text will continue empty.

*/

bool backspaceCompare(char* s, char* t) 
{

int s_size = strlen(s);
int t_size = strlen(t);
int top = 0;
int top2 = 0;

stack* s_stack = createStack(s_size);
stack* t_stack = createStack(t_size);

stack* s_treated = backspace(s_stack, s_size, top);
stack* t_treated = backspace(t_stack, t_size, top2);

if(s_treated == t_treated)
{
    return true;
}
return false;

}