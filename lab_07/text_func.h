#ifndef structures_h
#define structures_h

#include "structures.h"

#endif

#ifndef __TEXT_FUNC__H__

#define __TEXT_FUNC__H__

void free_matrix_rows(char **data, int n);

char** allocate_matrix_rows(int n);

void fill_text(int n, int m, char *text[m], FILE *f);

int word_count(FILE *f);

int create_unic_words(int n, int m, char *array[m], char *unic[]);

int frequency(int n, int m, char *array[m], char *word);

int unic_find(int n, char *unic[], char *word);

#endif
