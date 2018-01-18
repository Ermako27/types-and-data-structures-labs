#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timegen.h"

unsigned long long tick(void)
{
 unsigned long long d;
 __asm__ __volatile__ ("rdtsc" : "=A" (d) );
 return d;
}