#include <stdio.h>

int esMayus(char c)
{
    if (c >= 65 && c <= 90)
        return 1;

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *archivo_entrada, *archivo_salida;
    archivo_entrada = fopen("./Textos/Fito_Paez/elamordespuesdelamor.txt", "r");

    char caracter, prev_caracter;

    if (!archivo_entrada)
    {
        printf("No se pudo abrir el archivo");
        return 1;
    }

    archivo_salida = fopen("./Entradas/Fito_Paez.txt", "w");

    while ((caracter = fgetc(archivo_entrada)) != EOF)
    {
        if (esMayus(caracter))
            fputc(caracter + 32, archivo_salida);
        else if (caracter == '\n' && prev_caracter != '.')
            fputc(' ', archivo_salida);
        else if (caracter != '.' && caracter != ',')
        {
            fputc(caracter, archivo_salida);
        }

        prev_caracter = caracter;
    }

    fclose(archivo_entrada);
    fclose(archivo_salida);
    return 0;
}
