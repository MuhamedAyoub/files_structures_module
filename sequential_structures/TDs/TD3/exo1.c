#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
    srand(time(NULL));
    int x = rand();
    printf("this random val is %d", x);
    return 0;
}
