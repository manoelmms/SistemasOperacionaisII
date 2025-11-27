# Escreva um script que testa se determinado arquivo existe ou não. O nome do arquivo será
# passado na linha de comando.

LOG="erros.txt"

#!/bin/bash

# Verifica se o usuário informou o nome do arquivo
if [ -z "$1" ]; then
    echo "Uso correto: $0 <nome_do_arquivo>"
    echo "Erro: Nenhum arquivo informado pelo usuário." >> "$LOG"
    exit 1
fi

ARQUIVO="$1"

# Testa se o arquivo existe
if [ -e "$ARQUIVO" ]; then
    echo "O arquivo '$ARQUIVO' existe."
else
    echo "O arquivo '$ARQUIVO' não existe."
fi

# verifica se existe, mas não pode ser acessado
if [ -e "$ARQUIVO" ] && [ ! -r "$ARQUIVO" ]; then
    echo "O arquivo existe, mas não pode ser acessado."
    echo "Erro de permissão ao acessar: $ARQUIVO" >> "$LOG"
fi