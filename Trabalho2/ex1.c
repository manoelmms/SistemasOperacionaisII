// Crie um programa que receba uma lista de nomes de diretórios pela
// linha de comando e crie todos com permissões 0755.

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
        mode_t permissions = 0755;
        if (mkdir(filename, permissions) == -1)
        {
            perror("Não foi possível criar o diretório");
            return 1;
        }
        printf("Diretório %s criado com sucesso!\n", filename);
    }

    return 0;
}
