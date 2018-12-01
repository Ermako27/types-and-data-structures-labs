#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_func.h"
#include "tree.h"

#define TRUE 1


unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}


int main(void)
{
	int menu = TRUE;

	int flag = 0;
	int t = 0, pt = 0, pf = 0;
	int new_unic;
	int cmp_count;


	unsigned long long tree_find_start, tree_find_end;
	unsigned long long file_find_start, file_find_end;




	Node *root = NULL;
	Node *knot;


	char in[30];
	char out[30];
	char find[30];
	char find_file[30];

	char *ptr_in = in;
	char *ptr_find_file = find_file;
	char *ptr_find = find;
	char *ptr_out = out;
	int m = 30;
	int count, unic_count, frq;
	int *lens;
	char **words;
	FILE *f = fopen("test.txt", "r");
	FILE *g = fopen("graphviz.dot", "w");


	count = word_count(f); // количество слов в тексте
	char *unic_words[200]; // массив уникальных слов
	char **ptrs = allocate_matrix_rows(count);
	char **ptrs_find_tree = allocate_matrix_rows(count);
	char **ptrs_find_file = allocate_matrix_rows(count);
	rewind(f);
	words = allocate_matrix_rows(count);
	fill_text(count,m,words,f);
	unic_count = create_unic_words(count, m, words, unic_words);
	fclose(f);


	for (int i = 0; i < unic_count; i++)
	{
		frq = frequency(count,m,words,unic_words[i]);
		insert(&root, frq, unic_words[i]);
	}


	printf("Дерево уже построено по заданному в программе файле.\n");
	printf("Вы можете работать с ним с помощью следующих команд.\n");


	while (menu)
	{
		printf("\n");
		printf("--------------------------------------------------\n");
        printf("1 - Добавить узел в дерево.                      |\n");
        printf("2 - Удалить узел из дерева.                      |\n");
        printf("3 - Поиск по дереву.                             |\n");
        printf("4 - Поиск по файлу.                              |\n");
        printf("5 - Прямой (pre-order) обход.                    |\n");
        printf("6 - Симметричный или поперечный (in-order) обход.|\n");
        printf("7 - В обратном порядке (post-order).             |\n");
        printf("8 - Печать дерева в виде графа graphviz.         |\n");
        printf("9 - Печать дерева по уровням в терминале.        |\n");
        printf("0 - завершение работы.                           |\n");
        printf("--------------------------------------------------\n");
        printf("\n\n>>>");

        if (scanf("%d", &menu) == 0 || menu > 9	 || menu < 0)
        {
            printf("Incorrect input!!!\n");
            break;
        }

        if (menu == 1)
        {

        	f = fopen("test.txt", "a");
        	printf("Введите слово: ");
			scanf("%s", ptrs[t]);
			printf("\nCлово добавлено!\n");
			fprintf(f, "\n%s", ptrs[t]);
			fclose(f);

			words[count] = ptrs[t];
			count++;


      		new_unic = unic_find(unic_count,unic_words,ptrs[t]);

      		if (new_unic == 0)
      		{
      			unic_words[unic_count] = ptrs[t];
      			unic_count++;
      		}

      		t++;

      		root = NULL;
			for (int i = 0; i < unic_count; i++)
			{
				frq = frequency(count,m,words,unic_words[i]);
				insert(&root, frq, unic_words[i]);
			}
        }

        if (menu == 2) // не удаляется корень
        {
        	printf("Введите слово, которое хотите удалить: ");
        	scanf("%s", out);
        	frq = frequency(count,m,words,ptr_out);
        	deleteValue(root, frq, ptr_out);
        }

        if (menu == 3) 
        {

        	printf("Введите слово, которое хотите найти: ");
        	scanf("%s", ptrs_find_tree[pt]);
        	frq = frequency(count,m,words,ptrs_find_tree[pt]);

        	tree_find_start = tick();
        	knot = getNodeByValue(root, frq, ptrs_find_tree[pt], &cmp_count);
        	tree_find_end = tick();
			if (knot != NULL)
			{
				printf("Найденное слово: %s количество сравнений %d\n", knot->word, cmp_count + 1);
				printf("Время %llu\n", (tree_find_end - tree_find_start) / 5);
			}
			else
			{
				printf("Время %llu\n", (tree_find_end - tree_find_start) / 5);
				printf("Слово не найдено!\n");
				int choice_t;
				printf("Хотите добавить это слово в дерево и в файл? \n");
				printf("1 - Добавить.\n");
				printf("2 - Не добавлять.\n");
				printf("\n\n>>>");
				scanf("%d",&choice_t);
				if (choice_t == 1)
				{
					f = fopen("test.txt", "a");
					ptrs[t] = ptrs_find_tree[pt];
					fprintf(f, "\n%s", ptrs[t]);
					printf("\nCлово добавлено!\n");
					fclose(f);

					words[count] = ptrs[t];
					count++;


      				new_unic = unic_find(unic_count,unic_words,ptrs[t]);
      				if (new_unic == 0)
      				{
      						unic_words[unic_count] = ptrs[t];
      						unic_count++;
      				}

      				t++;
      				pt++;

      				root = NULL;
					for (int i = 0; i < unic_count; i++)
					{
						frq = frequency(count,m,words,unic_words[i]);
						insert(&root, frq, unic_words[i]);
					}
				}
			}
        }

        if (menu == 4)
        {
        	printf("Введите слово, которое хотите найти: ");
        	scanf("%s", ptrs_find_file[pf]);

        	file_find_start = tick();
        	for (int i = 0; i < count; i++)
        	{
        		if (strcmp(words[i], ptrs_find_file[pf]) == 0)
        		{
        			printf("Найденное слово: %s количество сравнений %d \n", ptrs_find_file[pf], i + 1);
        			flag = 1;
        			break;
        		}
        	}
        	file_find_end = tick();
        	printf("Время %llu\n", (file_find_end - file_find_start) / 5);

        	if (flag == 0)
        	{
        		printf("Слово не найдено!\n");
				int choice_t;
				printf("Хотите добавить это слово в дерево и в файл? \n");
				printf("1 - Добавить.\n");
				printf("2 - Не добавлять.\n");
				printf("\n\n>>>");
				scanf("%d",&choice_t);
				if (choice_t == 1)
				{
					f = fopen("test.txt", "a");
					ptrs[t] = ptrs_find_file[pf];
					fprintf(f, "\n%s", ptrs[t]);
					printf("\nCлово добавлено!\n");
					fclose(f);

					words[count] = ptrs[t];
					count++;

      				new_unic = unic_find(unic_count,unic_words,ptrs[t]);
      				if (new_unic == 0)
      				{
      						unic_words[unic_count] = ptrs[t];
      						unic_count++;
      				}

      				t++;
      				pf++;

      				root = NULL;
					for (int i = 0; i < unic_count; i++)
					{
						frq = frequency(count,m,words,unic_words[i]);
						insert(&root, frq, unic_words[i]);
					}
				}
        	}
        	flag = 0;
        }

        if (menu == 5)
        {
        	printf("Прямой обход: ");
			preOrderTravers(root, printNode, NULL);
        }

        if (menu == 6)
        {
        	printf("Симметричный обход: ");
	 		inOrderTravers(root, printNode, NULL);
        }

        if (menu == 7)
        {
        	printf("Обратный обход: ");
	 		postOrderTravers(root, printNode, NULL);
        }

        if (menu == 8)
        {
        	bst_print_dot(root,g);
        	fclose(g);
        }

        if (menu == 9)
        {
        	printTree(root, "root", 0);
        }

	} 



	// for (int i = 0; i < unic_count; i++)
	// {
	// 	frq = frequency(count,m,words,unic_words[i]);
	// 	insert(&root, frq, unic_words[i]);
	// 	// printf("word: %s %d\n",unic_words[i], frq);
	// }


	// printTree(root, "root", 0);

	// for (int i = 0; i < unic_count; i++)
	// {
	// 	//frq = frequency(count,m,words,unic_words[i]);
	// 	//insert(&root, frq, unic_words[i]);
	// 	printf("word: %s\n",unic_words[i]);
	// }



	// printf("pre: ");
	// preOrderTravers(root, printNode, NULL);
	// printf("in: ");
	// inOrderTravers(root, printNode, NULL);
	// printf("post: ");
	// postOrderTravers(root, printNode, NULL);



	// deleteValue(root, 2, unic_words[3]);
	// printTree(root, "root", 0);

	// knot = getNodeByValue(root, 1, unic_words[3]);
	// if (knot != NULL)
	// 	printf("find word: %s\n", knot->word);
	// else
	// 	printf("No word in the text!\n");

	// for (int i = 0; i < count; i++)
	// {
	// 	printf("%s \n", words[i]);
	// }
}


















			// char *p = "qwer";
			// unic_words[50] = p;
			// printf("%s\n", unic_words[50]);













































			// for (int i = 0; i < count; i++)
			// {
			// 	printf("words: %s \n", words[i]);
			// }

			// f = fopen("test.txt", "r");
			// count = word_count(f); // количество слов в тексте
			// printf("count2: %d\n", count);
			// rewind(f);
			// fill_text(count,m,words,f);

			// for (int i = 0; i < count; i++)
			// {
			// 	printf("words: %s \n", words[i]);
			// }

			// unic_count = create_unic_words(count, m, words, unic_words);

			// for (int i = 0; i < unic_count; i++)
			// {
			// 	printf("unic_words: %s \n", unic_words[i]);
			// }

			// fclose(f);

			
			// // перестраиваем дерево с добавленным в файл словом
			// // printf("count2: %d \n", count);
			// // words = (char**)realloc(words,count + 1);
			// // printf("2\n");
			// // words[count] = ptr_in;
			// // printf("new word: %s 3\n", words[count]);
			// // count++;

			// // unic_count = create_unic_words(count, m, words, unic_words);
			// // printf("4\n");

			// // new_unic = unic_find(unic_count, unic_words, ptr_in);

			// // if (new_unic == 0)
			// // {
			// // 	unic_words = (char)realloc(unic_words, unic_count + 1);
			// // 	unic_words[unic_count] = ptr_in;
			// // 	unic_count++;
			// // }
