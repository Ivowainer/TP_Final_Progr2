#include <stdio.h>
#include "./utils/generate_text_files_name.c"
#include "./utils/helpers.c"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Por favor, ingresa un argumento valido\n");
        return -1;
    }

    /* 1. Llama a generate_text_files_name y apertura de archivo */
    if (generate_text_files_name(argv[1]) == -1)
    {
        printf("No existe el directorio: Textos/%s\n", argv[1]);
        return -1;
    }

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