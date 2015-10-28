#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    int a[8];
    printf("%d",sizeof(a));
    a[0] = 1;
    printf("%d",*a);
    printf("hi");

}

