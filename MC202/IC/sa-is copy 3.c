//O objetivo é comparar um array de sufixos feito de forma ingênua O(nlogn) com
//o método SA-IS (suffix array induced sorting). Baseado em 

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
} node;

typedef struct bucket
{
    node* head;
}bucket;

bucket* createBucket()
{
    bucket* buck = malloc(sizeof(bucket));
    buck->head = NULL;
    return buck;
}
