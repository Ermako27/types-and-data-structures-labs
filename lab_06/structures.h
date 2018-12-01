#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node 
{
	char *word;
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;