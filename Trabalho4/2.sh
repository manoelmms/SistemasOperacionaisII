# Escreva um script que mostre a data de hoje e liste todos os arquivos da sua conta.

#!/bin/bash

LOG="erros.txt"

HOME_DIR="$HOME"

echo "Data de hoje:"

# Executa o comando date e redireciona qualquer erro para o arquivo de log.
# O "!" inverte o resultado: se date falhar, entramos no bloco do if.
if ! date 2>>"$LOG"; then
    echo "Não foi possível obter a data atual."
    exit 1
fi

echo
echo "Lista de arquivos na sua conta:"

# Verifica se o diretório definido em HOME_DIR realmente existe e se é um diretório
if [ ! -d "$HOME_DIR" ]; then
    echo "Diretório HOME inválido ou inexistente."

    echo "Erro ao acessar diretório HOME: $HOME_DIR" >> "$LOG"

    exit 1
fi

# Lista os arquivos do diretório HOME
if ! ls -la "$HOME_DIR" 2>>"$LOG"; then
    echo "Não foi possível listar os arquivos do diretório."
    exit 1
fi
