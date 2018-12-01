#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


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

	// while (zero_count != zero)
	// {
	// 	i_rand = rand()%n;
	// 	j_rand = rand()%m;
	// 	decision = rand()%4;
	// 	if (decision == 2 && array[i_rand][j_rand] != 0)
	// 	{
	// 		array[i_rand][j_rand] = 0;
	// 		zero_count++;
	// 	}
	// 	else if (decision == 3)
	// 		array[i_rand][j_rand] *= -1;
	// }

	for (int i = 0; i < zero; i++)
	{
		i_rand = rand()%n;
		j_rand = rand()%m;
		array[i_rand][j_rand] = 0;
	}

	int per = (n*m)*0.2;

	for (int i = 0; i < per; i++)
	{
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

            printf("%d ", a[i][j]);
            //printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
	int **array;
	array = allocate_matrix_rows(10,10);
	print_matrix(10,10,array);
	zero_add(10,10,array,20);
	print_matrix(10,10,array);


	return 0;
}


