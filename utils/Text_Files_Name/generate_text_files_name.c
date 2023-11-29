#include <stdlib.h>

void generate_text_files_name(char *name);

void generate_text_files_name(char name[])
{
    char command[100];

    sprintf(command, "cd Textos/%s && ls > ../../utils/Text_Files_Name/text_files_name.txt", name);
    system(command);
}