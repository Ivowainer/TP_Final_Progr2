#include <stdlib.h>

int generate_text_files_name(char *name);

/* Recibe como parametro el nombre del directorio al que debemos acceder
dentro de Textos/ luego, ejecuta el comando ls y guarda en utils/Text_Files_Name/ un archivo llamado
text_files_name.txt */
int generate_text_files_name(char name[])
{
    char command[100];

    sprintf(command, "./Textos/%s", name);
    FILE *faux = fopen(command, "r");

    if (!faux)
    {
        return -1;
    }

    fclose(faux);

    sprintf(command, "cd Textos/%s && ls > ../../text_files_name.txt", name);
    system(command);

    return 1;
}