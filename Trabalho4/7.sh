# Faça um script que renomeia todos os arquivos com extensão “.mpeg3” para “.mp3”, em um
# diretório fornecido na linha de comando.

#!/bin/bash

LOG="erros.txt"

# Verifica se o usuário informou um diretório
if [ -z "$1" ]; then
    echo "Uso correto: $0 <diretório>"
    echo "Erro: Nenhum diretório informado." >> "$LOG"
    exit 1
fi

DIRETORIO="$1"

# Verifica se o caminho é um diretório válido
if [ ! -d "$DIRETORIO" ]; then
    echo "O diretório '$DIRETORIO' não existe ou não é válido."
    echo "Diretório inválido informado: $DIRETORIO" >> "$LOG"
    exit 1
fi

# Busca segura por arquivos .mpeg3
# Faz com que glob vazio (*.mpeg3) não gere texto literal
shopt -s nullglob

# Armazena os arquivos .mpeg3 em um array
arquivos=("$DIRETORIO"/*.mpeg3)

# Verifica se há arquivos
if [ ${#arquivos[@]} -eq 0 ]; then
    echo "Nenhum arquivo .mpeg3 encontrado em '$DIRETORIO'."
    exit 0
fi

# Percorre cada arquivo encontrado
for arquivo in "${arquivos[@]}"; do

    # Altera somente a extensão
    novo_nome="${arquivo%.mpeg3}.mp3"

    # Tenta renomear com tratamento de erro
    if mv "$arquivo" "$novo_nome" 2>>"$LOG"; then
        echo "Renomeado: '$arquivo' → '$novo_nome'"
    else
        echo "Falha ao renomear '$arquivo'."
    fi

done