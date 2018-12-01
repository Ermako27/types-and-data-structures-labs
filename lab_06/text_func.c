#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_func.h"

void free_matrix_rows(char **data, int n)
{
    for (int i = 0; i < n; i++)
       // free можно передать NULL
       free(data[i]);

    free(data);
}

char** allocate_matrix_rows(int n)
{
    char **data = calloc(200, sizeof(char*));
    if (!data)
        return NULL;

    for (int i = 0; i < 200; i++)
    {
        data[i] = malloc(30 * sizeof(char));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        }
    }
    return data;
}


void fill_text(int n, int m, char *text[m], FILE *f) // выделение слов в тексте
{
	int j = 0;
	int flag = 1;
	char ch;
	char signs[6] = "!.?- \n";
	for (int i = 0; i < n; i++)
	{
		while (fscanf(f,"%c", &ch) == 1)
		{
			if (strchr(signs, ch) == NULL)
			{
				text[i][j++] = ch;
				flag = 0;
			}
			else if (flag == 0) 
			{
				flag = 1;
				break;
			}

		}
		j = 0;
	}
}


int word_count(FILE *f) // подсчет количества слов в тексте
{
	char ch;
	int count = 0;
	while (fscanf(f, "%c", &ch) == 1)
	{
		if (ch == ' ' || ch == '\n')
		{
			count++;
		}
	}
	return count;
}


int create_unic_words(int n, int m, char *array[m], char *unic[]) // создание массива из уникальных слов
{
	int flag = 0;
	int k = 0;
	int unic_count = 0;
	for (int i = 0; i < n; i++)
	{
		// printf("i: %d\n", i);
		for (int j = 0; j < unic_count; j++)
		{
			// printf("j: %d\n", j);
			if (strcmp(array[i], unic[j]) == 0)
				flag = 1;
		}
		if (flag == 0)
		{
			unic[unic_count] = array[i];
			unic_count++;
		}
		flag = 0;
	}

	return unic_count;
}

int unic_find(int n, char *unic[], char *word)
{
	for(int i = 0; i < n; i++)
	{
		if (strcmp(unic[i], word) == 0)
			return 1;
	}
	return 0;
}


int frequency(int n, int m, char *array[m], char *word) // частота встречания одного слова в тексте
{
	int frq = 0;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(array[i], word) == 0)
			frq++;
	}
	return frq;
}

// int findinfile(FILE *f, char *word) // поиск слова в файле
// {

// }


// int main(void)
// {
// 	int m = 30;
// 	int count, unic_count, frq;
// 	int *lens;
// 	char **words;
// 	FILE *f = fopen("test.txt", "r");
// 	count = word_count(f);
// 	char *unic_words[count];
// 	rewind(f);
// 	words = allocate_matrix_rows(count);
// 	fill_text(count,m,words,f);
// 	unic_count = create_unic_words(count, m, words, unic_words);



// 	// for (int i = 0; i < unic_count; i++)
// 	// {
// 	// 	frq = frequency(count,m,words,unic_words[i]);
// 	// 	printf("word: %s %d\n",unic_words[i], frq);
// 	// }


// 	// for (int i = 0; i < count; i++)
// 	// {
// 	// 	printf("%s \n", words[i]);
// 	// }

// 	// for (int i = 0; i < count; i++)
// 	// {
// 	// 	printf("%d ", lens[i]);
// 	// }
// }












































// int* words_len(int count, FILE *f)
// {
// 	int *array = malloc(count * sizeof(int));
// 	char ch;
// 	int len = 0;
// 	int i = 0;
// 	char signs[6] = "!.?- \n";
// 	while (fscanf(f,"%c", &ch) == 1)
// 	{
// 		if (strchr(signs, ch) == NULL)
// 		{
// 			len++;
// 		}
// 		else
// 		{
// 			if (len != 0)
// 			{
// 				array[i++] = len;
// 				len = 0;
// 			}
// 		}
// 	}

// 	return array;
// }
 


// char** tokenize(FILE *f)
// {

// }
