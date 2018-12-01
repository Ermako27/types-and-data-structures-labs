#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_func.h"


#define OVERFLOW -1

void table_init(int unic_count, Hash* table[])
{
	for (int i = 0; i < unic_count; i++)
		table[i] = NULL;
}

void hash_insert(Hash **head, char* word) 
{
    Hash *tmp = (Hash*) malloc(sizeof(Hash));
    tmp->word = word;
    tmp->next = (*head);
    (*head) = tmp;
}

Hash* hash_search(Hash* head, char* word, int *cmp_count)
{
	*cmp_count = 0;
	if (head == NULL)
		return NULL;
	while (head)
	{
		*cmp_count += 1;
		if (strcmp(word, head->word) == 0)
			return head;
		head = head->next;
	}
}

int func(int frq, int unic) // частота появления в тексте % количество уникальных слов
{
	//printf("frq: %d unic: %d index: %d\n", frq, unic, frq % unic);
	return frq % unic;
}


void printLinkedList(Hash *head) 
{
    while (head) 
    {
        printf("%s ", head->word);
        head = head->next;
    }
    printf("\n");
}




/////////////////////////////////////////////////////////

int close_func(int frq, int size, int i)
{
	int h1 = frq % size;
	//printf("fqr: %d, size: %d, i: %d, h1: %d, res: %d\n", frq,size,i,h1,(h1 + i * (2*h1 + 1)) % size);
	return (h1 + i * (2*h1 + 1)) % size;
}

int close_func_split(int frq, int size, int i)
{
	int h  = frq % size;
	int h1 = h + i;
	//printf("fqr: %d, size: %d, i: %d, h: %d, h1: %d\n", frq,size,i,h,h);

	return h1;
}


void close_table_init(char* table[], int size)
{
	for (int i = 0; i < size; i++)
		table[i] = NULL;
	
}

int close_hash_insert(char *table[], char* word, int size, int frq)
{
	int i = 0;
	int j = 0;
	while (i != size)
	{
		j = close_func_split(frq, size, i);
		if (table[j] == NULL)
		{
			table[j] = word;
			return j;
		}
		else
			i++;
	}
	return OVERFLOW;
}

char* close_hash_search(char* table[], char* word, int size, int frq, int* cmp_count)
{
	*cmp_count = 0;
	int i = 0;
	int j;

	if (frq == 0)
		return NULL;
	while (table[j] != NULL || i != size)
	{
		j = close_func_split(frq, size, i);
		if (strcmp(word, table[j]) == 0)
		{
			*cmp_count += 1;
			return table[j];
		}
		i++;
		*cmp_count += 1;
	}

}