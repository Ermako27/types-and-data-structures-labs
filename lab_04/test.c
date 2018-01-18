#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include "structures.h"
//#include "array.h"

#define QMAX 10000
#define N 35000

#define QMAX 10000

/*


/////////////////////////////////////////
       ОЧЕРЕДЬ МАССИВОМ
///////////////////////////////////////////////



*/

// #define QMAX 100

// typedef struct queue {
//   int qu[QMAX];
//   int rear, frnt;
// } Queue_t;

// //Добавление элемента в очередь
// void insert_main(Queue_t *q, float in, float proc) {
//   if(q->rear < QMAX-1) {
//     q->rear++;
//     q->qu[q->rear][0]= in;
//     q->qu[q->rear][1]= proc;
//   }
//   else
//     printf("Очередь полна!\n");
//   return;
// }



typedef struct queue {
  float qu[QMAX][2];
  int rear, frnt;
} Queue_t;


//Инициализация очереди
void init(Queue_t *q) {
  q->frnt = 1;
  q->rear = 0;
  return;
}


//Добавление элемента в очередь
// void insert(Queue_t *q, int x) {
//   if(q->rear < QMAX-1) {
//     q->rear++;
//     q->qu[q->rear]=x;
//   }
//   else
//     printf("Очередь полна!\n");
//   return;
// }
Добавление элемента в очередь
void insert_main(Queue_t *q, float in, float proc) {
  if(q->rear < QMAX-1) {
    q->rear++;
    q->qu[q->rear][0]= in;
    q->qu[q->rear][1]= proc;
  }
  else
    printf("Очередь полна!\n");
  return;
}



// //Проверка пустоты очереди
// int isempty(Queue_t *q) {
//   if(q->rear < q->frnt)    return(1);
//   else  return(0);
// }


//Вывод элементов очереди
// void print(Queue_t *q) {
//   int h;
//   if(isempty(q)==1) {
//     printf("Очередь пуста!\n");
//     return;
//   }
//   for(h = q->frnt; h<= q->rear; h++)
//     printf("%d ",q->qu[h]);
//   return;
// }


int removex(Queue_t *q) {
  int h;
  float *x;
  // if(isempty(q)==1) {
  //   printf("Очередь пуста!\n");
  //   return(0);
  // }
  x = q->qu[q->frnt];
  for(h = q->frnt; h < q->rear; h++) {
    q->qu[h][0] = q->qu[h+1][0];
    q->qu[h][1] = q->qu[h+1][1];
  }
  q->rear--;
  return(x);
}

#define QMAX 10000
#define N 35000



unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}


int main() 
{
/*
    ПЕРЕМЕННЫЕ ДЛЯ РАНДОМА ВРЕМЕНИ
                      */
  float R, r, min;
  int u;
  int i;  
  unsigned int some;
  long int L;
  L = (long) time(NULL); // Системное время
  some = (unsigned) L; // Приведение типов
  srand(some); // Задание исходного случайного числа для rand()


/* 
    ПЕРЕМЕННЫЕ ДЛЯ ОЧЕРЕДИ
                      */
  float in, proc; // общее время входа и обработки
  float in_prev = 0, proc_prev = 0; // время входа и обработки предыдущего элемента
  float t_in, t_proc; // текущее время прихода и обработки заявки
  float wait = 0; // время простоя
  int oa_count = 0; // количество срабатываний ОА
  int out_count = 0; // счетчик вышедших из ОА (1000 = завершение программы)
  int p; // вероятность выхода из ОА
  int l1,r1,l2,r2; // границы времени входа и обработки 
  int queue_len = 1; // длинны очереди

/*
    ИНИЦИАЛИЗАЦИЯ ОЧЕРЕДИ
                      */

  Queue_t *q;
  q = (Queue_t*)malloc(sizeof(Queue_t));
  init(q);


  printf("Введите целые границы времени входа в очередь(в формате: 0 6): ");
  scanf("%d%d", &l1,&r1);

  printf("Введите целые границы времени обработки(в формате: 0 1): ");
  scanf("%d%d", &l2,&r2);

  unsigned long long tb, te;
  int k = 0;

  tb = tick();  
  while (out_count != 1000)
  {
    oa_count += 1;
    r = (float) rand()/RAND_MAX;
    t_in = l1 + (r1 - l1) * r;

    r = (float) rand()/RAND_MAX;
    t_proc = l2 + (r2 - l2) * r;

    insert(q, t_in, t_proc);

    in += t_in;
    proc += t_proc;
    printf("------------%d------------------\n", oa_count);
      printf("t_in %f;  t_proc %f\n", t_in, t_proc);
    printf("in_prev %f; proc_prev %f\n", in_prev, proc_prev);
    //printf("delta %f\n", (t_in - proc_prev));

    if (oa_count != 1)
    {
      if (q.qu[0] >= proc_prev)
      {
        if (q.rear > 1)
        {
          removex(q);
          printf("len: %d\n", queue_len);
        }

        else
        {
          wait += (t_in - proc_prev);
          printf("delta %f\n", (t_in - proc_prev)); 
        }
      }
      else if (t_in < proc_prev)
      {
        insert(q, 1);
      }
    }

    p = rand()%5;
    //printf("%d\n", p);

    if (p == 4)
    {
      removex(q);
      out_count += 1;
      wait -= (t_in - proc_prev)*5;
    }

    in_prev = t_in;
    proc_prev = t_proc;
    removex(q);
  }
  te = tick();

  printf("OA workes %d times\n", oa_count);
  printf("OA wait %f\n", wait);
  printf("Time: %llu\n", (te - tb) / N);

  return 0;
}