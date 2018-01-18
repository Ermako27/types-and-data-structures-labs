#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define QMAX 6000
#define QAR 10

typedef struct queue {
  int qu[QMAX];
  int rear, frnt;
} Queue_t;

typedef struct queue_array {
  char qu[QAR];
  int rear, frnt;
} Queue_t_array;
