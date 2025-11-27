# Arquivo: 2.sh

## 1. Execução normal

```bash
./2.sh
```

## 2. HOME válido, mas vazio

```bash
mkdir home_vazio
HOME="$(pwd)/home_vazio" ./2.sh
```

## 3. Falha no comando date

```bash
PATH="" ./2.sh
```

## 4. HOME apontando para caminho inexistente

```bash
HOME="/caminho/que/nao/existe" ./2.sh
```

## 5. HOME definido como arquivo (não diretório)

```bash
echo "teste" > falso_home
HOME="$(pwd)/falso_home" ./2.sh
```

## 6. HOME sem permissão de acesso

```bash
mkdir home_sem_permissao
chmod 000 home_sem_permissao
HOME="$(pwd)/home_sem_permissao" ./2.sh
```

# Arquivo: 3.sh

## 1. Arquivo existente

```bash
touch arquivo.txt
./3.sh arquivo.txt
```

## 2. Arquivo inexistente
```bash
./3.sh naoexiste.txt
```

## 3. Nenhum argumento
```bash
./3.sh
```

## 4. Arquivo sem permissão
```bash
touch secreto.txt
chmod 000 secreto.txt
./3.sh secreto.txt
```

# Arquivo: 4.sh

## 1. Arquivo maior que 100 bytes
```bash
printf 'a%.0s' {1..150} > grande.txt
./4.sh grande.txt
```

## 2. Arquivo menor que 100 bytes
```bash
echo "Pequeno" > pequeno.txt
./4.sh pequeno.txt
```

## 3. Arquivo inexistente
```bash
./4.sh nada.txt
```

## 4. Nenhum argumento
```bash
./4.sh
```

## 5. Arquivo sem permissão
```bash
touch sem_permissão.txt
chmod 000 sem_permissão.txt
./4.sh sem_permissão.txt
```

# Arquivo: 5.sh

## 1. Execução normal
```bash
./5.sh
```

## 2. Simular erro no ps
```bash
PATH="" ./5.sh
```

# Arquivo: 6.sh

## 1. Execução normal
```bash
Digite o mês (1-12):
5
Digite o ano (YYYY):
2025
```

## 2. Mês inválido (positivo e fora do intervalo)
```bash
Digite o mês (1-12):
15
Digite o ano (YYYY):
2025
```

## 3. Mês inválido (negativo)
```bash
Digite o mês (1-12):
-3
Digite o ano (YYYY):
2025
```

## 4. Ano inválido
```bash
Digite o mês (1-12):
5
Digite o ano (YYYY):
abc
```

## 5. Ano fora do formato
```bash
Digite o mês (1-12):
5
Digite o ano (YYYY):
202
```

# Arquivo: 7.sh

## 1. Execução normal
```bash
mkdir musicas
touch musicas/teste1.mpeg3 musicas/teste2.mpeg3
./7.sh musicas
```

## 2. Sem arquivos
```bash
mkdir vazia
./7.sh vazia
```

## 3. Diretório inexistente
```bash
./7.sh naoexiste
```

## 4. Sem argumento
```bash
./7.sh
```

# Arquivo: 8.sh

## 1. Diretório válido e arquivos existentes
```bash
mkdir teste
touch teste/foto.mpeg3 teste/audio.mpeg3
```

## 2. Diretório válido sem arquivos
```bash
mkdir vazio

Diretório: vazio
Extensão antiga: mpeg3
Extensão nova: mp3
```

## 3. Diretório inexistente
```bash
Diretório: pasta_fake
```

## 4. Diretório vazio (não informado)
```bash
Diretório:
```
## 5. Extensão antiga vazia
```bash
Extensão antiga:
```

## 6. Extensão nova vazia
```bash
Extensão nova:
```

## 7. Extensão inválida (caracteres proibidos)
```bash
mp#3
```
# Arquivo: 9.sh

## 1. Nenhum argumento informado
```bash
./9.sh
```

## 2. Arquivo inexistente
```bash
./9.sh nada.txt
```

## 3. Caminho é diretório, não arquivo
```bash
mkdir teste_dir
./9.sh teste_dir
```

## 4. Arquivo sem permissão de leitura
```bash
touch sem_permissao.txt
chmod 000 sem_permissao.txt
./9.sh sem_permissao.txt
```

## 5. Arquivo válido (caso normal)
```bash
echo "Olá mundo
Essa é uma frase" > texto.txt
./9.sh texto.txt
```

## 6. Falha forçada do comando wc
```bash
PATH="" ./9.sh texto.txt
```

## 7. Arquivo vazio
```bash
touch vazio.txt
./9.sh vazio.txt
```

# Arquivo: 10.sh

## 1. Nenhum argumento
```bash
./10.sh
```

## 2. Parâmetros normais
```bash
./10.sh um dois tres
```

## 3. Parâmetro vazio
```bash
./10.sh "teste" "" "outro"
```

## 4. Muitos parâmetros (> 9)
```bash
./10.sh a b c d e f g h i j k l
```

## 5. Parâmetros com espaços
```bash
./10.sh "um parametro" "segundo teste"
```

## 6. Caracteres especiais
```bash
./10.sh "arquivo(1)" "$%¨&*" "#teste"
```

# Arquivo: 11.sh

## 1. Execução normal (caso padrão)
```bash
./11.sh
```

## 2. Simular /etc/passwd inexistente
```bash
sed -i '' 's|/etc/passwd|/etc/passwd_fake|' 11.sh
./11.sh
```

## 3. Simular falha nos comandos cut ou sort
```bash
PATH="" ./11.sh
```

# Arquivo: 12.sh

## 1. Execução normal
```bash
./12.sh
```

## 2. Simular /etc/passwd inexistente
```bash
sed -i '' 's|/etc/passwd|/etc/passwd_fake|' 12.sh
./12.sh
```

## 3. Falha nos comandos cut/sort/uniq
```bash
PATH="" ./12.sh
```
# Arquivo: 13.sh

## 1. Execução normal
```bash
./13.sh
```

## 2. Diretórios já existentes
```bash
mkdir dir1 dir3
./13.sh
```

## 3. Falha do comando touch ou mkdir (simulada via PATH)
```bash
PATH="" ./13.sh
```

# Arquivo: 14.sh

## 1. Nenhuma ideia informada
```bash
./14.sh
```

## 2. Inserção normal
```bash
./14.sh "Estudar Shell Script"
```

## 3. Arquivo sem permissão de escrita
```bash
chmod 444 ideias.txt
./14.sh "Teste sem permissão"
```

## 5. Falha do comando date (simulação)
```bash
PATH="" ./14.sh "Ideia teste"
```

# Arquivo: 15.sh

## 1. Execução normal
```bash
./15.sh
```

## 2. HOME inválido
```bash
HOME="/caminho/inexistente" ./15.sh
```

## 3. Diretório HOME vazio
```bash
mkdir vazio
HOME="$(pwd)/vazio" ./15.sh
```

# Arquivo: 16.sh

## 1. Execução normal
```bash
./16.sh
```

