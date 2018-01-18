/*
Вариант 10 группа 34, условие задачи приведено в соответствующем файле по варианту.

Лаба выполнена аккуратно, насколько я мог выполнить ее аккуратно на тот момент все тесты проходят.
Проблемы возникали в следующем:
1. Организация меню с помощью бесконченого цикла - после нажатия того или иного пункта меню совместно с самой командой вводился и символ перевода строки "\n", посдедующие команды принимали этот символ на ввод и программа расценивала это как некорректный ввод. Решение - getchar() в переменную, которая съедала этот \n и позволяла пользователю вводить команды после выбора определенного пункта в меню.

2. По каким-то причинам программа не захотела собираться из make файла, точнее она собиралась, но программа работала неопределенным способом - через раз программа падала с segmentation fault. Потому пришлось опять таки собрать все в один файл, но это были вынужденные меры(очень хотелось сдать раньше так как программа работает очень хорошо).

Файлы test*.c - файлы, в которых тестируются различные идеи и пробуются разные механники

Подробный отчет в wiki

*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
//#include "array_stack.h"

#define STACK_MAX_SIZE 10
#define STACK_MAX_SIZE_LIST 10
#define STACK_MAX_SIZE_TEST 500
#define STACK_MAX_SIZE_LIST_TEST 500
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

typedef struct Stack_tag_array_free
{
    T* data[STACK_MAX_SIZE];
    int size_array;
} Stack_t_free;

typedef struct Node_tag {
    T value;
    struct Node_tag *next;
} Node_t;


typedef struct Stack_tag_array_test
{
    T data[STACK_MAX_SIZE_TEST];
    int size_array;
} Stack_t_test;







unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}

 
int push_array(Stack_t *stack,const T value) 
{
    if (stack->size_array > STACK_MAX_SIZE)
        return STACK_OVERFLOW;
    stack->data[stack->size_array] = value;
    stack->size_array++;
    return OK;
}

int push_array_free(Stack_t_free *stack, T* value) 
{
    if (stack->size_array > STACK_MAX_SIZE)
        return STACK_OVERFLOW;
    stack->data[stack->size_array] = value;
    stack->size_array++;
    return OK;
}

int push_array_test(Stack_t_test *stack, const T value) 
{
    if (stack->size_array > STACK_MAX_SIZE)
        return STACK_OVERFLOW;
    stack->data[stack->size_array] = value;
    stack->size_array++;
    return OK;
}

int read_stack_array(Stack_t *stack)
{
    char ch;
    int error;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        error = push_array(stack,ch);
        if (error != OK)
            return STACK_OVERFLOW;   
    }
    return OK;
}

void printStackValue(const T value) 
{
    printf("%c", value);
}
 
void printStack_array(const Stack_t *stack) 
{
    int i;
    int len = stack->size_array - 1;
    printf("Stack >\n");
    printf("---------------------------------------------\n");
    printf("|        VALUE      |         ADRESS        |\n");
    printf("---------------------------------------------\n");
    for (i = 0; i < len; i++) 
    {
        printf("|         %c         |    %p     |\n", stack->data[i],&(stack->data[i]));
        printf("---------------------------------------------\n");
    }
    if (stack->size_array != 0) 
    {
        printf("|         %c         |    %p     |\n", stack->data[i],&(stack->data[i]));
        printf("---------------------------------------------\n");
    }
    printf("\n");
}


void printStack_array_free(Stack_t_free *stack) 
{
    int i;
    int len = stack->size_array - 1;
    printf("Stack >\n");
    printf("-------------------------\n");
    printf("|         ADRESS        |\n");
    printf("-------------------------\n");
    for (i = 0; i < len; i++) 
    {
        printf("|        %p         |\n",stack->data[i]);
        printf("---------------------\n");
    }
    if (stack->size_array != 0) 
    {
        printf("|       %p      |\n",stack->data[i]);
        printf("---------------------\n");
    }
    printf("\n");
}

T pop_array(Stack_t *stack) {
    if (stack->size_array == 0)
        return STACK_UNDERFLOW;
    stack->size_array--;
    //printf("VALUEEEEEE: %p\n", &(stack->data[stack->size_array]));
    return stack->data[stack->size_array];
}

void pop_array_free(Stack_t_free *stack) {
    //if (stack->size_array == 0)
    //    return STACK_UNDERFLOW;
    stack->size_array--;
    //printf("VALUEEEEEE: %p\n", &(stack->data[stack->size_array]));
    //return stack->data[stack->size_array];
}

T pop_array_test(Stack_t_test *stack) {
    if (stack->size_array == 0)
        return STACK_UNDERFLOW;
    stack->size_array--;
    //printf("VALUEEEEEE: %p\n", &(stack->data[stack->size_array]));
    return stack->data[stack->size_array];
}

void empty_st(void)
{
    char ch;
    while (ch = getchar() != '\n')
    {
        int *tmp = NULL; 
    }
}


int palindrome_check_array(void)
{
    unsigned long long tmp, tb, te;
    int len;
    int middle = -1;
    int k = 0;
    int overflow;
    int memmory;

    Stack_t stack_array; // стэк
    stack_array.size_array = 0;
    char understack1[30];
    char understack2[30];
    char enter;
    char ch;

    printf("Input ur string: "); // чтение в стек
    enter = getchar();
    overflow = read_stack_array(&stack_array);

    tb = tick();

    if (overflow != OK)
    {
        printf("Stack overflow!\n\n");
        empty_st();
        return 0;
    }

    len = stack_array.size_array;
    memmory = len*sizeof(stack_array);
    if ((int)(len%2) != 0)
    {
        middle = len - ((len - 1) / 2);
    }
    for (int i = 0; i < len; i++)
    {
        if (middle == -1)
        {
            if (i < (int)(len/2))
                understack1[i] = pop_array(&stack_array);
            else if (i >= (int)(len/2))
            {
                understack2[k] = pop_array(&stack_array);
                k++;
            }
        }
        else
        {
            if (i < middle-1)
                understack1[i] = pop_array(&stack_array);
            else if (i == middle-1)
                ch = pop_array(&stack_array);
            else if (i > middle - 1)
            {
                understack2[k] = pop_array(&stack_array);
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



void peek_ar(const Stack_t *stack) {

    printf("   %p  |\n", &(stack->data[stack->size_array - 1]));
}

T peek_ar_1(const Stack_t *stack) {

    return stack->data[stack->size_array - 1];
}

// void free_memmory(const Stack_t *stack)
// {
//    // int count = 10 - stack->size_array;

//     for (int i = stack->size_array; i < 10; i++)
//     {
//         printf("   %p  |\n", &(stack->data[stack->size_array - 1]) + sizeof(Stack_t)*i);

//     }
// }

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////






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
    if (*head == NULL)
        return STACK_UNDERFLOW;
    out = *head;
    *head = (*head)->next;
    value = out->value;
   // printf("VALUEEEEEE %p\n", &(out->value));
    free(out);
    return value;
}

T pop_list_free(Node_t **head, Stack_t_free *stack) 
{
    Node_t *out;
    T value;
    T* value_p;
    if (*head == NULL)
        return STACK_UNDERFLOW;
    out = *head;
    *head = (*head)->next;
    value = out->value;
    value_p = &(out->value);
   // printf("\nfree adress: %p\n", value_p);
    push_array_free(stack, value_p);
   // printf("VALUEEEEEE %p\n", &(out->value));
    free(out);
    return value;
}




void peek_list(const Node_t* head) 
{

    printf("        %p      |\n", &(head->value));
}



T peek_list_1(const Node_t* head) 
{

    return head->value;
}




void printStack_list(const Node_t* head) 
{
    printf("stack >\n");
    printf("-----------------------------------------\n");
    printf("|        VALUE      |       ADRESS      |\n");
    printf("-----------------------------------------\n");
    while (head) {
        printf("|         %c         |      %p    |\n", head->value,&(head->value));
        printf("-----------------------------------------\n");
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
        if (error > STACK_MAX_SIZE)
            return STACK_OVERFLOW;  
        push_list(head, ch);
        error++;
    }
    return error;  
}




int palindrome_check_list(void)
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
    enter = getchar();
    overflow = read_stack_list(&head);

    tb = tick();

    if (overflow == STACK_OVERFLOW)
    {
        printf("Stack overflow!\n\n");
        empty_st();
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




int main(void)
{
    
    Stack_t stack;
    Stack_t_free stack_free;
    Stack_t_test test_m;
    stack.size_array = 0;
    test_m.size_array = 0;
    stack_free.size_array = 0;
    Node_t *head = NULL;   
    int menu = TRUE;
    int count_m = 0;
    char check;
    char enter;
    char ch;
    int overflow, underflow,list_overflow = 0, list_underflow;
    char el;
    char el_ar; 
    unsigned long long tb_m, te_m, tb_s, te_s;
    while (menu)
    {
        printf("Size of stack - 10\n");
        printf("1 - palindrome check(stack with array)\n");
        printf("2 - palindrome check(stack with list)\n");
        printf("3 - push new element in array stack\n");
        printf("4 - push new element in list stack\n");
        printf("5 - pop  element from array stack\n");
        printf("6 - pop element from list stack\n");
        printf("7 - show array stack\n");
        printf("8 - show list stack\n");
        printf("9 - list of free spaces\n");
        printf("10 - measure time and memmory(array stack,list stack)\n");
        printf("0 - exit");
        printf("\n\n>>>");
        //scanf("%c", &check);
        if (scanf("%d", &menu) == 0 || menu > 10 || menu < 0)
        {
            printf("Incorrect input!!!\n");
            break;
        }
        // if (check == '\n')
        // {
        //     printf("Empty input!\n");
        //     break;
        // }
        // else
        //     menu = (int)check;

        //printf("menu: %c\n", menu);


        if (menu == 1)
        {
            palindrome_check_array();
        }
        if (menu == 2)
        {
            palindrome_check_list();
        }
        if (menu == 3)
        {
            enter = getchar();
            printf("Input only one element: ");
            ch = getchar();
            overflow = push_array(&stack, ch);
            //printf("main_size: %d", stack.size_array);
            if (overflow == STACK_OVERFLOW)
            {
                printf("Stack overflow!\n");
                break;
            }
        }
        if (menu == 4)
        {
            if (stack_free.size_array != 0)
                pop_array_free(&stack_free);

            enter = getchar();
            printf("Input only one element: ");
            ch = getchar();
            if (list_overflow == STACK_MAX_SIZE_LIST)
            {
                printf("Stack overflow!\n");
                break;
            }
            push_list(&head, ch);
            list_overflow++;

        }
        if (menu == 5)
        {
            //printf("underflow: %d\n", underflow);
            if (stack.size_array == 0)
            {
                printf("Stack is empty!\n");
                break;
            }
            else 
            {
                el_ar = peek_ar_1(&stack);
                printf("-----------------------------------------\n");
                printf("|        VALUE      |       ADRESS      |\n");
                printf("-----------------------------------------\n");
                printf("|       %c           |", el_ar);
                peek_ar(&stack);
                printf("-----------------------------------------\n");
            }
            pop_array(&stack);
                
        }
        if (menu == 6)
        {
            if (getSize_list(head) == 0)
            {
                printf("Stack is empty!\n");
                break;
            }
            else 
            {
                el = peek_list_1(head);
                printf("-----------------------------------------\n");
                printf("|        VALUE      |       ADRESS      |\n");
                printf("-----------------------------------------\n");
                printf("|       %c      |", el);
                peek_list(head);
                printf("-----------------------------------------\n");     
            }
            pop_list_free(&head, &stack_free);
        }
        if (menu == 7)
        {
            enter = getchar();
            printStack_array(&stack);
        }
        if (menu == 8)
        {
            enter = getchar();
            printStack_list(head);
        }

        if (menu == 9)
        {
            printStack_array_free(&stack_free);
        }


        if (menu == 10)
        {
            enter = getchar();
            printf("Input count of elements: ");
            scanf("%d", &count_m);
            tb_m = tick();
            for (int i = 0; i < count_m; i++)
                push_array_test(&test_m, i);
            for (int i = 0; i < count_m; i++)
                pop_array_test(&test_m);
            te_m = tick();

            tb_s = tick();
            for (int i = 0; i < count_m; i++)
                push_list(&head, i);
            for (int i = 0; i < count_m; i++)
                pop_list(&head);
            te_s = tick();



            printf("|----------------------------------------------------------------|\n");
            printf("|                  |          TIME         |       MEMMORY       |\n");
            printf("|----------------------------------------------------------------|\n");
            printf("|       array      |          %llu         |         %lu       |\n", (te_m - tb_m) / N, count_m*sizeof(Stack_t_test));
            printf("|----------------------------------------------------------------|\n");
            printf("|       list       |         %llu          |         %lu       |\n", (te_s - tb_s) / N, count_m*sizeof(Node_t));
            printf("|----------------------------------------------------------------|\n");





           // printf("time: %llu\n", (tem - tbm) / N);
            //printf("count: %d\n", count_m);

        }

        // if (menu == 9)
        // {
        //     enter = getchar();
        //     free_memmory(&stack);
        // }
    }
}
