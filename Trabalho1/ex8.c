// Tamanho e tipo de múltiplos arquivos (stat)
// Escreva um programa que:
// Receba vários nomes de arquivos como argumento.
// Para cada arquivo:
// Exiba tamanho
// Tipo (regular, diretório, link simbólico, etc.)
// Permissões

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo1> <nome_do_arquivo2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat fileStat;
        if (stat(filename, &fileStat) < 0) {
            perror("Erro ao usar stat");
            continue;
        }

        printf("Arquivo: %s\n", filename);
        printf("Tamanho: %lld bytes\n", (long long)fileStat.st_size);
        printf("Tipo: ");
        if (S_ISREG(fileStat.st_mode)) {
            printf("Arquivo regular\n");
        } else if (S_ISDIR(fileStat.st_mode)) {
            printf("Diretório\n");
        } else if (S_ISLNK(fileStat.st_mode)) {
            printf("Link simbólico\n");
        } else {
            printf("Outro tipo\n");
        }

        printf("Permissões: ");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-"); // Owner read
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-"); // Owner write
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-"); // Owner execute
        printf("\n\n");
    }

    return 0;
}