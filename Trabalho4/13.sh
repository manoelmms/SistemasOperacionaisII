# Crie um script que utilize um loop para criar 5 diretórios com o nome padrão dir<n>, onde n é o
# número a ser adicionado ao nome do diretório. Dentro de cada diretório crie 3 arquivos com o
# nome padrão file<m>, onde m é o número a ser adicionado ao nome do arquivo.

#!/bin/bash

for i in $(seq 1 5); do
    dir_name="dir$i" # Define o nome do diretório
    mkdir "$dir_name" # Cria o diretório
    for j in $(seq 1 3); do
        file_name="$dir_name/file$j" # Define o nome do arquivo dentro do diretório
        touch "$file_name" # Cria o arquivo
    done
done