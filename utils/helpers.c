#include <stdio.h>

int esMayus(char c)
{
    if (c >= 65 && c <= 90)
        return 1;

    return 0;
}

int get_quantity_files(FILE *fp)
{
    char caracter;

    int quantity_files = 0;
    while ((caracter = fgetc(fp)) != EOF)
    {
        if (caracter == '\n')
        {
            quantity_files++;
        }
    }

    return quantity_files;
}
