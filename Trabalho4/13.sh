# Crie um script que utilize um loop para criar 5 diretórios com o nome padrão dir<n>, onde n é o
# número a ser adicionado ao nome do diretório. Dentro de cada diretório crie 3 arquivos com o
# nome padrão file<m>, onde m é o número a ser adicionado ao nome do arquivo.

#!/bin/bash

LOG="erros.txt"

echo "Iniciando criação de diretórios e arquivos..."

# Loop para criação dos diretórios
for i in $(seq 1 5); do
    dir_name="dir$i"

    # Verifica se o diretório já existe
    if [ -e "$dir_name" ]; then
        echo "O diretório '$dir_name' já existe."
        echo "Diretório já existente: $dir_name" >> "$LOG"
        continue
    fi

    # Cria o diretório e trata erro
    if ! mkdir "$dir_name" 2>>"$LOG"; then
        echo "Falha ao criar o diretório '$dir_name'."
        continue
    fi

    # Cria 3 arquivos dentro do diretório
    for j in $(seq 1 3); do
        file_name="$dir_name/file$j"

        # Tenta criar o arquivo
        if ! touch "$file_name" 2>>"$LOG"; then
            echo "Falha ao criar o arquivo '$file_name'."
        fi
    done

done

echo "Processo concluído."
