#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
Слайд 6
*/

void print_adr(int *a)
{
    printf("pointer %p\n", a);
}

int main(void)
{
    int *a = NULL;
    int n = 5;

    // Выделение памяти
    a = malloc(n * sizeof(int));

    printf("a %p\n", a);
    printf("a %p\n", a+5);

    if (a > a+5*sizeof(int))
        printf("!");

    // Проверка успешности выделения
    if (a == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return -1;
    }

    // Использование памяти

    for (int i = 0; i < 10; i++)
    {
        if (a+i*sizeof(int) < a+5*sizeof(int))
        {
            a[i] = i;
            printf("a[i] %p\n", a+i*sizeof(int));
            
        }
        else
            break;
        
    }

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    print_adr(a+4*sizeof(int));

    //printf("\n%d", a[6]);

    // Освобождение памяти
    free(a);

    return 0;
}
// int main(void)
// {
//     int *tmp1 = malloc(20*sizeof(int));
//     //printf("%p\n", tmp1);
//     printf("adress: %p\n", tmp1);
//      for (int i = 0; i < 30; i++)
//      {
//          tmp1[i] = i;
//          printf("%d\n",tmp1[i]);
//      }
//     //free(tmp1);



//     int *tmp2 = malloc(20*sizeof(int));
//     printf("addres: %p\n", tmp2);   
//     free(tmp2); 
//     return 0;

//     if (tmp2 == tmp1)
//         printf("!\n");
// }