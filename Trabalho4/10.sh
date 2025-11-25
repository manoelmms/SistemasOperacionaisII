# Mostre na tela todos os argumentos recebidos na linha de comando, imprimindo-os como
# abaixo. Se forem mais do que 9, o comando shift será necessário.
# 1: parâmetro 1
# 2: parâmetro 2

#!/bin/bash

contador=1
for arg in "$@"; do
    echo "$contador: $arg"
    contador=$((contador + 1))
done

