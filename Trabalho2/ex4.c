// 4. Criar subdiretórios recursivamente
// Crie um programa que recebe um caminho como "pasta1/pasta2/pasta3" e
// cria todos os diretórios faltantes em sequência.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>  
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

#define PATH_MAX 4096

int mkpath(char* file_path, mode_t mode) {
    assert(file_path && *file_path); // garante que file_path não é nulo ou vazio

    // cria cada subdiretório na sequência
    // for inicializa um ponteiro p que procura por '/' em file_path a partir do segundo caractere
    // incrementa p para continuar procurando após o último '/'
    // para quando p for nulo (não há mais '/')
    for (char* p = strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/')) { 
        *p = '\0';
        if (mkdir(file_path, mode) == -1) { // tenta criar o subdiretório
            if (errno != EEXIST) { // ignora erro se o diretório já existe
                *p = '/';
                return -1;
            }
        }
        *p = '/';
    }
    
    // cria o último diretório (final da string)
    if (mkdir(file_path, mode) == -1) {
        if (errno != EEXIST) { // ignora erro se o diretório já existe
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Uso: %s <caminho de diretorio(s)>", argv[0]);
        return 1;
    }
    char path[PATH_MAX];
    strncpy(path, argv[1], PATH_MAX);
    path[PATH_MAX-1] = '\0';

    if(mkpath(path, 0755) == -1){
        perror("Erro ao criar diretórios\n");
        return -1;
    }
    printf("Diretórios criados com sucesso: %s\n", path);

    return 0;
}