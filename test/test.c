#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include "../utils/helpers.c"

void test_esMayus()
{
    char test_char = 'A';
    assert(esMayus(test_char) == 1);
    test_char = 'b';
    assert(esMayus(test_char) == 0);
    test_char = 'c';
    assert(esMayus(test_char) == 0);
    test_char = '_';
    assert(esMayus(test_char) == 0);
}

void test_add_text_to_output(char *text, char *expected_text)
{
    // 1. Mkdir para test y crea un archivo de prueba con algunos datos
    FILE *f_input = fopen("./Textos/Test/test_input.txt", "w");
    fprintf(f_input, text);
    fclose(f_input);

    /* 2. Creación de output y llamada de add_text_to_output */
    FILE *f_output = fopen("./Entradas/Test.txt", "w");
    add_text_to_output("Test", "test_input.txt", f_output);
    fclose(f_output);

    /* 3. Obtiene data de Test.txt y lo pone en buff para comparar resultados */
    FILE *f_test = fopen("./Entradas/Test.txt", "r");
    char buff[255];
    char result[255] = "";

    while (fgets(buff, sizeof(buff), f_test) != NULL)
    {
        strcat(result, buff);
    }

    fclose(f_test);

    /* 4. Compara resultados */
    assert(strcmp(result, expected_text) == 0);
}

int main()
{

    system("cd ./Textos && mkdir Test");
    test_esMayus();
    test_add_text_to_output("Hola, buenos dias, que tal.\nMi nombre es Ivan\ny estoy probando texto", "hola buenos dias que tal\nmi nombre es ivan y estoy probando texto\n");
    test_add_text_to_output("Algo se detuvo en punto muerto\nY fue tan grande ese silencio, fue tan grande el desamor.\nRestos de un navio que encallaba", "algo se detuvo en punto muerto y fue tan grande ese silencio fue tan grande el desamor\nrestos de un navio que encallaba\n");
    test_add_text_to_output("De musica ligera\nNada nos libra\nNada mas queda", "de musica ligera nada nos libra nada mas queda\n");
    test_add_text_to_output("Vi pasar los autos de la ruta,\nvoy a volverme a mi casa.", "vi pasar los autos de la ruta voy a volverme a mi casa\n");

    printf("Todos los test pasaron\n");
    return 0;
}