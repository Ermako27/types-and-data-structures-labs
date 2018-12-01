#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void print_matrix(int n, int m, int *a[m]) // функция печати массива
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
        	printf("%3d ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix_rows(int **data, int n)
{
    for (int i = 0; i < n; i++)
       free(data[i]);

    free(data);
}

int min(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

int** allocate_matrix_rows(int n, int m, FILE *f)
{
    int num;
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
            fscanf(f, "%d", &num);
            data[i][j] = num;
        }
        
    }

    return data;
}

void graph_build(int m, int *matrix[m], FILE *stream)
{
	  fprintf(stream, "graph BST {\n");
     fprintf(stream, "    node [fontname=\"Arial\"];\n");
    for (int i = 0; i < m; i++)
    {
    	for (int j = i; j < m; j++)
    	{
    		if (matrix[i][j] != 0)
    		{
    			fprintf(stream, "    %d--%d[label=%d]\n", i+1, j+1, matrix[i][j]);
    		}
    	}
    }
    fprintf(stream, "}\n");
}

//matrix - матрица смежности
void originalFloydWarshall(int **matrix, int numberOfVert) {
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < numberOfVert; k++) {
        for(int i = 0; i < numberOfVert; i++) {
            for(int j = 0; j < numberOfVert; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
 
}





int main(void)
{
	int n,m;
	FILE *g = fopen("graph.dot", "w");
	FILE *f = fopen("labels.txt", "r");
	fscanf(f,"%d",&n);
	fscanf(f,"%d",&m);
	int **graph = allocate_matrix_rows(n,m,f);
	print_matrix(n,m,graph);
	graph_build(m, graph, g);
	// originalFloydWarshall(graph,m);
	// print_matrix(n,m,graph);



  	int d[m]; // минимальное расстояние
  	int v[m]; // посещенные вершины
  	int temp;
  	int minindex, min;

	for (int i = 0; i<m; i++) 
  	{
    	d[i] = 10000;
    	v[i] = 1;
  	}
  	d[0] = 0;
  	// Шаг алгоритма
  	do 
  	{
    	minindex = 10000;
    	min = 10000;
    	for (int i = 0; i<m; i++) 
    	{ // Если вершину ещё не обошли и вес меньше min
    		if ((v[i] == 1) && (d[i]<min)) 
    		{ // Переприсваиваем значения
       			min = d[i];
       			minindex = i;
    		}
    	}
    // Добавляем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    	if (minindex != 10000) 
    	{
    		for (int i = 0; i<m; i++) 
    		{
       			if (graph[minindex][i] > 0)
       			{
       				temp = min + graph[minindex][i];
       				if (temp < d[i])
          			d[i] = temp;
       			}
    		}
    		v[minindex] = 0;
    	}

  	} while (minindex < 10000);

  	for (int i = 0; i < m; i++)
  	{
  		printf("%5d |", d[i]);
  	}
  	printf("\n");
  	for (int i = 0; i < m; i++)
  	{
  		printf("%5d |", v[i]);
  	}


	return 0;
}