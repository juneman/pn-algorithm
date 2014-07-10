
#include <stdio.h>
#include <stdlib.h>

void print_array(int *a, int n)
{
    int i = 0;
    for (; i < n ; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void gen(int *a, int size, int pos)
{
    if (0 == pos)
        print_array(a, size);
    else {
        int i = 0;
        for (; i <= pos; i++)
        {
            int tmp = a[i];
            a[i] = a[pos];
            a[pos] = tmp;

            permgen(a,size, pos -1);

            tmp = a[i];
            a[i] = a[pos];
            a[pos] = tmp;
        }
    }
}

int main(int ac, char *av[])
{
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int count = sizeof(a)/ sizeof(a[0]);

    gen(a, count, count - 1);

    return 0;
}