// Contar bytes nulos (\0) em um arquivo com lseek()
// Faça um programa que:
// Abra um arquivo binário.
// Use lseek() para percorrê-lo sem read() tradicional.
// Conte quantos bytes nulos (\0) existem nele.

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

    off_t tamanho = lseek(fd, 0, SEEK_END);
    if (tamanho == -1) {
        perror("Erro ao usar lseek");
        close(fd);
        return 1;
    }

    printf("Tamanho do arquivo: %lld bytes\n", (long long)tamanho);

    int count = 0;
    for (off_t i = 0; i < tamanho; i++) {
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("Erro ao usar lseek");
            close(fd);
            return 1;
        }
        char byte;
        if (read(fd, &byte, 1) != 1) {
            perror("Erro ao ler byte");
            close(fd);
            return 1;
        }
        // printf("Byte %lld: %d\n", (long long)i, (int)byte);

        if (byte == '\0') {
            count++;
        }
    }

    printf("Número de bytes nulos encontrados: %d\n", count);

    close(fd);
    return 0;
}