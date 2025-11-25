# Crie um script para mostrar todos os usuários cadastrados no sistema, em ordem alfabética.
# O comando cat e o arquivo /etc/passwd podem lhe ajudar.

#!/bin/bash
cat /etc/passwd | cut -d: -f1 | sort

# O comando cut é usado para extrair o primeiro campo (nome do usuário) do arquivo /etc/passwd,
# que é separado por dois pontos (:). Em seguida, o comando sort ordena os nomes em ordem alfabética.
