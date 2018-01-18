#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int command = 0;
    char s[5];
    int num;
    int i = 0;
    char ch;
    char enter;

    while (command != -1)
    {
        printf("1 - char\n"); // меню
        printf("2 - number\n"); 
        printf("-1 - exit\n");

        printf("Input commad: ");
        scanf("%d", &command);

        if (command == 1)
        {
            fflush(stdin);  
            printf("input char: ");
            enter = getchar();
            while (ch = getchar() != '\n') 
                s[i] = ch;  
            printf("\n");
        }
        if (command == 2)
        {
            rewind(stdin);
            printf("input number: ");
            scanf("%d", &num);
            printf("\n");
        }
        if (command == -1)
            break;
    }

    printf("char: %c %c", s[0],s[1]);
    printf("number: %d\n", num);
}