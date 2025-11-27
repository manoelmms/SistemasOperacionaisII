# Utilizando o comando find, busque os arquivos que pertencem ao seu usuário, a partir do “/”,
# redirecionando a saída para o arquivo “arq.txt”e os erros para “erros.txt”.

#!/bin/bash

LOG="erros.txt"
ARQ_SAIDA="arq.txt"

# Obtém o nome do usuário atual
USUARIO=$(whoami 2>>"$LOG")

# Verifica se o usuário foi obtido corretamente
if [ -z "$USUARIO" ]; then
    echo "Não foi possível identificar o usuário atual."
    exit 1
fi

echo "Iniciando busca de arquivos pertencentes ao usuário '$USUARIO'..."

# Execução protegida do find

# Executa o find redirecionando saída e erros
if find / -user "$USUARIO" > "$ARQ_SAIDA" 2>>"$LOG"; then
    echo "Busca finalizada com sucesso."
    echo "Arquivos encontrados foram salvos em '$ARQ_SAIDA'."
else
    echo "Busca concluída com erros. Consulte '$LOG' para detalhes."
fi

# O comando find / -user $(whoami) busca todos os arquivos a partir do diretório raiz (/) que pertencem ao usuário atual.
# A saída padrão (arquivos encontrados) é redirecionada para "arq.txt" usando o operador >, 
# enquanto os erros (como permissões negadas) são redirecionados para "erros.txt" usando o operador 2>.