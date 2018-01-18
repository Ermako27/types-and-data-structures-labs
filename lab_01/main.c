/*
Вариант 5, условие задачи приведено в соответствующем файле по варианту.

Первая лабораторная работа в курсе тисда, долго спорил с преподавателем на счет правильности поставленного условия, и соответствия моей реализации этому условию, потому много переделок, программа была оттестирована максимально полно, но некоторые тесты не проходят как раз по причине многочсленных переделок и подгонок(сроки как никак :) ), но если закрыть на них глаза лаба выполнена сравнительно не дурно для первой в году и в курсе.

P.S. Для будущего меня от меня на момент января 2018 года: учи мат часть подробнее и, ради всего святого, не лепи все в один файл - это ужасно.

*/




﻿#include <stdio.h>
#include <math.h>
#include <ctype.h>


#define OK 0
#define OVERMANT -1
#define OVERPOR -2
#define OVERFLOW -3
#define INPUT_ERR -4
#define EMPTY_INPUT -5

void print_mass(char a[], int size) // функция печати массива
{
    for (int i = 0; i < size; i++)
        printf("%c", a[i]);
    printf("\n");
}


int input(char *mantisa, char *poradok_m, int *poradok, int *m_count, int *count_por,char *znak, char *znak_p, int *out)
{
    int emp = 0;
    char ch;
    int j = 0, E_flag = 0, zero_flag = 0, dot_flag = 0;
    *m_count = 0;
    *count_por = 0;
    *poradok = 0;
    int i = 0;
    *out = 0;
    while ((ch = getchar()) != '\n' )
    {
        emp++;

        if (isalpha(ch) && ch != 'E')
            return INPUT_ERR;

        if (ch != '.' && ch != 'E' && E_flag == 0)
        {

            if (i == 0 && ch == '0')
            {
                zero_flag = 1;
            }
            else
                zero_flag = 0;
            if (zero_flag == 0)
            {
                //printf("%c\n",ch);
                *(mantisa + *m_count) = ch;
                if (ch != '+' && ch != '-')
                    *m_count += 1;
                else if (ch == '+' || ch == '-')
                    *znak = ch;
            }
            i++;


        }
        else if (ch == '.')
        {
            dot_flag = 1;
            *poradok = *m_count;
        }
        else if (ch == 'E')
        {
            *out = 1;
            E_flag = 1;
        }

        if (ch == '+' || ch == '-')
        {
            *znak_p = ch;
            continue;
        }

        if (E_flag == 1 && ch != 'E')
        {
            *(poradok_m + j) = ch;
            j++;
            *count_por += 1;
        }
        if (dot_flag == 0 && E_flag == 0)
            *poradok = *m_count;
    }

    if (i > 31)
        return OVERMANT;
    else if (*count_por > 5 || *poradok > 99999 || *poradok < -99999)
        return OVERPOR;
    else if (emp == 0)
        return EMPTY_INPUT;
    else
        return OK;
}



int multiply(int *res, char *mantisa_1, char *mantisa_2,int m_count_1, int m_count_2)
{
    int decimal; // результат умножение цифры на цифру
    int div = 0; // целая часть
    int new_dec = 0; // остаток
    int i;
    for (i = 0; i < 32; i++)
    {
        res[i] = 0;
    }
// массивы m_count_1 и m_count_2 - интовские массивы числа
    int m_int_1[m_count_1];
    for (int i = 0; i < m_count_1; i++)
    {
        m_int_1[i] = (mantisa_1[i] - '0');

    }
    int m_int_2[m_count_2];
    for (int j = 0; j < m_count_2; j++)
    {
        m_int_2[j] = (mantisa_2[j] - '0');
    }

    for (i = 0; i < m_count_2; i++)
    {
        for (int j = 0; j < m_count_1; j++)
        {
            decimal = m_int_1[m_count_1 - j - 1] * m_int_2[m_count_2-i - 1];
            if (decimal < 10)
            {
                if (res[j+i] + decimal < 10)
                {
                    res[j+i] += decimal;
                }
                else
                {
                    new_dec = (res[j+i] + decimal) % 10;
                    div = (res[j+i] + decimal) / 10;
                    res[j+i] = new_dec;
                    res[j+i+1] += div;  
                }
                div = 0;

            }
            else if (decimal >= 10)
            {
                new_dec = (res[j+i] + decimal) % 10;
                div = (res[j+i] + decimal) / 10;
                res[j + i + 1] += div;
                res[j + i] = new_dec;
            }
        }
    }
    if (res[31] != 0)
        return OVERFLOW;
    int q = 29;
    if (res[31] == 0 && res[30] != 0)
    {q--;
        if (res[30] < 5)
            res[30] = 0;
        else if (res[30] >= 5)
        {
            while (res[q] == 9)
            {
                res[q] = 0;
                q--;
            }
            if (res[q] < 9)
                res[q] += 1;
        }
        return OK;

    }
    else
        return OK;
}

