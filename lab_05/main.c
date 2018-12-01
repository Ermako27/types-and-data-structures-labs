#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "functions.h"

#define N 50
#define N1 35

unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}


int main(void)
{
	int vz;
	int zn, zm;
	int count = 0;

	int n, m;
	int decision1;
	int decision2;
	int zero_count;


	int **array;
	int **not_square_array;
	int **vector;

	int none_zero_a;
	int none_zero_b;
	int *ja;
	int *an;
	int *ip;
	int *jb;
	int *bn;

	int scalar_res;

	unsigned long long tb, te, tm = 0;

	printf("Введите размерность матрицы: ");
	if (scanf("%d%d", &n, &m) == 0)
	{
		printf("Incorrect input\n");
		return 0;
	}

	if (n == 0 || m == 0)
	{
		printf("Incorrect input\n");
		return 0;
	}
	printf("\n");
	printf("Как вы хотите ввести матрицу? \n");
	printf("1 - Сгенерировать матрицу и ввести позиции не нулей с клавиатуры. \n");
	printf("2 - Сгенерировать матрицу и случайным образом распределить нули. \n");
	printf(">>> ");
	if (scanf("%d", &decision1) == 0 || decision1 > 2 || decision1 < 1)
	{
		printf("Incorrect input\n");
		return 0;
	}

	int ch;
	if (decision1 == 1)
	{
		printf("Сколько должно быть не нулей в матрице: ");
		scanf("%d", &zero_count);
		printf("Матрица индексируется с единицы.\n");
		array = allocate_matrix_rows_zero(n, m);
		while (count != zero_count)
		{
			printf("Введите позицию не нуля и значение: ");	
			if (scanf("%d%d%d", &zn,&zm,&ch) != 0 || zm <= m || zm >= 0 || zn <= n || zn >= 0)
			{
				array[zn-1][zm-1] = ch;
				count++;
			}
			else
				printf("некорректный ввод\n");
		}
		if (n < 30 || m < 30)
		{
			printf("\n|--------MATRIX--------|\n");
			print_matrix(n, m, array);
		}
		if (n != m)
			not_square_array = not_square_transpon(n,m,array);
		else
			transpon(n,m,array);
	}
	if (decision1 == 2)
	{
		printf("Сколько должно быть нулей в матрице: ");
		scanf("%d", &zero_count);
		array = allocate_matrix_rows(n,m);
		zero_add(n,m,array,zero_count);
		if (n < 30 || m < 30)
		{
			printf("\n|--------MATRIX--------|\n");
			print_matrix(n,m,array);
		}
		if (n != m)
			not_square_array = not_square_transpon(n,m,array);
		else
			transpon(n,m,array);

	}

	printf("Как вы хотите ввести вектор? \n");
	printf("1 - Сгенерировать вектор и ввести позиции нулей с клавиатуры. \n");
	printf("2 - Сгенерировать вектор и случайным образом распределить нули. \n");
	printf(">>> ");
	if (scanf("%d", &decision2) == 0 || decision2 > 2 || decision2 < 1)
	{
		printf("Incorrect input\n");
		return 0;
	}
	if (decision2 == 1)
	{
		printf("Сколько должно быть не нулей в векторе: ");
		scanf("%d", &zero_count);
		printf("Вектор индексируется с единицы.\n");
		vector = allocate_matrix_rows_zero(n, m);
		count = 0;
		while (count != zero_count)
		{
			printf("Введите позицию не нуля и значение: ");	
			if (scanf("%d%d",&zm,&ch) != 0 || zm <= m || zm >= 0 || zn <= n || zn >= 0)
			{
				vector[0][zm-1] = ch;
				count++;
			}
		}
		if (n < 30 || m < 30)
		{
			printf("\n|--------VECTOR--------|\n");
			print_matrix(1, m, vector);
		}
	}

	if (decision2 == 2)
	{
		printf("Сколько должно быть нулей в векторе: ");
		scanf("%d", &zero_count);
		if (n != m)
		{
			vector = allocate_matrix_rows(1, m);
			zero_add(1,m,vector,zero_count);
		}
		else
		{
			vector = allocate_matrix_rows(1, n);
			//zero_add(1,n,vector,zero_count);
		}
		if (n < 30 || m < 30)
		{
			printf("\n|--------VECTOR--------|\n");
			print_matrix(1,m,vector);
		}
	}


	int less;
	if (n <= m)
		less = n;
	else
		less = m;
	int *aptr = vector[0];
	int *bptr;
	int result_vector[less];
	int memory = 0;

	none_zero_a = count_of_non_zero(aptr, less);
    ja = ja_create(aptr,less);
	an = an_create(aptr,ja,none_zero_a);
	ip = ip_create(ja,less,none_zero_a);
	memory += less*sizeof(int);

	for (int i = 0; i < less; i++)
	{
		if (n != m)
			bptr = not_square_array[i];
		else
			bptr = array[i];

		none_zero_b = count_of_non_zero(bptr, less);
		memory += none_zero_b*sizeof(int)*2;
		jb = ja_create(bptr,less);
		bn = an_create(bptr,jb,none_zero_b);
	
	    tb = tick();
		scalar_res = scalar_multiply(jb,an,bn, ip, none_zero_b);
		te = tick();

		tm += ((te - tb) / N);
		result_vector[i] = scalar_res;

	}

	printf("\nРезультаты алгоритма для разреженных матриц.\n");

	if (n < 30 || m < 30)
	{
		printf("Результат умножения: ");
		for (int i = 0; i < less; i++)
			printf("%d | ", result_vector[i]);
	}

	printf("\nЗамеры:\n");
    printf("|------------------------------------------|\n");
    printf("|       TIME        |       MEMMORY        |\n");
    printf("|------------------------------------------|\n");
    printf("|       %llu        |         %d         |\n", tm, memory);
    printf("|------------------------------------------|\n");
	

	int result_vector2[less];
	int proizv = 0;

    tb = tick();
    int c_memory = n*m*sizeof(int);
    int h = 0;

    if (n != m)
    {
		for (int i = 0; i < m; i++)
    	{
    		for (int j = 0; j < n; j++)
    		{
    			proizv += vector[0][j] * not_square_array[i][j];
    		}
    		result_vector2[i] = proizv;
    		proizv = 0;
    	}	
    }
    else
    {
    	for (int i = 0; i < n; i++)
    	{
    		for (int j = 0; j < m; j++)
    		{
    			proizv += vector[0][j] * array[i][j];
    		}
    		result_vector2[i] = proizv;
    		proizv = 0;
    	}
	}

    te = tick();

    printf("\nРезультаты стандартного алгоритма обработки матриц.\n");
        
	if (n < 30 || m < 30)
	{
		printf("Результат умножения: ");
		for (int i = 0; i < less; i++)
			printf("%d | ", result_vector[i]);
	}
    
	printf("\nЗамеры:\n");
    printf("|------------------------------------------|\n");
    printf("|       TIME        |       MEMMORY        |\n");
    printf("|------------------------------------------|\n");
    printf("|       %llu        |         %d         |\n", (te - tb) / N1, c_memory);
    printf("|------------------------------------------|\n");	
}