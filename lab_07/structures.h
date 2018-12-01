#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node 
{
	char *word; // 1
    int data; // 4
    int height; // 4
    struct Node *left; // 
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct Hash
{
	char *word;
	struct Hash *next;
} Hash;