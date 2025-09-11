// 9. Alterar permissões e criar diretório
// Crie um programa que cria um diretório e imediatamente altera suas
// permissões com chmod() para rwxr-x---.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_diretorio>\n", argv[0]);
        return 1;
    }

    const char *directory = argv[1];

    // cria o diretório com permissões padrão (ex.: 0755)
    if (mkdir(directory, 0755) == -1) {
        perror("Erro ao criar diretório\n");
        return 1;
    }

    printf("Diretório criado: %s\n", directory);

    // altera as permissões para rwxr-x---
    if (chmod(directory, 0750) == -1) {
        perror("Erro ao alterar permissoes\n");
        return 1;
    }

    printf("Permissões alteradas com sucesso para rwxr-x--- (750)\n");

    return 0;
}
