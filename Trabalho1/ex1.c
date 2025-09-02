// Usando lseek() para medir o tamanho do arquivo
// Escreva um programa que:
// Abra um arquivo qualquer.
// Use lseek(fd, 0, SEEK_END) para posicionar no final.
// Exiba o tamanho do arquivo em bytes.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

    printf("Tamanho do arquivo '%s': %ld bytes\n", filename, tamanho);
    
    close(fd);
    return 0;
}