#include <stdlib.h>

void generate_text_files_name(char *name);

/* Recibe como parametro el nombre del directorio al que debemos acceder
dentro de Textos/ luego, ejecuta el comando ls y guarda en utils/Text_Files_Name/ un archivo llamado
text_files_name.txt */
void generate_text_files_name(char name[])
{
    char command[100];

    sprintf(command, "cd Textos/%s && ls > ../../text_files_name.txt", name);
    system(command);
}