// 5. Testar diretório vazio antes de remover
// Crie um programa que verifica se um diretório está vazio antes de
// chamar rmdir().

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>  
#include <sys/types.h>
#include <dirent.h>
#include <string.h> 

int is_directory_empty(DIR *directory) {
    struct dirent *entry;
    while((entry = readdir(directory)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) { // ignora . e ..
            return 0; // diretório não está vazio
        }
    }
    return 1; // diretório está vazio
}

int main(int argc, char *argv[]){

    if( argc != 2) {
        fprintf(stderr, "Uso: %s <diretorio>\n", argv[0]);
        return 1;
    }

    const char *directory_name = argv[1];
    
    DIR *directory = opendir(directory_name);
    if(directory == NULL){
        perror("Erro ao abrir diretorio.\n");
        return -1;
    }

    struct dirent *entry;
    int is_empty = is_directory_empty(directory);
    closedir(directory);

    if(is_empty == -1){
        printf("Diretorio %s nao esta vazio e nao sera removido\n", directory_name);
        return 1;
    }

    if(rmdir(directory_name) == -1){
        perror("Erro ao remover diretório\n");
        return -1;
    }

    printf("Sucesso ao remover o diretório %s \n", directory_name);
    return 0;
}