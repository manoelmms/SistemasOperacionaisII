// Usando fstat()
// Escreva um programa que:
// Abra um arquivo com open().
// Use fstat(fd, &buf) para obter as informações.
// Mostre se o arquivo é regular, diretório ou link.
// Compare com stat() para verificar que o resultado é o mesmo.

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

    printf("Modo do arquivo (usando fstat): %o\n", fileStat.st_mode);
    if (S_ISREG(fileStat.st_mode)) {
        printf("O arquivo é um arquivo regular.\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("O arquivo é um diretório.\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("O arquivo é um link simbólico.\n");
    } else {
        printf("O arquivo é de outro tipo.\n");
    }

    struct stat statFile;
    if (stat(filename, &statFile) < 0) {
        perror("Erro ao usar stat");
        close(fd);
        return -1;
    }
    printf("Modo do arquivo (usando stat): %o\n", statFile.st_mode);
    if (S_ISREG(statFile.st_mode)) {
        printf("O arquivo é um arquivo regular.\n");
    } else if (S_ISDIR(statFile.st_mode)) {
        printf("O arquivo é um diretório.\n");
    } else if (S_ISLNK(statFile.st_mode)) {
        printf("O arquivo é um link simbólico.\n");
    } else {
        printf("O arquivo é de outro tipo.\n");
    }

    struct stat linkStat;
    if (lstat(filename, &linkStat) < 0) {
        perror("Erro ao usar lstat");
        close(fd);
        return -1;
    }

    printf("Modo do arquivo (usando lstat): %o\n", linkStat.st_mode);
    if (S_ISREG(linkStat.st_mode)) {
        printf("O arquivo é um arquivo regular.\n");
    } else if (S_ISDIR(linkStat.st_mode)) {
        printf("O arquivo é um diretório.\n");
    } else if (S_ISLNK(linkStat.st_mode)) {
        printf("O arquivo é um link simbólico.\n");
    } else {
        printf("O arquivo é de outro tipo.\n");
    }

    close(fd);
    return 0;
}
