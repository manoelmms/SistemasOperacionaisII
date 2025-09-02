// Comparação entre stat() e lstat()
// Crie um link simbólico para um arquivo (ln -s arquivo.txt
// link.txt).
// Escreva um programa que:
// Use stat("link.txt") e mostre o tamanho do arquivo real.
// Use lstat("link.txt") e mostre o tamanho do link (não do alvo).
// Explique a diferença.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    struct stat fileStat;
    if (fstat(fd, &fileStat) < 0) {
        perror("Erro ao usar stat");
        close(fd);
        return -1;
    }
    printf("Tamanho do arquivo real (usando stat): %lld bytes\n", (long long)fileStat.st_size);

    struct stat linkStat;
    if (lstat(filename, &linkStat) < 0) {
        perror("Erro ao usar lstat");
        close(fd);
        return -1;
    }
    printf("Tamanho do link (usando lstat): %lld bytes\n", (long long)linkStat.st_size);

    close(fd);
    return 0;
}

// Diferença:
// A função stat() retorna informações sobre o arquivo real ao qual o link simbólico aponta,
// incluindo seu tamanho. Já a função lstat() retorna informações sobre o link simbólico em si,
// incluindo o tamanho do link, que geralmente é menor que o tamanho do arquivo real, no caso do teste 16 bytes.