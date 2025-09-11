// 10. Criar diretórios temporários para teste
// Crie um programa que cria uma estrutura temporária dentro de /tmp, faz
// algumas operações (chdir(), listagem) e depois remove tudo com rmdir()
// em sequência.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

void list_current_dir() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("Erro ao abrir diretório");
        return;
    }

    printf("Conteúdo de %s:\n", getcwd(NULL, 0));
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

int main() {
    const char *base_directory = "/tmp/teste_tmp";

    // cria diretório base
    if (mkdir(base_directory, 0755) == -1) {
        perror("Erro ao criar diretório base\n");
        return -1;
    }
    printf("Diretorio base criado com sucesso: %s\n", base_directory);

    // entra nele
    if (chdir(base_directory) == -1) {
        perror("Erro ao entrar no diretorio base\n");
        return -1;
    }

    // cria subdiretórios
    if (mkdir("sub1", 0755) == -1 || mkdir("sub2", 0755) == -1) {
        perror("Erro ao criar subdiretorios\n");
        return -1;
    }
    printf("Subdiretorios criados: sub1, sub2\n");

    // lista conteúdo
    list_current_dir();

    // remove subdiretórios
    if (rmdir("sub1") == -1 || rmdir("sub2") == -1) {
        perror("Erro ao remover subdiretorios\n");
        return -1;
    }
    printf("Subdiretórios removidos\n");

    // volta para /tmp
    if (chdir("..") == -1) {
        perror("Erro ao voltar para /tmp \n");
        return -1;
    }

    // remove diretório base
    if (rmdir(base_directory) == -1) {
        perror("Erro ao remover diretorio base \n");
        return 1;
    }
    printf("Diretorio base removido com sucesso: %s\n", base_directory);

    return 0;
}
