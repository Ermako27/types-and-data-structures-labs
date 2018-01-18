#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define STACK_MAX_SIZE 20
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OK 0
#define N 5

typedef char T;

typedef struct Stack_tag_array 
{
    T data[STACK_MAX_SIZE];
    int size_array;
} Stack_t;

unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}
 
int push_array(Stack_t *stack, const T value) 
{
    if (stack->size_array >= STACK_MAX_SIZE)
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
 
void printStack_array(const Stack_t *stack, void (*printStackValue)(const T)) 
{
    int i;
    int len = stack->size_array - 1;
    printf("Current stack %d: ", stack->size_array);
    for (i = 0; i < len; i++) 
    {
        printStackValue(stack->data[i]);
        printf(" | ");
    }
    if (stack->size_array != 0) 
    {
        printStackValue(stack->data[i]);
    }
    printf("\n");
}

T pop_array(Stack_t *stack) {
    if (stack->size_array == 0)
        return STACK_UNDERFLOW;
    stack->size_array--;
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
    //printf("memmory: %lu\n", sizeof(stack));
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
    // tb = tick();

    len = stack_array.size_array;
    // printf("len: %d\n", len);
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
    // printf("under: %d\n", under_stak_len);
    for (int i = 0; i < under_stak_len; i++)
    {
        if (understack1[i] != understack2[under_stak_len-1-i])
        {
            flag = 1;
            break;
        }
    }
    te = tick();

    // printf("%s\n", understack1);
    // printf("%s\n", understack2);
    

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

// int read_line(char *st)
// {
//     int ch, i = 0;
//     while ((ch = getchar()) != '\n' && ch != EOF)
//     {
//         st[i++] = ch;
//     }
//     st[i] = '\0';
//     return OK;
// }

