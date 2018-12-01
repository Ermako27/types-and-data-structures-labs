#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_func.h"
#include "tree.h"
#include "hash_func.h"

#define TRUE 1
#define OVERFLOW -1
#define TABLE 16 // размет таблицы при закрытом хешировании 


unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}

// int comp (const int *i, const int *j)
// {
// 	return *i - *j;
// }

// char* find_frq_word(char* unic_words[], int f, int unic_count, int all, int m, char *words[m])
// {
// 	for (int i = 0; i < count; i++)
// 	{
// 		frq = frequency(all, m, words,unic_words[i]);
// 		if (frq == f)
// 		{
// 			return unic_words[i];
// 		}
// 	}

// }




int main(void)
{
	//int test[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	char enter;
	int menu = TRUE;

	int flag = 0;
	int t = 0, pt = 0, pf = 0;
	int new_unic;
	int cmp_count, average_cmp = 0; // количество сравнений обычного дерева
	int cmp_count_avl, average_avl_cmp = 0; // количество сравнений авл
	int size1,size2,size3,size4; // замеры памяти
	int average_size1 = 0, average_size2 = 0, average_size3 = 0, average_size4 = 0; // средние замеры памяти
	int height = -5; // высота дерева

// Замеры времени
	unsigned long long not_balanced_start, not_balanced_end, first, average_not_balanced = 0;
	unsigned long long balanced_start, balanced_end, second, average_balanced = 0;
	unsigned long long open_hash_start, open_hash_end, third, average_open = 0;
	unsigned long long close_hash_start, close_hash_end, fourth, average_close = 0;




	Node *root = NULL;
	Node *AVL_root = NULL;
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
	FILE *g = fopen("not_balanced.dot", "w");
	FILE *h = fopen("balanced.dot", "w");


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


	Hash *hash_table[unic_count]; // таблица методом цепочек (открытая адресация)
	Hash *find_node;
	table_init(unic_count, hash_table);
	int hash_index; // значение хэш функции
	int open_hash_search_cmp, average_open_cmp = 0; // количество сравнений, среднее количество сравнений

	char* close_table[TABLE];
	char* find_close_node;
	char* find_word;
	close_table_init(close_table, TABLE);
	int close_hash_search_cmp, average_close_cmp = 0; // количетсво сравнений, среднее количество сравнений
	int close_insert_error; // ошибка переполнения хэша




// создание обычного дерева
	for (int i = 0; i < unic_count; i++)
	{
		frq = frequency(count,m,words,unic_words[i]);
		// frq_array[i] = frq;
		printf("word: %s count: %d\n", unic_words[i], frq);
		insert(&root, frq, unic_words[i]);
	}


// создание АВЛ дерева
	for (int i = 0; i < unic_count; i++)
	{
		frq = frequency(count,m,words,unic_words[i]); // посчитал ключ 
		AVL_root = insert_balance(AVL_root, frq, unic_words[i]); // вставил элемент
	}


// создание хэш таблицы с методом цепочек

	for (int i = 0; i < unic_count; i++)
	{
		frq = frequency(count,m,words,unic_words[i]);
		hash_index = func(frq, unic_count);
		hash_insert(&hash_table[hash_index], unic_words[i]);
	}

	printLinkedList(hash_table[7]);

// создание хэш таблицы с открытой адресацией
	for (int i = 0; i < unic_count; i++)
	{
		frq = frequency(count,m,words,unic_words[i]);
		close_insert_error = close_hash_insert(close_table, unic_words[i], TABLE, frq);
		if (close_insert_error == OVERFLOW)
		{
			printf("Хэш переполнен\n");
		}

	}





	printf("Дерево уже построено по заданному в программе файле.\n");
	printf("Вы можете работать с ним с помощью следующих команд.\n");


	while (menu)
	{
		printf("\n");
		printf("--------------------------------------------------\n");
        printf("1 - Талица результатов замеров поиска 1-го слова.|\n");
        printf("2 - Таблица средних значений поиска.             |\n");
        printf("3 - Вывод несбалансированного дерева.            |\n");
        printf("4 - Вывод сбалансированного дерева.              |\n");
        printf("5 - Вывод хеш таблицы (закрытая адресация).      |\n");
        printf("6 - Вывод хэш таблицы (открытая адресация)       |\n");
        // printf("6 - Поиск в несбалансированном дереве.           |\n");
        // printf("7 - Поиск в сбалансированном дереве.             |\n");
        // printf("8 - Поиск в хэш таблице (открытая адресация).    |\n");
        // printf("9 - Поиск в хэш таблице (закрытая адресация).    |\n");
        // printf("5 - Прямой (pre-order) обход.                    |\n");
        // printf("6 - Симметричный или поперечный (in-order) обход.|\n");
        // printf("7 - В обратном порядке (post-order).             |\n");
        // printf("8 - Печать дерева в виде графа graphviz.         |\n");
        // printf("9 - Печать дерева по уровням в терминале.        |\n");
        // printf("0 - завершение работы.                           |\n");
        printf("--------------------------------------------------\n");
        printf("\n\n>>>");

        if (scanf("%d", &menu) == 0 || menu > 9	 || menu < 0)
        {
            printf("Incorrect input!!!\n");
            break;
        }

        if (menu == 1) 
        {
        	printf("Введите слово, которое хотите найти: ");
        	scanf("%s", ptrs_find_tree[pt]);
        	frq = frequency(count,m,words, ptrs_find_tree[pt]);

        	not_balanced_start = tick();
        	knot = getNodeByValue(root, frq, ptrs_find_tree[pt], &cmp_count);
        	not_balanced_end = tick();
        	first = not_balanced_end - not_balanced_start;
        	size1 = unic_count*sizeof(Node);
           // printf("SIZE: %lu\n", sizeof(Node));


        	balanced_start = tick();
        	knot = getNodeByValue(AVL_root, frq, ptrs_find_tree[pt], &cmp_count_avl);
        	balanced_end = tick();
        	second = balanced_end - balanced_start;
        	size2 = size1;

        	hash_index = func(frq, unic_count);
        	open_hash_start = tick();
        	find_node = hash_search(hash_table[hash_index], ptrs_find_tree[pt],&open_hash_search_cmp);
        	open_hash_end = tick();
        	third = open_hash_end - open_hash_start;
        	size3 = unic_count * sizeof(Hash);

            //printf("SIZE_HASH: %lu\n", sizeof(Hash));
        	close_hash_start = tick();
        	find_word = close_hash_search(close_table, ptrs_find_tree[pt], TABLE, frq, &close_hash_search_cmp);
        	close_hash_end = tick();
        	fourth = close_hash_end - close_hash_start;
        	size4 = TABLE * sizeof(char);

        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|              |   Обычное дерево   |     АВЛ     |   Метод цепочек   |   Закрытая адресация   |\n");
        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|     Время    |        %5llu       |    %5llu    |       %5llu       |         %5llu          |\n",
        		first, second,third,fourth);
        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|     Память   |      %5d         |    %5d    |       %5d       |         %5d          |\n",
        		size1,size2,size3,size4);
        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|   Сравнения  |      %5d         |    %5d    |       %5d       |         %5d          |\n",
        		cmp_count,cmp_count_avl,open_hash_search_cmp,close_hash_search_cmp);
        	printf("------------------------------------------------------------------------------------------------\n");
        	pt++;
        }

        if (menu == 2)
        {
        	for (int i = 0; i < unic_count; i++)
        	{
        		frq = frequency(count,m,words, unic_words[i]);

        		not_balanced_start = tick();
        		knot = getNodeByValue(root, frq, unic_words[i], &cmp_count);
        		not_balanced_end = tick();
        		first = not_balanced_end - not_balanced_start;
        		//printf("NOT AVL: %llu\n", first);
        		size1 = unic_count*sizeof(Node);

        		average_not_balanced += first;
        		average_size1 += size1;
        		average_cmp += cmp_count;



        		balanced_start = tick();
        		knot = getNodeByValue(AVL_root, frq, unic_words[i], &cmp_count_avl);
        		balanced_end = tick();
        		second = balanced_end - balanced_start;

        		printf("AVL| word: %s time %llu\n", unic_words[i], second);
        		size2 = size1;

        		average_balanced += second;
        		average_size2 += size2;
        		average_avl_cmp += cmp_count_avl;


        		hash_index = func(frq, unic_count);
        		open_hash_start = tick();
        		find_node = hash_search(hash_table[hash_index], ptrs_find_tree[pt],&open_hash_search_cmp);
        		open_hash_end = tick();
        		third = open_hash_end - open_hash_start;
        		size3 = unic_count * sizeof(Hash);

        		average_open += third;
        		average_size3 += size3;
        		average_open_cmp += open_hash_search_cmp;

        		close_hash_start = tick();
        		find_word = close_hash_search(close_table, unic_words[i]	, TABLE, frq, &close_hash_search_cmp);
        		close_hash_end = tick();
        		fourth = close_hash_end - close_hash_start;
        		size4 = TABLE * sizeof(char);


        		average_close += fourth;
  
        		average_size4 += size4;
        		average_close_cmp += close_hash_search_cmp;
        	}

        	average_not_balanced /= unic_count;
        	average_balanced /= unic_count;
        	average_open /= unic_count;
        	average_close /= unic_count;

        	average_size1 /= unic_count;
        	average_size2 /= unic_count;
        	average_size3 /= unic_count;
        	average_size4 /= unic_count;

        	average_cmp /= unic_count;
        	average_avl_cmp /= unic_count;
        	average_open_cmp /= unic_count;
        	average_close_cmp /= unic_count;

        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|              |   Обычное дерево   |     АВЛ     |   Метод цепочек   |   Закрытая адресация   |\n");
        	printf("------------------------------------------------------------------------------------------------\n");

        	printf("|     Время    |        %5llu       |    %5llu    |       %5llu       |         %5llu          |\n",
        		average_not_balanced, average_balanced,average_open,average_close);
        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|     Память   |      %5d         |    %5d    |       %5d       |         %5d          |\n",
        		average_size1,average_size2,average_size3,average_size4);
        	printf("------------------------------------------------------------------------------------------------\n");
        	printf("|   Сравнения  |      %5d         |    %5d    |       %5d       |         %5d          |\n",
        		average_cmp,average_avl_cmp,average_open_cmp,average_close_cmp);
        	printf("------------------------------------------------------------------------------------------------\n");
        }

        if (menu == 3)
        {
        	bst_print_dot(root,g);
         	fclose(g);
        }

        if (menu == 4) 
        {	
        	bst_print_dot(AVL_root,h);
         	fclose(h);
        }

        if (menu == 5)
        {
        	for (int i = 0; i < TABLE; i++)
        	{
        		if (close_table[i] != NULL)
        			printf("%s | ", close_table[i]);
        		else
        			printf("NULL | ");
        	}
        }

        if (menu == 6)
        {
        	// for (int i = 0; i < unic_count; i++)
        	// {
        	// 	if (close_table[i] != NULL)
        	// 	{
        	// 		printf("%d: ", i);
        	// 		printLinkedList(hash_table[i]);
        	// 	}
        	// 	else
        	// 		printf("%d: NULL\n", i);
        	// }

        	for (int i = 0; i < unic_count; i++)
        	{
        		printf("%d: ", i);
        		printLinkedList(hash_table[i]);
        	}

        }


   //      if (menu == 6)
   //      {
   //      	printf("Введите слово, которое хотите найти: ");
   //      	scanf("%s", ptrs_find_tree[pt]);
   //      	frq = frequency(count,m,words,ptrs_find_tree[pt]);

   //      	not_balanced_start = tick();
   //      	knot = getNodeByValue(root, frq, ptrs_find_tree[pt], &cmp_count);
   //      	not_balanced_end = tick();
			// if (knot != NULL)
			// {
			// 	printf("Найденное слово: %s количество сравнений %d\n", knot->word, cmp_count + 1);
			// 	printf("Время %llu\n", (not_balanced_end - not_balanced_start));
			// }
			// else
			// {
			// 	printf("Время %llu\n", (not_balanced_end - not_balanced_start));
			// 	printf("Слово не найдено!\n");
				
			// }
			// pt++;
   //      } 

   //      if (menu == 7)
   //      {
   //      	printf("Введите слово, которое хотите найти: ");
   //      	scanf("%s", ptrs_find_tree[pt]);
   //      	frq = frequency(count,m,words,ptrs_find_tree[pt]);

   //      	balanced_start = tick();
   //      	knot = getNodeByValue(AVL_root, frq, ptrs_find_tree[pt], &cmp_count_avl);
   //      	balanced_end = tick();
			// if (knot != NULL)
			// {
			// 	printf("Найденное слово: %s количество сравнений %d\n", knot->word, cmp_count_avl + 1);
			// 	printf("Время АВЛ %llu\n", (balanced_end - balanced_start));
			// }
			// else
			// {
			// 	printf("Время %llu\n", (balanced_end - balanced_start));
			// 	printf("Слово не найдено!\n");
				
			// }
			// pt++;

   //      }

        // if (menu == 8)
        // {
        // 	printf("Введите слово, которое хотите найти: ");
        // 	scanf("%s", ptrs_find_tree[pt]);
        // 	frq = frequency(count,m,words,ptrs_find_tree[pt]);
        // 	hash_index = func(frq, unic_count);
        // 	open_hash_start = tick();
        // 	find_node = hash_search(hash_table[hash_index],ptrs_find_tree[pt],&open_hash_search_cmp);
        // 	open_hash_end = tick();

        // 	if(find_node != NULL && hash_index != 0) 
        // 	{
        // 		printf("Найденное слово: %s количество сравнений %d\n", find_node->word, open_hash_search_cmp);
        // 		printf("Время поиска в открытом хэше: %llu\n", open_hash_end - open_hash_start);
        // 	}
        // 	else 
        // 	{
        // 		printf("Слово не найдено\n");
        // 		printf("Время: %llu\n", open_hash_end - open_hash_start);
        // 	}

        // }

        // if (menu == 9)
        // {
        // 	printf("Введите слово, которое хотите найти: ");
        // 	scanf("%s", ptrs_find_tree[pt]);
        // 	frq = frequency(count,m,words,ptrs_find_tree[pt]);
        // 	close_hash_start = tick();
        // 	find_word = close_hash_search(close_table, ptrs_find_tree[pt], TABLE, frq, &close_hash_search_cmp);
        // 	close_hash_end = tick();

        // 	if(find_word != NULL) 
        // 	{
        // 		printf("Найденное слово: %s количество сравнений %d\n", find_word, close_hash_search_cmp);
        // 		printf("Время поиска в закрытом хэше: %llu\n", close_hash_end - close_hash_start);
        // 	}
        // 	else 
        // 	{
        // 		printf("Слово не найдено\n");
        // 		printf("Время: %llu\n", close_hash_end - close_hash_start);
        // 	}
        // 	pt++;

        // }
    }
}

















   //      	printf("Введите слово, которое хотите найти: ");
   //      	scanf("%s", ptrs_find_tree[pt]);
   //      	frq = frequency(count,m,words,ptrs_find_tree[pt]);

   //      	tree_find_start = tick();
   //      	knot = getNodeByValue(root, frq, ptrs_find_tree[pt], &cmp_count);
   //      	tree_find_end = tick();
			// if (knot != NULL)
			// {
			// 	printf("Найденное слово: %s количество сравнений %d\n", knot->word, cmp_count + 1);
			// 	printf("Время %llu\n", (tree_find_end - tree_find_start) / 5);
			// }
			// else
			// {
			// 	printf("Время %llu\n", (tree_find_end - tree_find_start) / 5);
			// 	printf("Слово не найдено!\n");
			// }
        

