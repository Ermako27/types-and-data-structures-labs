#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "functions.h"



void read_line(int *s, int n)
{
	char num , i = 0;
	while ((num = getchar()) != '\n' && num != EOF)
	{
		if (i < n - 1){
			printf("%c\n", num);
			s[i++] = num;
			printf("s[i]: %d", s[i]);
		}
	}
}

int zeros(int n, int *array)
{
	printf("1\n");
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (array[i] == 0)
		{
			count++;
			printf("%d\n",count);
		}
	}
	return 0;
}

int count_of_non_zero(int *data, int n) // количество ненулевх элементов
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (data[i] != 0)
			count++;
	}
	return count;
}

int* ja_create(int *data, int n) // создание массива индексов ненулевых элементов
{
	int p = 0;
	int *ja = malloc(n * sizeof(int));
	if (!ja)
		return NULL;

	for (int i = 0; i < n; i++)
	{
		if (data[i] != 0)
			ja[p++] = i+1;
	}

	return ja;
}

int* an_create(int *data, int *ja, int n) // создание массива из элементов по ненулевым индексам
{
	int *an = malloc(n * sizeof(int));
	if (!an)
		return NULL;

	for (int i = 0; i < n; i++)
		an[i] = data[ja[i]-1];

	return an;
}

int* ip_create(int *ja, int n, int none_zero)
{
	int p = 0;
	int *ip = malloc (n * sizeof(int));
	if (!ip)
		return NULL;

	for (int i = 0; i < n; i++)
		ip[i] = 0;

	
	for (int i = 0; i < none_zero; i++)
	{
		ip[ja[i]-1] = i + 1;
	}
	
	return ip;
}

int scalar_multiply(int *jb, int *an, int *bn, int *ip, int less)
{
	int result = 0;

	int jb_index;
	int ip_index;

	int jb_value;
	int ip_value;

	for (int i = 0; i < less; i++)
	{
		jb_value = jb[i];
		ip_value = ip[jb_value-1];
		if (jb_value != 0 && ip_value != 0)
		{

			result += an[ip_value-1] * bn[i];
		}
	}
	return result;
}

void free_matrix_rows(int **data, int n)
{
    for (int i = 0; i < n; i++)
       // free можно передать NULL
       free(data[i]);

    free(data);
}

int** allocate_matrix_rows(int n, int m)
{
	int r;
	unsigned int some;
    long int L;
    L = (long) time(NULL); // Системное время
    some = (unsigned) L; // Приведение типов
    srand(some); // Задание исходного случайного числа для rand()

    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        }
        for(int j = 0; j < m; j++)
        {
        	r = rand()%10+1;
            data[i][j] = r;
            //printf("%f\n",data[i][j] );
        }   
    }
    return data;
}

int** allocate_matrix_rows_zero(int n, int m)
{
	

    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        }
        for(int j = 0; j < m; j++)
        {

            data[i][j] = 0;
            //printf("%f\n",data[i][j] );
        }   
    }
    return data;
}

int** self_allocate_matrix_rows(int n, int m)
{
	int input;
    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        }
        for(int j = 0; j < m; j++)
        {
        	printf("введите элемент (%d, %d) матрицы: ", i ,j);
        	scanf("%d", &input);
        	//printf("\n");
            data[i][j] = input;
            //printf("%f\n",data[i][j] );
        }   
    }
    return data;
}
// {
// 	char enter;

//     int **data = calloc(n, sizeof(int*));
//     if (!data)
//         return NULL;

//     for (int i = 0; i < n; i++)
//     {
//         data[i] = malloc(m * sizeof(int));
//         if (!data[i])
//         {
//             free_matrix_rows(data, n);
//             return NULL;
//         }

//         enter = getchar();
//         printf("Введите строку %d матрицы (строка из челых чисел): ", i+1);
//         read_line(data[i], m);
//         for (int j = 0; j < m; j++)
//         	printf("%d\n", data[i][j]);
//     }
//     return data;
// }

void zero_add(int n, int m, int *array[m],int zero)
{
	unsigned int some;
    long int L;
    L = (long) time(NULL); // Системное время
    some = (unsigned) L; // Приведение типов
    srand(some); // Задание исходного случайного числа для rand()

	int zero_count = 0;
	int i_rand;
	int j_rand;
	int decision;

	// for (int i = 0; i < zero; i++)

	if (n != 1)
	{
		while (zero_count < zero)
		{
			i_rand = rand()%n;
			j_rand = rand()%m;
			if (array[i_rand][j_rand] != 0)
			{
				array[i_rand][j_rand] = 0;
				zero_count++;
			}
		}	
	}
	else
	{
		while (zero_count < zero)
		{
			j_rand = rand()%m;
			if (array[0][j_rand] != 0)
			{
				array[0][j_rand] = 0;
				zero_count++;
			}
		}
	}

	int per = (n*m)*0.2;

	for (int i = 0; i < per; i++)
	{
		if (n == 1)
			i_rand = 0;
		else 
			i_rand = rand()%n;
		j_rand = rand()%m;
		array[i_rand][j_rand] *= -1;
	}
}

void minus_add(int n, int m, int *array[m])
{
	unsigned int some;
    long int L;
    L = (long) time(NULL); // Системное время
    some = (unsigned) L; // Приведение типов
    srand(some); // Задание исходного случайного числа для rand()

	int i_rand;
	int j_rand;
	int decision;

	int per = (n*m)*0.2;

	for (int i = 0; i < per; i++)
	{
		if (n == 1)
			i_rand = 0;
		else 
			i_rand = rand()%n;
		j_rand = rand()%m;
		array[i_rand][j_rand] *= -1;
	}
}

void print_matrix(int n, int m, int *a[m]) // функция печати массива
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf(" %3d |", a[i][j]);
            //printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}


void transpon(int size1, int size2, int *array[size2])
{
	for(int i = 0; i < size1; i++)
    {
        for(int j = i; j < size2; j++)
        {
            int temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }
}

int** not_square_transpon(int n, int m, int *array[m])
{
    int **data = calloc(m, sizeof(int*));
    for (int i = 0; i < m; i++)
    {
        data[i] = malloc(n * sizeof(int));
        for(int j = 0; j < n; j++)
        {
            data[i][j] = array[j][i];;
        }   
    }
    return data;
}
