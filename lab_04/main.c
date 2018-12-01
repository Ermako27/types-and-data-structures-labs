/*

Вариант 5 по заданию.

В данной задаче главное вовремя понять, что аппарат это абстракция, его на самом деле нет, и потому не нужно стараться реализовать реальные параллельные процессы поступления заявок из очередей в аппарат и одновременных обработок этих заявок. Суть моей реализации в том, что вся программа состоит из множества счетчиков и каждый из них зависит от другого, этими счетчиками моделируется время, вероятность возврата, количество вошедших и обработанных и многое другое.

В этой лабе наконец получилось сделать толковый make файл позволяющий правильно струкртурировать программу.
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "array.h"
#include "list.h"
#include "timegen.h"

// #define T1_LEFT 0
// #define T1_RIGHT 6


#define QMAX 6000
#define QAR 10
#define QLIST 10
#define N 500

#define TRUE 1
#define OK 0
#define ARRAY_OVERFLOW -1
#define ARRAY_UNDERFLOW -2


int main(void) 
{
	int menu = TRUE;
	char ch, enter;
	int array_overflow, array_underflow;
	int list_overflow = 0;
/* инициализация очереди массивом */
	Queue_t_array *q; 
	q = (Queue_t_array*)malloc(sizeof(Queue_t_array));
    q->frnt = 1;
    q->rear = 0;

/* инициализация очереди списком */

    Queue_t_list *ql;
    ql = (Queue_t_list*)malloc(sizeof(Queue_t_list));
  	init_list(ql);

	while (menu)
	{
        printf("1 - array queue modeing\n");
        printf("2 - list queue modeling\n");
        printf("3 - add new element in array queue\n");
        printf("4 - add new element in list queue\n");
        printf("5 - remove  element from array queue\n");
        printf("6 - remove element from list queue\n");
        printf("7 - show array queue\n");
        printf("8 - show list queue\n");
       // printf("9 - measure time and memmory(array queue,list queue)\n");
        printf("0 - exit");
        printf("\n\n>>>");

        if (scanf("%d", &menu) == 0 || menu > 8 || menu < 0)
        {
            printf("Incorrect input!!!\n");
            break;
        }

        if (menu == 1)
        {
        	array_queue();
        	printf("\n\n");
        }

        if (menu == 2)
        {
        	list_queue();
        	printf("\n\n");
        }

        if (menu == 3)
        {
        	enter = getchar();
            printf("Input only one element: ");
            ch = getchar();
            array_overflow = insert_arr(q, ch);
            if (array_overflow == ARRAY_OVERFLOW)
            {
            	printf("Queue overflow!!!\n");
            	break;
            }
        }

        if (menu == 4)
        {
            enter = getchar();
            printf("Input only one element: ");
            ch = getchar();
            if (list_overflow == QLIST)
            {
                printf("Stack overflow!\n");
                break;
            }
            insert_list(ql, ch);
            list_overflow++;
        }

        if (menu == 5)
        {
        	removex_array(q);
        }

        if (menu == 6)
        {
        	remove_list_main(ql);
        }

        if (menu == 7)
        {
        	enter = getchar();
        	print_array_queue(q);
        }

        if(menu == 8)
        {
        	enter = getchar();
        	print_list_queue(ql);
        }


	} 
	return 0;
}
