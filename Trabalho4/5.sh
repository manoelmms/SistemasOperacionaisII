# Faça um script que imprime quantos processos estão atualmente em execução na sua máquina.
# Não se esqueça de que o seu script também entrará na contagem.

#!/bin/bash

LOG="erros.txt"

echo "Contando processos em execução..."

# Executa o comando ps e redireciona qualquer erro para o log
saida_ps=$(ps -e 2>>"$LOG")

# Verifica se o comando ps falhou
if [ $? -ne 0 ]; then
    echo "Não foi possível obter a lista de processos."
    exit 1
fi

# Conta quantas linhas existem na saída do ps
# Cada linha representa um processo (exceto a primeira, que é o cabeçalho)
num_processos=$(echo "$saida_ps" | wc -l)

# Subtrai 1 para não contar a linha de cabeçalho do ps
num_processos=$((num_processos - 1))

# Garante que o resultado não seja negativo
if [ "$num_processos" -lt 0 ]; then
    echo "Erro ao calcular o número de processos."
    echo "Contagem inválida retornada pelo comando ps." >> "$LOG"
    exit 1
fi

echo "Número de processos em execução: $num_processos"