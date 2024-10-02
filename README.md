# README - Compilação e Execução do Projeto em C++

Este README fornece instruções sobre como compilar e executar o projeto em C++. 

## Pré-requisitos

Certifique-se de que você tem o `make` e um compilador C++ (como `g++`) instalados no seu sistema.

## Compilação

Para compilar o projeto, siga estas etapas:

1. Abra o terminal.
2. Navegue até o diretório onde o código-fonte do projeto está localizado.
3. Execute o seguinte comando:

   ```bash
   make
   ```

Esse comando irá compilar todos os arquivos necessários e gerar o executável.

## Execução

Após a compilação, você pode executar o programa usando o seguinte comando:

```bash
./counter <DATASET> <QUANTIDADE_DE_CLICKS [k]> <ALGORITMO> <r [OPCIONAL]>
```

### Parâmetros

- `<DATASET>`: O caminho para o arquivo de dataset que será utilizado.
- `<QUANTIDADE_DE_CLICKS [k]>`: O número de cliques (em milhares) que o programa deve processar.
- `<ALGORITMO>`: O algoritmo que você deseja usar para o processamento, onde:
  - `0`: Sequencial
  - `1`: Paralelo
  - `2`: Paralelo com roubo de carga
- `<r [OPCIONAL]>`: Um parâmetro opcional que pode ser utilizado dependendo da implementação do algoritmo.

### Exemplo de Execução

```bash
./counter dataset.txt 3 1
```

Esse comando executaria o programa utilizando o dataset `dataset.txt`, processando 3 cliques com o algoritmo paralelo.

---

Se tiver alguma dúvida ou encontrar problemas, sinta-se à vontade para abrir uma issue!