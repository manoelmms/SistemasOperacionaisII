# Faça um script que informa se o arquivo passado pela linha de comando, caso exista, é maior
# que 100 bytes. O comando stat pode ajudar na determinação do tamanho.

#!/bin/bash

LOG="erros.txt"

# Verifica se o usuário informou um argumento
if [ -z "$1" ]; then
    echo "Uso correto: $0 <arquivo>"
    echo "Erro: Nenhum arquivo informado." >> "$LOG"
    exit 1
fi

ARQUIVO="$1"

# Verifica se existe
if [ ! -e "$ARQUIVO" ]; then
    echo "O arquivo '$ARQUIVO' não existe."
    echo "Arquivo inexistente informado: $ARQUIVO" >> "$LOG"
    exit 1
fi

# Verifica a permissão de leitura
if [ ! -r "$ARQUIVO" ]; then
    echo "O arquivo existe, mas não pode ser acessado."
    echo "Permissão negada ao acessar: $ARQUIVO" >> "$LOG"
    exit 1
fi

# Executa stat e redireciona erro para o log
# Para Linux
#tamanho=$(stat -c%s "$ARQUIVO" 2>>"$LOG")
# Para Mac
tamanho=$(stat -f%z "$ARQUIVO" 2>>"$LOG")

# Verifica se o comando stat falhou
if [ $? -ne 0 ]; then
    echo "Não foi possível obter o tamanho do arquivo."
    exit 1
fi

# Comparação do tamanho
if [ "$tamanho" -gt 100 ]; then
    echo "O arquivo '$ARQUIVO' é maior que 100 bytes."
else
    echo "O arquivo '$ARQUIVO' não é maior que 100 bytes."
fi