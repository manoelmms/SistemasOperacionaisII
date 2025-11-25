# Faça um script que renomeia todos os arquivos com extensão “.mpeg3” para “.mp3”, em um
# diretório fornecido na linha de comando.

#!/bin/bash
if [ -d "$1" ]; then # Verifica se o argumento é um diretório
    for arquivo in "$1"/*.mpeg3; do # Itera sobre todos os arquivos .mpeg3 no diretório
        if [ -e "$arquivo" ]; then # Verifica se o arquivo existe
            novo_nome="${arquivo%.mpeg3}.mp3"
            mv "$arquivo" "$novo_nome" # Renomeia o arquivo
            echo "Renomeado: '$arquivo' para '$novo_nome'"
        else
            echo "Nenhum arquivo .mpeg3 encontrado em '$1'."
        fi
    done
else
    echo "O diretório '$1' não existe."
fi
