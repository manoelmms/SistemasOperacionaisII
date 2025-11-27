# Crie um script que peça um mês e um ano ao usuário e depois apresente o calendário do
# mês/ano pedido. O comando cal é recomendado neste caso.

#!/bin/bash
LOG="erros.txt"

echo "Digite o mês (1-12): "
read mes # Lê o mês informado pelo usuário

echo "Digite o ano (AAAA): "
read ano # Lê o ano informado pelo usuário

# Validação do mês

# Verifica se o mês é numérico
if ! [[ "$mes" =~ ^[0-9]+$ ]]; then
    echo "Mês inválido. Informe um número entre 1 e 12."
    echo "Entrada inválida para mês: $mes" >> "$LOG"
    exit 1
fi

# Verifica se está no intervalo 1-12
if [ "$mes" -lt 1 ] || [ "$mes" -gt 12 ]; then
    echo "Mês inválido. Informe um valor entre 1 e 12."
    echo "Mês fora do intervalo válido: $mes" >> "$LOG"
    exit 1
fi

# Validação do ano

# Verifica se o ano é numérico
if ! [[ "$ano" =~ ^[0-9]+$ ]]; then
    echo "Ano inválido. Informe um número no formato AAAA."
    echo "Entrada inválida para ano: $ano" >> "$LOG"
    exit 1
fi

# Verifica se o ano tem 4 dígitos
if [ "${#ano}" -ne 4 ]; then
    echo "Ano inválido. Utilize o formato AAAA."
    echo "Ano fora do padrão: $ano" >> "$LOG"
    exit 1
fi

# Exibição do calendário

# Executa o comando cal com tratamento de erro
if ! cal "$mes" "$ano" 2>>"$LOG"; then
    echo "Não foi possível gerar o calendário para $mes/$ano."
    exit 1
fi