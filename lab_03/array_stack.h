#ifndef __FUNCTIONS__H__

#define __FUNCTIONS__H__

#define STACK_MAX_SIZE 20

typedef int T;

typedef struct Stack_tag_array 
{
    T data[STACK_MAX_SIZE];
    int size_array;
} Stack_t;


typedef struct Node_tag Node_t;    

int push_array(Stack_t *stack, const T value);

int read_stack_array(Stack_t *stack);

void printStackValue(const T value);

void printStack_array(const Stack_t *stack, void (*printStackValue)(const T));

T pop_array(Stack_t *stack);

void empty_st(void);

int palindrome_check_array(void);

#endif
