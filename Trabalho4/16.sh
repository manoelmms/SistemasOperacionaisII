# Utilizando o comando find, busque os arquivos que pertencem ao seu usuário, a partir do “/”,
# redirecionando a saída para o arquivo “arq.txt”e os erros para “erros.txt”.

#!/bin/bash
find / -user $(whoami) > arq.txt 2> erros.txt

# O comando find / -user $(whoami) busca todos os arquivos a partir do diretório raiz (/) que pertencem ao usuário atual.
# A saída padrão (arquivos encontrados) é redirecionada para "arq.txt" usando o operador >, 
# enquanto os erros (como permissões negadas) são redirecionados para "erros.txt" usando o operador 2>.