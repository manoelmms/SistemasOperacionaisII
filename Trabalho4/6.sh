# Crie um script que peça um mês e um ano ao usuário e depois apresente o calendário do
# mês/ano pedido. O comando cal é recomendado neste caso.

#!/bin/bash
echo "Digite o mês (1-12): "
read mes # recebe do input o mês
echo "Digite o ano (YYYY): "
read ano # recebe do input o ano
cal $mes $ano # Exibe o calendário do mês e ano fornecidos pelo usuário

# cal retorna erro se o mês for inválido (não entre 1-12) ou se o ano não for um número válido.