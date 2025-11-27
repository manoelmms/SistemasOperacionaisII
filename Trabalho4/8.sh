# Repita o exercício anterior de forma interativa, perguntando o diretório desejado e as
# extensões.

#!/bin/bash

LOG="erros.txt"

# Entrada do usuário

read -r -p "Digite o diretório desejado: " diretorio
read -r -p "Digite a extensão dos arquivos a serem renomeados (ex: mpeg3): " extensao_antiga
read -r -p "Digite a nova extensão dos arquivos (ex: mp3): " extensao_nova

# Remove ponto inicial, se o usuário digitar ".mp3" ou ".mpeg3"
extensao_antiga="${extensao_antiga#.}"
extensao_nova="${extensao_nova#.}"

# Validação do diretório

if [ -z "$diretorio" ]; then
    echo "Nenhum diretório informado."
    echo "Erro: diretório vazio informado." >> "$LOG"
    exit 1
fi

if [ ! -d "$diretorio" ]; then
    echo "O diretório '$diretorio' não existe ou não é válido."
    echo "Diretório inválido informado: $diretorio" >> "$LOG"
    exit 1
fi

# Validação das extensões

if [ -z "$extensao_antiga" ]; then
    echo "Extensão antiga não pode ser vazia."
    echo "Extensão antiga vazia informada." >> "$LOG"
    exit 1
fi

if [ -z "$extensao_nova" ]; then
    echo "Extensão nova não pode ser vazia."
    echo "Extensão nova vazia informada." >> "$LOG"
    exit 1
fi

# Restringe extensões a caracteres simples
if ! [[ "$extensao_antiga" =~ ^[A-Za-z0-9_]+$ ]]; then
    echo "Extensão antiga inválida. Use apenas letras, números ou _."
    echo "Extensão antiga inválida: $extensao_antiga" >> "$LOG"
    exit 1
fi

if ! [[ "$extensao_nova" =~ ^[A-Za-z0-9_]+$ ]]; then
    echo "Extensão nova inválida. Use apenas letras, números ou _."
    echo "Extensão nova inválida: $extensao_nova" >> "$LOG"
    exit 1
fi

# Busca pelos arquivos
shopt -s nullglob
arquivos=("$diretorio"/*."$extensao_antiga")

if [ ${#arquivos[@]} -eq 0 ]; then
    echo "Nenhum arquivo .$extensao_antiga encontrado em '$diretorio'."
    shopt -u nullglob
    exit 0
fi

# Renomeação dos arquivos
for arquivo in "${arquivos[@]}"; do
    novo_nome="${arquivo%.$extensao_antiga}.$extensao_nova"

    if mv "$arquivo" "$novo_nome" 2>>"$LOG"; then
        echo "Renomeado: '$arquivo' → '$novo_nome'"
    else
        echo "Falha ao renomear '$arquivo'."
    fi
done

shopt -u nullglob