// Usando stat() para informações de um arquivo
// Faça um programa que:
// Receba o nome de um arquivo.
// Use stat() para mostrar:
// Tamanho
// Número de links
// UID do dono
// Permissões de acesso (rwx)
// Última modificação (st_mtime formatada em data/hora)

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

    printf("Tamanho: %lld bytes\n", (long long)fileStat.st_size);
    printf("Número de links: %ld\n", (long)fileStat.st_nlink);
    printf("UID do dono: %d\n", (int)fileStat.st_uid);
    printf("Permissões de acesso: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-"); // Owner read
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-"); // Owner write
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-"); // Owner execute
    printf("\n");
    printf("Última modificação: %s", ctime(&fileStat.st_mtime));

    close(fd);
    return 0;
}