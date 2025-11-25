# Escreva um script capaz de adicionar ideias em um repositório de ideias, situado em /ideias.txt.
# O programa deve ser executado com a ideia como parâmetro da linha de comando e deve fazer
# entradas que comecem com a data/hora do dia, como no exemplo abaixo:
# 30/08/2008 10:21 Fazer script para remover usuários

#!/bin/bash
if [ -z "$1" ]; then # Verifica se o argumento foi fornecido
    echo "Uso: $0 'sua ideia aqui'"
    exit 1
fi
ideia="$1"
data_hora=$(date +"%d/%m/%Y %H:%M")
# valida se deu certo a inserção
if echo "$data_hora $ideia" >> ./ideias.txt; then
    echo "Ideia adicionada com sucesso."
else
    echo "Erro ao adicionar ideia."
fi
