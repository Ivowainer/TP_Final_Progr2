#include <stdio.h>
#include "./utils/Text_Files_Name/generate_text_files_name.c"
#include "./utils/helpers.c"

void add_text_to_output(char *name, char *filetxt, FILE *archivo_salida)
{
    char path[100];

    /* Declaración de archivos */
    sprintf(path, "./Textos/%s/%s", name, filetxt);
    FILE *archivo_entrada = fopen(path, "r");

    char caracter, prev_caracter;

    if (!archivo_entrada)
    {
        /* printf("No se pudo abrir el archivo de entrada"); */
        return;
    }

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

    /* CREA EL ARCHIVO DE SALIDA (ENTRADAS) */
    char path[100];
    sprintf(path, "./Entradas/%s.txt", argv[1]);
    FILE *archivo_salida = fopen(path, "w");

    char *stringAux = malloc(sizeof(char) * 100); // String auxiliar para guardar los nombres de los archivos
    stringAux[0] = '\0';
    char caracter;
    int i = 0;
    while ((caracter = fgetc(fp)) != EOF)
    {
        if (caracter != '\n')
        {
            stringAux[i] = caracter;
            stringAux[i + 1] = '\0';
            i++;
        }
        else
        {
            add_text_to_output(argv[1], stringAux, archivo_salida);

            free(stringAux);
            stringAux = malloc(sizeof(char) * 100);
            stringAux[0] = '\0';
            i = 0;
        }
    }

    fclose(archivo_salida);

    sprintf(path, "python3 main.py %s", argv[1]);
    system(path);
    return 0;
}
