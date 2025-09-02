// Ler parte de um arquivo com lseek()
// Escreva um programa que:
// Receba o nome de um arquivo
// Leia apenas os 100 primeiros bytes usando read().
// Depois, use lseek() para pular para o byte 200 e leia mais 50
// bytes.
// Exiba o conteúdo lido.

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
    char buffer[151]; // 100 + 50 + 1 para o terminador nulo
    ssize_t bytes_lidos;

    // Ler os primeiros 100 bytes
    bytes_lidos = read(fd, buffer, 100);
    if (bytes_lidos == -1) {
        perror("Erro ao ler os 100 primeiros bytes do arquivo usando read");
        close(fd);
        return 1;
    }

    // Usar lseek() para pular para o byte 200
    if (lseek(fd, 200, SEEK_SET) == -1) {
        perror("Erro ao usar lseek para pular para o byte 200");
        close(fd);
        return 1;
    }

    // Ler mais 50 bytes
    bytes_lidos = read(fd, buffer + 100, 50);
    if (bytes_lidos == -1) {
        perror("Erro ao ler os 50 bytes do arquivo usando read");
        close(fd);
        return 1;
    }

    // Exibir o conteúdo lido
    buffer[100 + 50] = '\0'; // Adicionar terminador nulo
    printf("Conteúdo lido:\n%s\n", buffer);

    close(fd);
    return 0;
}