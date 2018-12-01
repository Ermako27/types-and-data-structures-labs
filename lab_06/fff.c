#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
	FILE *f = fopen("test.txt", "a");
	char a[30];
	printf("input: ");
	scanf("%s", a);
	fprintf(f, " %s", a);
	fclose(f);

}