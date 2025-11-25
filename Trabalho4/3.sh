# Escreva um script que testa se determinado arquivo existe ou não. O nome do arquivo será
# passado na linha de comando.

#!/bin/bash
if [ -e "$1" ]; then
  echo "O arquivo '$1' existe."
else
  echo "O arquivo '$1' não existe."
fi