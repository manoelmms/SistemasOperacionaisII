# Crie um script que mostre o espaço utilizado pelos arquivos dentro de cada diretório da sua
# conta no sistema, colocando em ordem numérica o resultado.

#!/bin/bash

LOG="erros.txt"
HOME_DIR="$HOME"

echo "Calculando o espaço utilizado em cada item do diretório HOME..."

# Verifica se a variável HOME está definida
if [ -z "$HOME_DIR" ]; then
    echo "Diretório HOME não definido."
    echo "Variável HOME vazia." >> "$LOG"
    exit 1
fi

# Verifica se HOME é um diretório válido
if [ ! -d "$HOME_DIR" ]; then
    echo "Diretório HOME inválido."
    echo "HOME não é diretório válido: $HOME_DIR" >> "$LOG"
    exit 1
fi

# Faz com que glob vazio não vire texto literal
shopt -s nullglob

# Armazena todos os itens do HOME
itens=("$HOME_DIR"/*)

# Verifica se há itens
if [ ${#itens[@]} -eq 0 ]; then
    echo "Nenhum arquivo ou diretório encontrado em $HOME_DIR."
    shopt -u nullglob
    exit 0
fi

# Executa du e ordena os resultados
saida=$(du -sh "${itens[@]}" 2>>"$LOG" | sort -h 2>>"$LOG")

# Verifica se houve erro
if [ $? -ne 0 ]; then
    echo "Erro ao calcular o espaço em disco."
    exit 1
fi

echo "$saida"
shopt -u nullglob


# O comando du -sh ~/* calcula o espaço utilizado por cada diretório e arquivo na sua conta,
# exibindo o tamanho em formato legível (-h) e o total para cada item (-s). 
# Em seguida, o comando sort -h ordena os resultados em ordem numérica.