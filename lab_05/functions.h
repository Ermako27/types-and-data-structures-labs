#ifndef __FUNCTIONS__H__

#define __FUNCTIONS__H__

void read_line(int *s, int n);

int zeros(int n, int *array);

int count_of_non_zero(int *data, int n);

int* ja_create(int *data, int n);

int* an_create(int *data, int *ja, int n);

int* ip_create(int *ja, int n, int none_zero);

int scalar_multiply(int *jb, int *an, int *bn, int *ip, int less);

void free_matrix_rows(int **data, int n);

int** allocate_matrix_rows(int n, int m);

int** allocate_matrix_rows_zero(int n, int m);

int** self_allocate_matrix_rows(int n, int m);

void zero_add(int n, int m, int *array[m],int zero);

void minus_add(int n, int m, int *array[m]);

void print_matrix(int n, int m, int *a[m]);

void transpon(int size1, int size2, int *array[size2]);

int** not_square_transpon(int size1, int size2, int *array[size2]);

#endif