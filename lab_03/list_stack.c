#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define STACK_MAX_SIZE 20
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OK 0

typedef int T;




typedef struct Node_tag 
{
    T value;
    struct Node_tag *next;
} Node_t;


int push_list(Node_t **head, T value) 
{
    Node_t *tmp = malloc(sizeof(Node_t));
    if (tmp == NULL) 
        return STACK_OVERFLOW;
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
    return OK;
}

T pop_list(Node_t **head)
{
    Node_t *out;
    T value;
    if (*head == NULL)
        return STACK_UNDERFLOW;
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

int peek_list(const Node_t* head) 
{
    if (head == NULL) 
        return STACK_UNDERFLOW;
    else
        return head->value;
}


void printStack_list(const Node_t* head) 
{
    printf("stack >");
    while (head) 
    {
        printf("%d ", head->value);
        head = head->next;
    }
}


int getSize_list(const Node_t *head) 
{
    int size = 0;
    while (head) 
    {
        size++;
        head = head->next;
    }
    return size;
}
for (int i = 0; i < len; i++)
{
    if (middle == -1)
    {
        if (i < (int)(len/2))
            understack1[i] = pop_array(&stack);
        else if (i >= (int)(len/2))
        {
            understack2[k] = pop_array(&stack);
            k++;
        }
    }
    else
    {
        if (i < middle-1)
            understack1[i] = pop_array(&stack);
        else if (i == middle-1)
            pop_array(&stack);
        else if (i > middle - 1)
        {
            printf("%d\n",i);
            understack2[k] = pop_array(&stack);
            k++;
        }
    }
}