# Um dos parâmetros de cada linha do arquivo /etc/passwd é o shell usado pelo usuário (7o
# campo). Escreva um script capaz de listar todos os shells únicos existentes neste arquivo. O
# comando uniq pode ser útil.

#!/bin/bash
cat /etc/passwd | cut -d: -f7 | sort | uniq

# O comando cut é usado para extrair o sétimo campo (shell) do arquivo /etc/passwd,
# que é separado por dois pontos (:). Em seguida, o comando sort ordena os shells em ordem alfabética,
# e o comando uniq remove os shells duplicados, exibindo apenas os únicos.