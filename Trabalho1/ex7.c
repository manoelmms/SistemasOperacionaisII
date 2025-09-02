// Truncar arquivo com lseek() e write()
// Escreva um programa que:
// Abra um arquivo de texto.
// Use lseek() para pular até o byte 20.
// Escreva "FIM\n".
// Isso deve cortar/truncar o conteúdo a partir dali.

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
    int fd = open(filename, O_RDWR);
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

    if (lseek(fd, 20, SEEK_SET) == -1) {
        perror("Erro ao usar lseek para pular para o byte 20");
        close(fd);
        return 1;
    }
    const char *texto = "FIM\n";
    ssize_t bytes_escritos = write(fd, texto, 4);
    if (bytes_escritos == -1) {
        perror("Erro ao escrever no arquivo");
        close(fd);
        return 1;
    }
    printf("Escreveu %zd bytes no arquivo.\n", bytes_escritos);

    // Truncar o arquivo na posição atual (20 + 4 = 24 bytes)
    off_t nova_posicao = lseek(fd, 0, SEEK_CUR);
    if (ftruncate(fd, nova_posicao) == -1) {
        perror("Erro ao truncar o arquivo");
        close(fd);
        return 1;
    }
    printf("Arquivo truncado para %lld bytes.\n", (long long)nova_posicao);

    close(fd);
    return 0;
}