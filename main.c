#include <stdio.h>
#include "./utils/generate_text_files_name.c"
#include "./utils/helpers.c"

void add_text_to_output(char *name, char *filetxt, FILE *file_output)
{
    // a. Declaración de variable auxiliar path y archivos
    char path[100];

    sprintf(path, "./Textos/%s/%s", name, filetxt);
    FILE *file_input = fopen(path, "r");

    if (!file_input)
    {
        printf("No se pudo abrir el archivo de entrada");
        return;
    }

    /* b. Declaración de ciclo while para archivo del artista y variables auxiliares character, prev_character */
    char character, prev_character;
    while ((character = fgetc(file_input)) != EOF)
    {
        /* c. Condiciones para el parseo y sustitución de caracteres */
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
    /* d. Agregado de \n para evitar bugs y cierre de archivo */
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

    /* 1. Llama a generate_text_files_name y apertura de archivo */
    generate_text_files_name(argv[1]);

    FILE *text_files_name = fopen("./text_files_name.txt", "r");

    /* 2. Creación de archivo de salida, (Entradas/nombre.txt) */
    char path[100]; // String auxiliar para guardar rutas (se irá modificando a lo largo del programa)
    sprintf(path, "./Entradas/%s.txt", argv[1]);
    FILE *file_output = fopen(path, "w");

    /* 3. Declaración del bucle while por cada línea de text_files_name y
    ejecución de add_text_to_output por cada archivo recorrido (almacenado en path) */
    while ((fscanf(text_files_name, "%s", path)) != EOF)
    {
        add_text_to_output(argv[1], path, file_output); // <--
    }

    /* 4. Libreación de memoria, cierre de archvios y llamada al programa Python */
    fclose(file_output);
    fclose(text_files_name);

    sprintf(path, "python3 main.py %s", argv[1]);
    system(path);
    return 0;
}