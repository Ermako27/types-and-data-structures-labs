#include "structures.h"

#ifndef __ARRAY__H__

#define __ARRAY__H__

int removex(Queue_t *q);

int removex_array(Queue_t_array *q);

void init(Queue_t *q);

void insert(Queue_t *q, int x);

int insert_arr(Queue_t_array *q, char x);

int isempty(Queue_t *q);

int isempty_array(Queue_t_array *q);

void print(Queue_t *q);

void print_array_queue(Queue_t_array *q);

float pogr(float l1, float r1, float l2, float r2);

int array_queue(void);

#endif
