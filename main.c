#include <stdio.h>
#include "./utils/Text_Files_Name/generate_text_files_name.c"
#include "./utils/helpers.c"

void add_text_to_output(char *name, char *filetxt)
{
    char path[100];

    sprintf(path, "./Textos/%s/%s", name, filetxt);

    FILE *archivo_entrada, *archivo_salida;
    archivo_entrada = fopen(path, "r");

    char caracter, prev_caracter;

    if (!archivo_entrada)
    {
        printf("No se pudo abrir el archivo de entrada");
        return;
    }

    sprintf(path, "./Entradas/%s.txt", name);
    archivo_salida = fopen(path, "a");

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
    fputc('\n', archivo_salida);

    fclose(archivo_entrada);
    fclose(archivo_salida);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Por favor, ingresa un argumento valido\n");
        return 1;
    }

    /* PARTE DONDE CREA EL ARCHIVO */
    generate_text_files_name(argv[1]);

    FILE *fp = fopen("./utils/Text_Files_Name/text_files_name.txt", "r");

    char *stringAux = malloc(sizeof(char) * 100);
    char caracter;
    int i = 0;
    while ((caracter = fgetc(fp)) != EOF)
    {
        if (caracter != '\n')
        {
            stringAux[i] = caracter;
            i++;
        }
        else
        {
            add_text_to_output(argv[1], stringAux);
            stringAux = malloc(sizeof(char) * 100);
            i = 0;
        }
    }

    /* system("python3 main.py") */
    return 0;
}
