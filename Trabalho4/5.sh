# Faça um script que imprime quantos processos estão atualmente em execução na sua máquina.
# Não se esqueça de que o seu script também entrará na contagem.

#!/bin/bash
num_processos=$(ps -e | wc -l) # Conta o número de linhas retornadas pelo comando ps -e
num_processos=$((num_processos - 1)) # Subtrai 1 para não contar o próprio script
echo "Número de processos em execução: $num_processos"
