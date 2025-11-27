# Escreva um script que informa o número de linhas e de palavras de um arquivo passado na linha
# de comando.

#!/bin/bash

LOG="erros.txt"

# Validação da entrada

if [ -z "$1" ]; then
    echo "Uso correto: $0 <arquivo>"
    echo "Erro: Nenhum arquivo informado." >> "$LOG"
    exit 1
fi

ARQUIVO="$1"

# Verificação de existência

if [ ! -e "$ARQUIVO" ]; then
    echo "O arquivo '$ARQUIVO' não existe."
    echo "Arquivo inexistente informado: $ARQUIVO" >> "$LOG"
    exit 1
fi

# Verificação se é arquivo regular

if [ ! -f "$ARQUIVO" ]; then
    echo "'$ARQUIVO' não é um arquivo válido."
    echo "Caminho não é arquivo regular: $ARQUIVO" >> "$LOG"
    exit 1
fi

# Permissão de leitura

if [ ! -r "$ARQUIVO" ]; then
    echo "O arquivo existe, mas não pode ser lido."
    echo "Permissão negada ao ler: $ARQUIVO" >> "$LOG"
    exit 1
fi

# Contagem de linhas

linhas=$(wc -l < "$ARQUIVO" 2>>"$LOG")

if [ $? -ne 0 ]; then
    echo "Erro ao contar linhas do arquivo."
    exit 1
fi

# Contagem de palavras

palavras=$(wc -w < "$ARQUIVO" 2>>"$LOG")

if [ $? -ne 0 ]; then
    echo "Erro ao contar palavras do arquivo."
    exit 1
fi

echo "O arquivo '$ARQUIVO' tem $linhas linhas e $palavras palavras."