void output(int *result, int por_1, int por_2, char znak_1, char znak_2, int sum,
            int E_flag_1,int E_flag_2, char *E_porm_1, char *E_porm_2, char znak_p_1, char znak_p_2,
            int c_1, int c_2)
{
    int p;
    int i,k;
    int e_por_1 = 0, e_por_2 = 0;
    int sum_por = por_1 + por_2;


    if (E_flag_1 == 1)
    {

        for (i = 0; i < c_1; i++)
        {
            k = (E_porm_1[i]-'0') * (int)pow(10,c_1 - i - 1);
            e_por_1 += k;
        }
        if (znak_p_1 == '-')
            e_por_1 *= -1;
    }
    if (E_flag_2 == 1)
    {
        for (i = 0; i < c_2; i++)
        {
            k = (E_porm_2[i]-'0') * (int)pow(10,c_2 - i - 1);
            e_por_2 += k;
        }
        if (znak_p_2 == '-')
            e_por_2 *= -1;
    }

    if (E_flag_1 == 1 && E_flag_2 == 1)
    {
        p = e_por_1 + e_por_2 + por_1 + por_2;
        if (znak_1 == znak_2)
        {
            printf("+0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);

        }
        else if (znak_1 != znak_2)
        {
            printf("-0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);
        }
    }

    else if (E_flag_1 == 1 && por_2 != -1)
    {
        p = e_por_1 + por_2 + por_1;
        if (znak_1 == znak_2)
        {
            printf("+0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);

        }
        else if (znak_1 != znak_2)
        {
            printf("-0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);
        }
    }

    else if (por_1 != -1 && E_flag_2 == 1)
    {
        p = por_1 + e_por_2 + por_1 + por_2;
        if (znak_1 == znak_2)
        {
            printf("+0.");

            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);

        }
        else if (znak_1 != znak_2)
        {
            printf("-0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", p);
        }
    }

    else if (E_flag_1 == 0 && E_flag_2 == 0)
    {
        if (znak_1 == znak_2)
        {
            printf("+0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", sum_por);

        }
        else if (znak_1 != znak_2)
        {
            printf("-0.");
            for (int i = sum; i >= 0; i--)
            {
                if ((i == sum && result[sum] == 0))
                    continue;
                printf("%d", result[i]);
            }
            printf("E%d", sum_por);
        }
    }

}

int main(void)
{
    int multiply_error;
    int por_1 = -1; // порядок при вводе с точкой или без
    int por_2 = -1;
    int m_count_1;// количество цифр в мантисе без знака
    int m_count_2;
    int count_por_1; // количество цифр в порядке при в вводе с Е
    int count_por_2;
    int input_error;
    char mant_1[40];// мантисса 1 числа
    char por_m_1[10]; // порядок при вводе с Е 1 числа
    char mant_2[40]; // мантисса 2 числа
    char por_m_2[10]; // порядок при вводе с Е 2 числа
    int result[32];
    char znak_1 = '+';
    char znak_2 = '+';
    char znak_p_1 = '+';
    char znak_p_2 = '+';
    int e_flag_1;
    int e_flag_2;



    printf("Input firsrt number: ");
    input_error = input(&mant_1[0], &por_m_1[0], &por_1, &m_count_1, &count_por_1,&znak_1,&znak_p_1, &e_flag_1);
    if (input_error == OVERMANT)
    {
        printf("Excess of mantissa!\n");
        return 0;
    }
    else if (input_error == OVERPOR)
    {
        printf("Excess of order!\n");
        return 0;
    }
    else if (input_error == INPUT_ERR)
    {
        printf("Incorret input.\n");
        return 0;
    }
    else if (input_error == EMPTY_INPUT)
    {
        printf("Empty input.\n");
        return 0;
    }

    printf("Input second number: ");
    input_error = input(&mant_2[0], &por_m_2[0], &por_2, &m_count_2, &count_por_2, &znak_2,&znak_p_2, &e_flag_2);

    if (input_error == OVERMANT)
    {
        printf("Excess of mantissa!\n");
        return 0;
    }
    else if (input_error == OVERPOR)
    {
        printf("Excess of order!\n");
        return 0;
    }
    else if (input_error == INPUT_ERR)
    {
        printf("Incorret input.\n");
        return 0;
    }
    else if (input_error == EMPTY_INPUT)
    {
        printf("Empty input.\n");
        return 0;
    }

    multiply_error = multiply(result,mant_1,mant_2,m_count_1,m_count_2);
    if (multiply_error == OVERFLOW)
    {
        printf("Excess of mantissa!\n");
        return 0;
    }
    int sum = m_count_1 + m_count_2;
    output(result,por_1,por_2,znak_1,znak_2,sum,e_flag_1,e_flag_2,por_m_1,por_m_2,znak_p_1,znak_p_2,count_por_1,count_por_2);
    printf("\n");


    return 0;
}
