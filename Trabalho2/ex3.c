// Crie um programa que recebe um caminho relativo ou absoluto, muda para
// ele com chdir() e imprime o diretório atual com getcwd().

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 

int main(int argc, char *argv[]) 
{
    char *buffer;
    long path_max = 10000;

    if (argc < 2) 
    {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return 1;
    }
    const char *path = argv[1];
    if (chdir(path) == -1)
    {
        perror("Não foi possível mudar o diretório");
        return 1;
    }
    
    // Allocate memory for the buffer
    buffer = (char *)malloc(path_max * sizeof(char));
    if (buffer == NULL) 
    {
        perror("malloc error");
        return 1;
    }

    if(getcwd(buffer, path_max) == NULL)
    {
        perror("getcwd error");
    }

    printf("Diretório Atual: %s\n", buffer);
    return 0;
}
