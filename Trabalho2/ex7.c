// 7. Criar diretórios com base na data
// Crie um programa que cria diretórios com nomes baseados na data atual
// (2025-08-27) dentro de /tmp ou outro caminho.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]){

    //caminho base
    const char *base_path = "/tmp";

    //obter data atual
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char date_str[11];
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", tm_info);

    // construir caminho completo
    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", base_path, date_str);


    // criar diretório
    if (mkdir(full_path, 0755) == -1) {
        perror("Erro ao criar diretório");
        return 1;
    }

    printf("Diretório criado com sucesso: %s\n", full_path);

    return 0;
}