//         if (menu == 4)
//         {
//         	printf("Введите слово, которое хотите найти: ");
//         	scanf("%s", ptrs_find_file[pf]);

//         	file_find_start = tick();
//         	for (int i = 0; i < count; i++)
//         	{
//         		if (strcmp(words[i], ptrs_find_file[pf]) == 0)
//         		{
//         			printf("Найденное слово: %s количество сравнений %d \n", ptrs_find_file[pf], i + 1);
//         			flag = 1;
//         			break;
//         		}
//         	}
//         	file_find_end = tick();
//         	printf("Время %llu\n", (file_find_end - file_find_start) / 5);

//         	if (flag == 0)
//         	{
//         		printf("Слово не найдено!\n");
// 				int choice_t;
// 				printf("Хотите добавить это слово в дерево и в файл? \n");
// 				printf("1 - Добавить.\n");
// 				printf("2 - Не добавлять.\n");
// 				printf("\n\n>>>");
// 				scanf("%d",&choice_t);
// 				if (choice_t == 1)
// 				{
// 					f = fopen("test.txt", "a");
// 					ptrs[t] = ptrs_find_file[pf];
// 					fprintf(f, "\n%s", ptrs[t]);
// 					printf("\nCлово добавлено!\n");
// 					fclose(f);

// 					words[count] = ptrs[t];
// 					count++;

