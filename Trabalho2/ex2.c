// Crie um programa que recebe vários nomes de diretórios e tenta removê-
// los com rmdir(), mostrando mensagem de sucesso ou erro para cada um.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> 

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nome_do_diretorio1> <nome_do_diretorio2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        if (rmdir(filename) == -1)
        {
            perror("Não foi possível remover o diretório");
            return 1;
        }
        printf("Diretório %s removido com sucesso!\n", filename);
    }

    return 0;
}
