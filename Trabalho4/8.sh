# Repita o exercício anterior de forma interativa, perguntando o diretório desejado e as
# extensões.

#!/bin/bash
read -p "Digite o diretório desejado: " diretorio
read -p "Digite a extensão dos arquivos a serem renomeados (ex: mpeg3): " extensao_antiga
read -p "Digite a nova extensão dos arquivos (ex: mp3): " extensao_nova

if [ -d "$diretorio" ]; then # Verifica se o diretório existe
    for arquivo in "$diretorio"/*."$extensao_antiga"; do # Itera sobre todos os arquivos com a extensão antiga
        if [ -e "$arquivo" ]; then # Verifica se o arquivo existe
            novo_nome="${arquivo%.$extensao_antiga}.$extensao_nova"
            mv "$arquivo" "$novo_nome" # Renomeia o arquivo
            echo "Renomeado: '$arquivo' para '$novo_nome'"
        else
            echo "Nenhum arquivo .$extensao_antiga encontrado em '$diretorio'."
        fi
    done
else
    echo "O diretório '$diretorio' não existe."
fi
