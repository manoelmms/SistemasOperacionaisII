// 8. Navegar recursivamente e listar diretórios
// Crie um programa que percorre um caminho fornecido e imprime todos os
// subdiretórios recursivamente usando chdir() e getcwd().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

#define PATH_MAX 4096

void list_dirs_recursive(const char *path, int depth) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Erro ao abrir diretório");
        return;
    }

    // Salva o diretório atual
    char cwd[PATH_MAX];
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("Erro ao obter cwd");
        closedir(dir);
        return;
    }

    if (chdir(path) == -1) {
        perror("Erro ao mudar de diretório");
        closedir(dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            struct stat st;
            if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode)) {
                for (int i = 0; i < depth; i++) printf("  ");
                printf("%s\n", entry->d_name);
                // chama recursivamente
                list_dirs_recursive(entry->d_name, depth + 1);
            }
        }
    }

    closedir(dir);

    // Volta para o diretório anterior
    if (chdir(cwd) == -1) {
        perror("Erro ao voltar para diretório anterior");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <caminho>\n", argv[0]);
        return 1;
    }

    printf("Listando diretórios de: %s\n", argv[1]);
    list_dirs_recursive(argv[1], 0);

    return 0;
}
