# Huffman Compressor & Decompressor 

Este projeto é uma implementação do algoritmo de compressão de **Huffman** desenvolvida em linguagem C. O programa é capaz de reduzir o tamanho de arquivos de texto através da codificação de caracteres baseada em sua frequência e depois descompactar.

## 🚀 Como Funciona

O projeto utiliza estruturas de dados clássicas para realizar a tarefa:
1. **Frequência**: Mapeia a ocorrência de cada caractere ASCII.
2. **Lista de Prioridade**: Organiza os caracteres para a construção da árvore.
3. **Árvore de Huffman**: Gera códigos binários variáveis (caracteres comuns = códigos curtos).
4. **Buffer de Bits**: Manipula a escrita binária em nível de bit para otimizar o espaço.



## 🛠️ Estrutura do Projeto

- `main.c`: Ponto de entrada para compressão.
- `descompactar.c`: Ponto de entrada para descompressão.
- `arvore.c / .h`: Lógica da árvore binária.
- `lista.c / .h`: Implementação da lista de prioridade.
- `codigo.c / .h`: Manipulador de buffer de bits e dicionário.
- `teste.txt`: Arquivo para usar de teste (pode ser modificado caso queira)

## 🧠 Conceitos Aplicados
- **Árvores Binárias**: Navegação de caminhos (0 para esquerda, 1 para direita).
- **Lista de Prioridade**: Ordenação dinâmica de frequências.
- **Bitwise Operations**: Manipulação de memória em nível de bit para compressão real.
- **Backtracking**: Recursão para geração de dicionário na árvore.

## 💻 Como Executar

### Pré-requisitos
Possuir um compilador C (GCC ou Clang) instalado.

### Passo 1: Compilar e Comprimir
```bash
# Compilar o compressor
gcc main.c arvore.c lista.c codigo.c -o huffman

# Executar a compressão (gera o arquivo compactado.huf)
./huffman
```
### Passo 2: Compilar e Descomprimir
```bash
# Compilar o descompressor
gcc descompactar.c arvore.c lista.c codigo.c -o descompactar

# Executar a descompressão (gera o arquivo saida_final.txt)
./descompactar
```
### Comandos Úteis de Inspeção
```bash
# Ver as primeiras linhas do arquivo em binário
xxd -b compactado.huf | head -n 10

# Para pular o cabeçalho e ver os bits reais que representam o seu texto
tail -c +2057 compactado.huf | xxd -b

# Para garantir que o arquivo descompactado é 100% igual ao original
diff -s teste.txt saida_final.txt
```
