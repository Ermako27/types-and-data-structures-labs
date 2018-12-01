#include <stdio.h>
#include <string.h>

struct list
{
    list *next;
    list *prev;
    int data;
};

list *new_list()
{
    list *q = new list;
    q->data = 0;
    q->next = q;
    q->prev = q;

    return q;
}

int pop(list *q, int *d)
{
    if (q->prev == q)
    {
		printf("Queue was empty\n");
        return 0;
    }

	float min = d[q->prev->data];
    list *victim = q->prev;
	list *current = q;
	while (q != (current = current->next))
	{
		if (d[current->data] < min)
		{
			min = d[current->data];
			victim = current;
		}
	}

    victim->prev->next = victim->next;
    victim->next->prev = victim->prev;
    int data = victim->data;
    delete victim;
    return data;
}

void push(list *q, int data)
{
    list *tmp = q->next;
    q->next = new list;

    q->next->prev = q;
    q->next->next = tmp;
    q->next->data = data;

    tmp->prev = q->next;
}


void _printPath(int from, int to, char city[100][100], int Pr[100])
{
	if (from == to)
	{
		printf("%s", city[to]);
	} else {
		if (Pr[to] == -1)
		{
			printf("No way\n");
		} else {
			_printPath(from, Pr[to], city, Pr);
			printf(" -> %s", city[to]);
		}
	}
}

void printMinimalPathway(list *G[100], int N, int weights[100][100], char city[100][100], int A, int B)
{
	int d[100], Pr[100];
	for (int i = 0; i < N; i++)
	{
		d[i] = 100000;
		Pr[i] = -1;
	}

	d[A] = 0;
	list *Q = new_list();
	for (int i = 0; i < N; i++)
	{
		push(Q, i);
	}
	while (Q != Q->next)
	{
		int u = pop(Q, d);
		list *cur = G[u];
		while (G[u] != (cur = cur->next))
		{
			int v = cur->data;
			if (d[v] > d[u] + weights[u][v])
			{
				d[v] = d[u] + weights[u][v];
				Pr[v] = u;
			}
		}
	}

	_printPath(A, B, city, Pr);
}

int getCity(char city[100][100], int *cityN, char cityName[100])
{
	for (int i = 0; i < *cityN; i++)
	{
		if (!strcmp(city[i], cityName))
		{
			return i;
		}
	}

	strcpy(city[*cityN], cityName);
	int ret = *cityN;
	(*cityN)++;
	return ret;
}


// void graph_build(int m, int *matrix[m], FILE *stream)
// {
// 	 fprintf(stream, "graph BST {\n");
//      fprintf(stream, "    node [fontname=\"Arial\"];\n");
//     for (int i = 0; i < m; i++)
//     {
//     	for (int j = i; j < m; j++)
//     	{
//     		if (matrix[i][j] != 0)
//     		{
//     			fprintf(stream, "    %d--%d[label=%d]\n", i+1, j+1, matrix[i][j]);
//     		}
//     	}
//     }
//     fprintf(stream, "}\n");
// }

void graph_build(FILE *f, FILE *stream)
{
	fprintf(stream, "graph BST {\n");
	fprintf(stream, "    node [fontname=\"Arial\"];\n");
	int n, m;
	char a, b, enter;
	int s, p;
	fscanf(f, "%d", &n);
	fscanf(f, "%d", &m);

	//printf("n: %d, m: %d\n",n,m);
	for (int i = 0; i < m; i++)
	{
		fscanf(f, "%c", &enter);
		fscanf(f, "%s", &a);
		fscanf(f, "%s", &b);
		fscanf(f, "%d", &s);
		fscanf(f, "%d", &p);
		//printf("a: %c, b: %c, s: %d, p: %d\n",a,b,s,p);
		fprintf(stream, "    %c--%c[label=%d]\n", a, b, s+p);
	}
	fprintf(stream, "}\n");

}

int main(int argc, char **argv)
{
	// char filename[16];
	// printf("Filename: "); 
	// scanf("%s", filename);

	// FILE *f = fopen(filename, "r");
	// if (!f)
	// {
	// 	perror("Error opening file");
	// 	return 1;
	FILE *g = fopen("graph.dot", "w");
	FILE *f = fopen(argv[1], "r"); // успешное открытие файла
    if (f == NULL)
    {
        fprintf(stderr, "Could not open file\n");
    }

	// Создание пустого графа
	list *G[100];
	int cityN = 0;
	char city[100][100];
	int weights[100][100];
	int N; fscanf(f, "%d", &N);
	if (N == 0)
	{
		printf("No way\n");
		return 0;
	}
	int M; fscanf(f, "%d", &M);
	for (int i = 0; i < N; i++)
	{
		G[i] = new_list();
		for (int j = 0; j < N; j++)
		{
			weights[i][j] = 0;
		}
	}
	// Ввод системы дорог
	for (int i = 0; i < M; i++)
	{
		char temp[100];
		fscanf(f, "%s", temp);
		int city1 = getCity(city, &cityN, temp);
		fscanf(f, "%s", temp);
		int city2 = getCity(city, &cityN, temp);
		int s, p;
		fscanf(f, "%d %d", &s, &p);
		push(G[city1], city2);
		push(G[city2], city1);
		if (!weights[city1][city2] || weights[city1][city2] > s + p)
		{
			weights[city1][city2] = weights[city2][city1] = s + p;
		}
	}
	// Остальные данные
	char _A[100], _B[100];
	fscanf(f, "%s %s", _A, _B);
	int A = getCity(city, &cityN, _A);
	int B = getCity(city, &cityN, _B);

	rewind(f);
	graph_build(f, g);
	// Вычисление и вывод результата
	printMinimalPathway(G, N, weights, city, A, B);
	printf("\n");
	return 0;
}