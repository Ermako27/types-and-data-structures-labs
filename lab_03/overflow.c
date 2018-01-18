#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define STACK_MAX_SIZE 5
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OK 0
#define N 5
#define TRUE 1

typedef char T;

typedef struct Node_tag {
    T value;
    struct Node_tag *next;
} Node_t;


// int push_list(Node_t **head, T value, Node_t *end_of_stack) 
// {
//     //printf("end in push: %p\n", end_of_stack);
//     Node_t *tmp = malloc(sizeof(Node_t));
//     printf("head: %p  tmp: %p     end in push: %p\n", head, tmp+2*sizeof(Node_t), end_of_stack);
//     if (tmp+2*sizeof(Node_t) >= end_of_stack)
//         return STACK_OVERFLOW;
//     tmp->next = *head;
//     tmp->value = value;
//     *head = tmp;
//     return OK;
// }

void push_list(Node_t **head, T value) 
{
    Node_t *tmp = malloc(sizeof(Node_t));
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
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
    return OK;  
}

void printStack_list(const Node_t* head) 
{
    printf("stack >");
    while (head) {
        printf("%c ", head->value);
        head = head->next;
    }
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

int main(void)
{
    Node_t *point = malloc(7*sizeof(Node_t));
    Node_t *head = NULL;
 

    printf("start: %p\n", point);
    printf("end: %p\n", point+5*sizeof(Node_t));
    int error;
    // for (int i = 0; i < 10; i++)
    // {
    //     error = push_list(&head, i, point+7*sizeof(Node_t));
    //     if (error == STACK_OVERFLOW)
    //     {
    //         printf("OVERFLOW");
    //         break;
    //     }
    // }

    printf("Input string: ");
    error = read_stack_list(&head);
    if (error == STACK_OVERFLOW)
    {
        printf("OVERFLOW");
    }


    printStack_list(head);
    printf("\n");


    char element = pop_list(&head);
    printf("element: %c\n", element);

    printStack_list(head);
    printf("\n");
    return 0;

}