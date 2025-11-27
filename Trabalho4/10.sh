# Mostre na tela todos os argumentos recebidos na linha de comando, imprimindo-os como
# abaixo. Se forem mais do que 9, o comando shift será necessário.
# 1: parâmetro 1
# 2: parâmetro 2

#!/bin/bash

LOG="erros.txt"

# Verificação de argumentos

if [ $# -eq 0 ]; then
    echo "Nenhum parâmetro foi informado."
    echo "Erro: execução sem argumentos." >> "$LOG"
    exit 1
fi

contador=1

# Impressão dos argumentos

for arg in "$@"; do
    # Se por algum motivo o argumento estiver vazio, registra no log
    if [ -z "$arg" ]; then
        echo "Parâmetro $contador está vazio."
        echo "Argumento vazio encontrado na posição $contador" >> "$LOG"
    else
        echo "$contador: $arg"
    fi

    contador=$((contador + 1))
done
