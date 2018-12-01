#ifndef structures_h
#define structures_h

#include "structures.h"

#endif



#ifndef __HASH_FUNC__H__

#define __HASH_FUNC__H__

void table_init(int unic_count, Hash* table[]);

void hash_insert(Hash **head, char* word);

Hash* hash_search(Hash* head, char* word, int *cmp_count);

int func(int frq, int unic);

void printLinkedList(Hash *head);

int close_func(int frq, int size, int i);

int close_func_split(int frq, int size, int i);

void close_table_init(char* table[], int size);

int close_hash_insert(char *table[], char* word, int size, int frq);

char* close_hash_search(char* table[], char* word, int size, int frq, int* cmp_count);

#endif
