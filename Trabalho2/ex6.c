// 6. Alternar entre dois diretórios
// Crie um programa que salva o diretório atual, muda para outro caminho
// fornecido, imprime o diretório atual, e depois volta para o diretório
// original.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return 1;
    }

    char current_directory[PATH_MAX];
    char original_directory[PATH_MAX];

    // obtem diretorio atual
    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("Erro ao obter diretório atual");
        return 1;
    }
    printf("Diretório atual salvo: %s\n", current_directory);

    // copia para original_directory
    strncpy(original_directory, current_directory, PATH_MAX);
    original_directory[PATH_MAX-1] = '\0';

    // muda para o diretório fornecido
    if (chdir(argv[1]) == -1) {
        perror("Erro ao mudar de diretório");
        return 1;
    }

    char new_directory[PATH_MAX];
    if (getcwd(new_directory, sizeof(new_directory)) == NULL) {
        perror("Erro ao obter novo diretório");
        return 1;
    }
    printf("Diretório após mudança: %s\n", new_directory);

    // volta para o diretório original
    if (chdir(original_directory) == -1) {
        perror("Erro ao voltar para o diretório original");
        return 1;
    }

    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("Erro ao obter diretório original");
        return 1;
    }
    printf("Diretório original: %s\n", current_directory);

    return 0;
}
