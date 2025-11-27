# Crie um script para mostrar todos os usuários cadastrados no sistema, em ordem alfabética.
# O comando cat e o arquivo /etc/passwd podem lhe ajudar.

#!/bin/bash

LOG="erros.txt"
ARQUIVO_PASSWD="/etc/passwd"

# Verifica se o arquivo existe
if [ ! -e "$ARQUIVO_PASSWD" ]; then
    echo "Arquivo de usuários do sistema não encontrado."
    echo "/etc/passwd inexistente." >> "$LOG"
    exit 1
fi

# Verifica se há permissão de leitura
if [ ! -r "$ARQUIVO_PASSWD" ]; then
    echo "Não é possível ler o arquivo de usuários do sistema."
    echo "Permissão negada em /etc/passwd." >> "$LOG"
    exit 1
fi

# Extrai os nomes de usuários e ordena
usuarios=$(cut -d: -f1 "$ARQUIVO_PASSWD" 2>>"$LOG" | sort 2>>"$LOG")

# Confere se houve erro na execução
if [ $? -ne 0 ]; then
    echo "Erro ao processar a lista de usuários."
    exit 1
fi

echo "Usuários do sistema (ordem alfabética):"
echo "$usuarios"
