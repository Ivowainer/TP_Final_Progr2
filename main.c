#include <stdio.h>
#include "./utils/Text_Files_Name/generate_text_files_name.c"
#include "./utils/helpers.c"

void add_text_to_output(char *name, char *filetxt, FILE *file_output)
{
    char path[100];

    /* Declaración de archivos */
    sprintf(path, "./Textos/%s/%s", name, filetxt);
    FILE *file_input = fopen(path, "r");

    char character, prev_character;

    if (!file_input)
    {
        /* printf("No se pudo abrir el archivo de entrada"); */
        return;
    }

    while ((character = fgetc(file_input)) != EOF)
    {
        if (esMayus(character))
            fputc(character + 32, file_output);
        else if (character == '\n' && prev_character != '.')
            fputc(' ', file_output);
        else if (character != '.' && character != ',')
        {
            fputc(character, file_output);
        }

        prev_character = character;
    }
    fputc('\n', file_output);

    fclose(file_input);
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

    FILE *text_files_name = fopen("./utils/Text_Files_Name/text_files_name.txt", "r");

    /* CREA EL ARCHIVO DE SALIDA (ENTRADAS) */
    char path[100];
    sprintf(path, "./Entradas/%s.txt", argv[1]);
    FILE *file_output = fopen(path, "w");

    char *stringAux = malloc(sizeof(char) * 100); // String auxiliar para guardar los nombres de los archivos
    stringAux[0] = '\0';
    char character;
    int i = 0;
    while ((character = fgetc(text_files_name)) != EOF)
    {
        if (character != '\n')
        {
            stringAux[i] = character;
            stringAux[i + 1] = '\0';
            i++;
        }
        else
        {
            add_text_to_output(argv[1], stringAux, file_output);

            free(stringAux);
            stringAux = malloc(sizeof(char) * 100);
            stringAux[0] = '\0';
            i = 0;
        }
    }

    fclose(file_output);

    sprintf(path, "python3 main.py %s", argv[1]);
    system(path);
    return 0;
}
