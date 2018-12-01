#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

	// if (none_zero_a <= none_zero_b)
	// 	less = none_zero_a;
	// else
	// 	less = none_zero_b;

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

	for (int i = 0; i < zero + 1; i++)
	{
		if (n == 1)
			i_rand = 0;
		else 
			i_rand = rand()%n;

		j_rand = rand()%m;
		array[i_rand][j_rand] = 0;
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

int** not_square_transpon(int size1, int size2, int *array[size2])
{
    int **data = calloc(size2, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < size2; i++)
    {
        data[i] = malloc(size1 * sizeof(int));
        if (!data[i])
        {
            free_matrix_rows(data, size1);
            return NULL;
        }
        for(int j = 0; j < size1; j++)
        {

            data[i][j] = array[i][j];
            //printf("%f\n",data[i][j] );
        }   
    }
    return data;
}


int main(void)
{
	int **array;
	int **vector;

	int none_zero_a;
	int none_zero_b;
	int *ja;
	int *an;
	int *ip;
	int *jb;
	int *bn;

	int scalar_res;
	int result_vector[10];

	array = allocate_matrix_rows(5,10);
	print_matrix(5,10,array);
	zero_add(5,10,array,20);
	print_matrix(5,10,array);
	array = not_square_transpon(5,10,array);
	print_matrix(10,5,array);

	vector = allocate_matrix_rows(1,10);
	print_matrix(1,10,vector);
	zero_add(1,10,vector,5);
	print_matrix(1,10,vector);

	int *bptr = vector[0];

	for (int i = 0; i < 10; i++)
	{
		int *aptr = array[i];

		none_zero_a = count_of_non_zero(aptr, 10);
		ja = ja_create(aptr,10);
		an = an_create(aptr,ja,none_zero_a);
		ip = ip_create(ja,10,none_zero_a);

	    none_zero_b = count_of_non_zero(bptr, 10);
		jb = ja_create(bptr,10);
	    bn = an_create(bptr,jb,none_zero_b);

	    if (none_zero_a <= none_zero_b)
			scalar_res = scalar_multiply(ja,bn,an, ip, none_zero_a);
		else
			scalar_res = scalar_multiply(jb,an,bn, ip, none_zero_b);
		
		result_vector[i] = scalar_res;

	}


	if (n < 30 || m < 30)
	{
		for (int i = 0; i < 10; i++)
			printf("%d | ", result_vector[i]);
	}

	return 0;
}



		// ip = ip_create(jb,m,none_zero_b);
		// for (int i = 0; i < none_zero_a; i++)
		// 	printf("%d ", ja[i]);
		// printf("\n");
		// for (int i = 0; i < none_zero_a; i++)
		// 	printf("%d ", an[i]);
		// printf("\n");
		// for (int i = 0; i < m; i++)
		// 	printf("%d ", ip[i]);
		// printf("\n");

	 //    none_zero_a = count_of_non_zero(aptr, m);
		// ja = ja_create(aptr,m);
	 //    an = an_create(aptr,ja,none_zero_a);

		// for (int i = 0; i < none_zero_b; i++)
		// 	printf("%d ", jb[i]);
		// printf("\n");
		// for (int i = 0; i < none_zero_b; i++)
		// 	printf("%d ", bn[i]);
		// printf("\n");
		// printf("---------------------------------\n");

	  //   if (none_zero_a <= none_zero_b)
	  //   {
	  //   	printf("!!!!!!\n");
	  //   	tb = tick();
			// scalar_res = scalar_multiply(ja,bn,an, ip, none_zero_a);
			// te = tick();
	  //   }

		// else
		// {
		// 	printf("$$$$$$44\n");
	 //    	tb = tick();
		// 	scalar_res = scalar_multiply(jb,an,bn, ip, none_zero_b);
		// 	te = tick();
		// }