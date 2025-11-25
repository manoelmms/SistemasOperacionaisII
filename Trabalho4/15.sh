# Crie um script que mostre o espaço utilizado pelos arquivos dentro de cada diretório da sua
# conta no sistema, colocando em ordem numérica o resultado.

#!/bin/bash
du -sh ~/* | sort -h

# O comando du -sh ~/* calcula o espaço utilizado por cada diretório e arquivo na sua conta,
# exibindo o tamanho em formato legível (-h) e o total para cada item (-s). 
# Em seguida, o comando sort -h ordena os resultados em ordem numérica.