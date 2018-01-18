#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "list.h"
#include "timegen.h"

#define N 500

#define OK 0
#define list_OVERFLOW -3
#define list_UNDERFLOW -4

void init_list(Queue_t_list *q) {
  q->frnt = 0;
  q->rear = 0;
}

Queue_t_list * init_knot(char a) // а- значение первого узла
{
  Queue_t_list *lst;
  // выделение памяти под корень списка
  lst = (Queue_t_list*)malloc(sizeof(Queue_t_list));
  lst->field = a;
  lst->ptr = NULL; // это последний узел списка
  return(lst);
}

Queue_t_list * addelem(Queue_t_list *lst, char number)
{
  Queue_t_list *temp, *p;
  temp = (Queue_t_list*)malloc(sizeof(Queue_t_list));
  p = lst->ptr; // сохранение указателя на следующий узел
  lst->ptr = temp; // предыдущий узел указывает на создаваемый
  temp->field = number; // сохранение поля данных добавляемого узла
  temp->ptr = p; // созданный узел указывает на следующий элемент
  return(temp);
}

//Проверка пустоты очереди
int isempty_list(Queue_t_list *q) {
  if(q->frnt==0)
    return(1);
  else
    return(0);
}

//Добавление элемента в очередь
void insert_list(Queue_t_list *q, char x) {
  if((q->rear==0) && (q->frnt==0)) {
    q->rear = init_knot(x);
    q->frnt = q->rear;
  } else
    q->rear = addelem(q->rear, x);
}

//Вывод элементов очереди
void print_list_queue(Queue_t_list *q) {
  Queue_t_list *h;
  if(isempty_list(q)==1) {
    printf("Очередь пуста!\n");
    return;
  }


  printf("Queue >\n");
  printf("---------------------------------------------\n");
  printf("|        VALUE      |         ADRESS        |\n");
  printf("---------------------------------------------\n");
  for(h = q->frnt; h!= NULL; h=h->ptr)
    printf("|         %c         |       %p       |\n", h->field,&(h->field));
    printf("---------------------------------------------\n");
  return;
}

//Удаление элемента из очереди
int remove_list(Queue_t_list *q) {
  Queue_t_list *temp;
  int x;
  if(isempty_list(q)==1) {
    //printf("Очередь пуста!\n");
    return 0;
  }
  x = q->frnt->field;
  temp = q->frnt;
  q->frnt = q->frnt->ptr;
  free(temp);
  return x;
}


int remove_list_main(Queue_t_list *q) {
  Queue_t_list *temp;
  int x;
  if(isempty_list(q)==1) {
    printf("Очередь пуста!\n");
    return list_UNDERFLOW;
  }
  x = q->frnt->field;
  printf("-----------------------------------------\n");
  printf("|        VALUE      |       ADRESS      |\n");
  printf("-----------------------------------------\n");
  printf("|       %c           |       %p     |\n", q->frnt->field, &(q->frnt->field));
  printf("-----------------------------------------\n");
  temp = q->frnt;
  q->frnt = q->frnt->ptr;
  free(temp);
  return OK;
}


float pogr_list(float l1, float r1, float l2, float r2){


  float avg_work = (r2 - l2) / 2;
  float on_one = avg_work * 5;
  float work_time = 1000 * on_one;
  float avg_in  = (r1 - l1) / 2;
  float in_time = 1000 * avg_in;
  float wait_time = in_time - work_time;

  return wait_time;


}


int list_queue(void){
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

  Queue_t_list *q;
  q = (Queue_t_list*)malloc(sizeof(Queue_t_list));
  init_list(q);

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

  ideal_wait = pogr_list(l1,r1,l2,r2);

  
  



  unsigned long long tb, te;
  int k = 0;

  tb = tick();  
  while (out_count != 1000)
  {
    len_amount += queue_len;

    insert_list(q, 1);

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
          remove_list(q);
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
        insert_list(q, 1);
        queue_len += 1;

      }
    }

    p = rand()%5;

    if (p == 4)
    {
      remove_list(q);
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
    remove_list(q);
  }

  average_proc = proc / 1000;
  float modeling = proc + wait;
  int in_elements = modeling / ((r1-l1)/2);
  int memmory = abs(in_elements - 1000) * 8;
  printf("---------------------------------------------\n\n\n");
  printf("|-------------------RESULT------------------|\n");
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