//       				new_unic = unic_find(unic_count,unic_words,ptrs[t]);
//       				if (new_unic == 0)
//       				{
//       						unic_words[unic_count] = ptrs[t];
//       						unic_count++;
//       				}

//       				t++;
//       				pf++;

//       				root = NULL;
// 					for (int i = 0; i < unic_count; i++)
// 					{
// 						frq = frequency(count,m,words,unic_words[i]);
// 						insert(&root, frq, unic_words[i]);
// 					}
// 				}
//         	}
//         	flag = 0;
//         }
// }

 //        if (menu == 5)
 //        {
 //        	printf("Прямой обход: ");
	// 		preOrderTravers(root, printNode, NULL);
 //        }

 //        if (menu == 6)
 //        {
 //        	printf("Симметричный обход: ");
	//  		inOrderTravers(root, printNode, NULL);
 //        }

 //        if (menu == 7)
 //        {
 //        	printf("Обратный обход: ");
	//  		postOrderTravers(root, printNode, NULL);
 //        }

 //        if (menu == 8)
 //        {
 //        	bst_print_dot(root,g);
 //        	fclose(g);
 //        }

 //        if (menu == 9)
 //        {
 //        	printTree(root, "root", 0);
 //        }

	// } 



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
// 	// 	printf("%s \n", words[i]);
// 	// }
// }


















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
