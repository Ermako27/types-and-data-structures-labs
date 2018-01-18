#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct list {
  int field;
  struct list *ptr, *frnt, *rear;
} Queue_t_list;