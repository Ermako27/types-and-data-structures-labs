#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
//#include "array_stack.h"

#define STACK_MAX_SIZE 20
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OK 0
#define N 5
#define TRUE 1

typedef char T;

typedef struct Stack_tag_array 
{
    T data[STACK_MAX_SIZE];
    int size_array;
} Stack_t;

typedef struct Node_tag {
    T value;
    struct Node_tag *next;
} Node_t;

unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}





void push_list(Node_t **head, T value) 
{
    Node_t *tmp = malloc(sizeof(Node_t));
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}


T pop_list(Node_t **head) 
{
    Node_t *out;
    T value;
    if (*head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}


T peek_list(const Node_t* head) 
{
    if (head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}


void printStack_list(const Node_t* head) 
{
    printf("stack >");
    while (head) {
        printf("\n%c ", head->value);
        printf("%p \n", &(head->value));
        head = head->next;
    }
}



int getSize_list(const Node_t *head) 
{

    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

int read_stack_list(Node_t **head)
{
    char ch;
    int error = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (error == STACK_MAX_SIZE)
            return STACK_OVERFLOW;  
        push_list(head, ch);
        error++;
    }
    return error;  
}




int main(void)
{
    unsigned long long tmp, tb, te;
    int len;
    int middle = -1;
    int k = 0;
    int overflow;
    int memmory;

    Node_t *head = NULL;
    char understack1[30];
    char understack2[30];
    char enter;
    char ch;

    printf("Input ur string: "); // чтение в стек
   // enter = getchar();
    overflow = read_stack_list(&head);

    printStack_list(head);

    tb = tick();

    if (overflow == STACK_OVERFLOW)
    {
        printf("Stack overflow!\n\n");
       // empty_st();
        return 0;
    }

    len = getSize_list(head);
    memmory = len*sizeof(head);
    if ((int)(len%2) != 0)
    {
        middle = len - ((len - 1) / 2);
    }
    for (int i = 0; i < len; i++)
    {
        if (middle == -1)
        {
            if (i < (int)(len/2))
                understack1[i] = pop_list(&head);
            else if (i >= (int)(len/2))
            {
                understack2[k] = pop_list(&head);
                k++;
            }
        }
        else
        {
            if (i < middle-1)
                understack1[i] = pop_list(&head);
            else if (i == middle-1)
                ch = pop_list(&head);
            else if (i > middle - 1)
            {
                understack2[k] = pop_list(&head);
                k++;
            }
        }
    }
    int flag = 0;
    int under_stak_len;
    if (len%2 == 0)
        under_stak_len = len/2;
    else
        under_stak_len = (len-1)/2;
    for (int i = 0; i < under_stak_len; i++)
    {
        if (understack1[i] != understack2[under_stak_len-1-i])
        {
            flag = 1;
            break;
        }
    }
    te = tick();

    if (flag == 0)
         printf("Result: String is a palindrome!\n");
    else
    {
        printf("Result: string is not a palindrome");
        printf("%c\n",enter);
    }
    printf("|------------------------------------------|\n");
    printf("|       TIME        |       MEMMORY        |\n");
    printf("|------------------------------------------|\n");
    printf("|       %llu         |         %d          |\n", (te - tb) / N, memmory);
    printf("|------------------------------------------|\n");

    return 0;
}