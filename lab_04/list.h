#include "structures_list.h"

#ifndef __LIST__H__

#define __LIST__H__

void init_list(Queue_t_list *q);

Queue_t_list * init_knot(char a);

Queue_t_list * addelem(Queue_t_list *lst, char number);

int isempty_list(Queue_t_list *q);

void insert_list(Queue_t_list *q, char x);

void print_list_queue(Queue_t_list *q);

int removel_list(Queue_t_list *q);

int remove_list_main(Queue_t_list *q);

float pogr_list(float l1, float r1, float l2, float r2);

int list_queue(void);


#endif
