#include "catch.h"

int* parser(int ac, char **av)
{
    if (ac < 5)
    {
        printf("NOT ENOUGH ARGUMENTS : (ex: ./catch.11 11 12 1 66)\n");
        return (NULL);
    }
    int *arr = malloc(16);
    if (!arr) return NULL;
    int i = 0;
    while (i < ac - 1)
    {
        arr[i] = atoi(av[i + 1]);
        i++;
    }
    i = 0;
    while (i < ac - 1)
        printf("%d\n", arr[i++]);
    return (arr);
}