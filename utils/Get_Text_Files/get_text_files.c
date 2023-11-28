void get_text_files(char *name);

void get_text_files(char name[])
{
    char command[100];

    sprintf(command, "cd Textos/%s && ls > ./text_files.txt", name);
    system(command);
}