#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array.h"
#include "timegen.h"

// #define T1_LEFT 0
// #define T1_RIGHT 6
#define QMAX 6000
#define QAR 10
#define N 500

#define OK 0
#define ARRAY_OVERFLOW -1
#define ARRAY_UNDERFLOW -2



//Инициализация очереди
void init(Queue_t *q) {
  q->frnt = 1;
  q->rear = 0;
  return;
}


//Добавление элемента в очередь
void insert(Queue_t *q, int x) {
  if(q->rear < QMAX-1) {
    q->rear++;
    q->qu[q->rear]=x;
  }
  else
    printf("Очередь полна!\n");
  return;
}

int insert_arr(Queue_t_array *q, char x) {
  if(q->rear < QAR-1) {
    q->rear++;
    q->qu[q->rear]=x;
    return OK;
  }
  else
    return ARRAY_OVERFLOW;
}


//Проверка пустоты очереди
int isempty(Queue_t *q) {
  if(q->rear < q->frnt)    return(1);
  else  return(0);
}

int isempty_array(Queue_t_array *q) {
  if(q->rear < q->frnt)    return(1);
  else  return(0);
}


//Вывод элементов очереди
void print(Queue_t *q) {
  int h;
  if(isempty(q)==1) {
    printf("Очередь пуста!\n");
    return;
  }
  for(h = q->frnt; h<= q->rear; h++)
    printf("%d ",q->qu[h]);
  return;
}

//Вывод элементов очереди
void print_array_queue(Queue_t_array *q) {
  int h;
  if(isempty_array(q)==1) {
    printf("Очередь пуста!\n");
    return;
  }


  printf("Queue >\n");
  printf("---------------------------------------------\n");
  printf("|        VALUE      |         ADRESS        |\n");
  printf("---------------------------------------------\n");
  for(h = q->frnt; h<= q->rear; h++)

    printf("|         %c         |       %p       |\n", q->qu[h],&(q->qu[h]));
    printf("---------------------------------------------\n");
  return;
}


int removex(Queue_t *q) {
  int x, h;
  if(isempty(q)==1) {
    return 0;
  }
  x = q->qu[q->frnt];
  for(h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h+1];
  }
  q->rear--;
  return x;
}

int removex_array(Queue_t_array *q) {
  int h;
  char x;
  if(isempty_array(q)==1) {
    printf("Очередь пуста!!!\n");
    return ARRAY_UNDERFLOW;
  }
  x = q->qu[q->frnt];
  printf("-----------------------------------------\n");
  printf("|        VALUE      |       ADRESS      |\n");
  printf("-----------------------------------------\n");
  printf("|       %c           |       %p     |\n", q->qu[q->frnt], &(q->qu[q->frnt]));
  printf("-----------------------------------------\n");
  for(h = q->frnt; h < q->rear; h++) {
    q->qu[h] = q->qu[h+1];
  }
  q->rear--;
  return OK;
}

float pogr(float l1, float r1, float l2, float r2){


  float avg_work = (r2 - l2) / 2;
  float on_one = avg_work * 5;

  float work_time = 1000 * on_one;


  float avg_in  = (r1 - l1) / 2;
  float in_time = 1000 * avg_in;
  float wait_time = in_time - work_time;

  return wait_time;


}


int array_queue(void){
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
  float l1,r1,l2,r2; // границы времени входа и обработки 
  int queue_len = 1; // длинны очереди
  float average_len = 0;
  float average_time = 0;
  float average_time_in_queue = 0;
  float time_in_queue = 0;
  float average_proc = 0;
  int len_amount = 0;
  float time_amount;
  float ideal_wait;

/*
    ИНИЦИАЛИЗАЦИЯ ОЧЕРЕДИ
                      */

  Queue_t *q;
  q = (Queue_t*)malloc(sizeof(Queue_t));
  init(q);

  printf("Введите целые границы времени входа в очередь(в формате: 0 6): ");
  if (scanf("%f%f", &l1,&r1) == 0)
  {
    printf("Incorrect input!!!");
    return -5;
  }


  printf("Введите целые границы времени обработки(в формате: 0 1): ");
  if (scanf("%f%f", &l2,&r2) == 0)
  {
    printf("Incorrect input!!!");
    return -5;
  }


  if ((l1 == 0 && r1 == 0 ) || (l2 == 0 && r2 == 0))
  {
    printf("Zero interval!!!\n");
    return -5;
  }

  ideal_wait = pogr(l1,r1,l2,r2);

  
  



  unsigned long long tb, te;
  int k = 0;

  tb = tick();  
  while (out_count != 1000)
  {
    len_amount += queue_len;

    insert(q, 1);

    oa_count += 1;
    r = (float) rand()/RAND_MAX;
    t_in = l1 + (r1 - l1) * r;

    r = (float) rand()/RAND_MAX;
    t_proc = l2 + (r2 - l2) * r;

    in += t_in;
    proc += t_proc;

    if (oa_count != 1)
    {

      time_in_queue += abs((t_in - in_prev));

      if (t_in >= proc_prev)
      {
        if (queue_len > 1)
        {
          removex(q);
          queue_len -= 1;

        }

        else
        {

          if (wait < ideal_wait && ideal_wait > 0)
            wait += (t_in - proc_prev);

        }
      }
      else if (t_in < proc_prev)
      {
        time_amount += proc_prev - t_in;
        insert(q, 1);
        queue_len += 1;

      }
    }

    p = rand()%5;


    if (p == 4)
    {
      removex(q);
      out_count += 1;
      if (out_count != 0 && out_count % 100 == 0)
      {
        average_len = len_amount / oa_count;
        average_time = time_amount / oa_count;
        printf("---------------------------------------------\n");
        printf("Current queue len: %d\n", queue_len);
        printf("Average queue len: %f\n", average_len);
        printf("Average time in queue: %f\n", average_time);
        printf("out: %d\n", out_count);
      }

    }

    in_prev = t_in;
    proc_prev = t_proc;
    removex(q);
  }

  average_proc = proc / 1000;
  float modeling = proc + wait;
  int in_elements = modeling / ((r1-l1)/2);
  int memmory = QMAX  * sizeof(int) + 8;
  printf("---------------------------------------------\n\n\n");
  printf("|-------------------RESULT-----------------|\n");
  printf("OA workes %d times\n", oa_count);
  printf("Modeling time: %f\n",modeling);
  printf("OA wait %f\n", wait);
  printf("Count of in elemnts: %d\n", in_elements);
  printf("Count of out elements: 1000\n");
  te = tick();  
  printf("|------------------------------------------|\n");
  printf("|       TIME        |       MEMMORY        |\n");
  printf("|------------------------------------------|\n");
  printf("|       %llu         |         %d          |\n", (te - tb) / N, memmory);
  printf("|------------------------------------------|\n");

  return 0;
}
