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

/* add_text_to_output: String, String, FILE
Obtiene el nombre del artista pasado por parametros, el nombre de la canción y su archivo de salida.
Se encarga de iterar sobre el archivo filetxt (el de la canción) y poner los caracteres correspondientes
en el archivo de salida.

entrada: Fito_Paez, elamordespuesdelamor.txt, ./Entradas/Fito_Paez.txt; salida: el amor despues del amor tal vez...
*/
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