# Faça um script que informa se o arquivo passado pela linha de comando, caso exista, é maior
# que 100 bytes. O comando stat pode ajudar na determinação do tamanho.

#!/bin/bash
if [ -e "$1" ]; then
  tamanho=$(stat -c%s "$1") # Obtém o tamanho do arquivo em bytes usando stat
  if [ "$tamanho" -gt 100 ]; then
    echo "O arquivo '$1' é maior que 100 bytes."
  else
    echo "O arquivo '$1' não é maior que 100 bytes."
  fi
else
  echo "O arquivo '$1' não existe."
fi