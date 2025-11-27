# Escreva um script capaz de adicionar ideias em um repositório de ideias, situado em /ideias.txt.
# O programa deve ser executado com a ideia como parâmetro da linha de comando e deve fazer
# entradas que comecem com a data/hora do dia, como no exemplo abaixo:
# 30/08/2008 10:21 Fazer script para remover usuários

#!/bin/bash

LOG="erros.txt"
ARQUIVO_IDEIAS="ideias.txt"

# Validação da entrada

if [ -z "$1" ]; then
    echo "Uso: $0 \"sua ideia aqui\""
    echo "Erro: Nenhuma ideia fornecida." >> "$LOG"
    exit 1
fi

IDEIA="$*"

# Geração da data/hora

data_hora=$(date +"%d/%m/%Y %H:%M" 2>>"$LOG")

if [ $? -ne 0 ]; then
    echo "Não foi possível obter a data e hora."
    exit 1
fi

# Verificação do arquivo ideias.txt

# Se o arquivo não existir, tenta criá-lo
if [ ! -e "$ARQUIVO_IDEIAS" ]; then
    if ! touch "$ARQUIVO_IDEIAS" 2>>"$LOG"; then
        echo "Não foi possível criar o arquivo de ideias."
        exit 1
    fi
fi

# Verifica permissão de escrita
if [ ! -w "$ARQUIVO_IDEIAS" ]; then
    echo "Não há permissão para escrever no arquivo de ideias."
    echo "Permissão negada em $ARQUIVO_IDEIAS" >> "$LOG"
    exit 1
fi

# Adiciona a ideia no arquivo
if echo "$data_hora $IDEIA" >> "$ARQUIVO_IDEIAS" 2>>"$LOG"; then
    echo "Ideia adicionada com sucesso."
else
    echo "Erro ao adicionar ideia."
fi