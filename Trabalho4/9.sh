# Escreva um script que informa o número de linhas e de palavras de um arquivo passado na linha
# de comando.

#!/bin/bash
if [ -f "$1" ]; then
    linhas=$(wc -l < "$1")
    palavras=$(wc -w < "$1")
    echo "O arquivo '$1' tem $linhas linhas e $palavras palavras."
else
    echo "O arquivo '$1' não existe."
fi