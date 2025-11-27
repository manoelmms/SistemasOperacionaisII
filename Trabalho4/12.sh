# Um dos parâmetros de cada linha do arquivo /etc/passwd é o shell usado pelo usuário (7o
# campo). Escreva um script capaz de listar todos os shells únicos existentes neste arquivo. O
# comando uniq pode ser útil.

#!/bin/bash

LOG="erros.txt"
ARQUIVO_PASSWD="/etc/passwd"

# Verifica se o arquivo existe
if [ ! -e "$ARQUIVO_PASSWD" ]; then
    echo "Arquivo de usuários do sistema não encontrado."
    echo "/etc/passwd inexistente." >> "$LOG"
    exit 1
fi

# Verifica se é possível ler o arquivo
if [ ! -r "$ARQUIVO_PASSWD" ]; then
    echo "Não é possível ler o arquivo de usuários do sistema."
    echo "Permissão negada em /etc/passwd." >> "$LOG"
    exit 1
fi

# Extrai o 7º campo (shell), ordena e remove duplicados
shells=$(cut -d: -f7 "$ARQUIVO_PASSWD" 2>>"$LOG" | sort 2>>"$LOG" | uniq 2>>"$LOG")

# Verifica falha nos comandos
if [ $? -ne 0 ]; then
    echo "Erro ao processar a lista de shells do sistema."
    exit 1
fi

echo "Shells únicos existentes no sistema:"
echo "$shells"


# O comando cut é usado para extrair o sétimo campo (shell) do arquivo /etc/passwd,
# que é separado por dois pontos (:). Em seguida, o comando sort ordena os shells em ordem alfabética,
# e o comando uniq remove os shells duplicados, exibindo apenas os únicos.