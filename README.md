-> UTFPR - Academia de Magia Tecnológica

-> Estrutura do Projeto

Projetofinal_C2/
|-- src/
│    main.c           # Arquivo principal com função main
│   funcoes.c        # Implementação de todas as funções
|-- include/
│    funcoes.h        # Cabeçalho com structs e protótipos
|-- data/
│    ranking.txt      # Arquivo de ranking persistente
|--- docs/
     documentacao.txt # Documentação completa do projeto

-> Como Compilar

No diretório raiz do projeto, execute:

 bash
gcc src/main.c src/funcoes.c -I include -o jogo


-> Descrição

Este é um jogo de RPG em modo texto onde você é um estudante de magia na UTFPR transformada em Academia de Magia Tecnológica. O jogo apresenta:

- 5 capítulos narrativos interativos
- Sistema de decisões baseado em lançamento de dados
- Pontuação e ranking persistente
- Títulos baseados no desempenho

## Conceitos de Programação Implementados do requisito para o projeto

-Ponteiros e alocação dinâmica (malloc, realloc, free)
-Estruturas de dados (structs, vetores, matrizes)
-Manipulação de arquivos (leitura e escrita)
-Modularização de código
-Algoritmos de ordenação (Bubble Sort)
-Tratamento de erros
-Sistema de dado com regra de sucesso/falha

-> Autores
Pedro Lucas Lobato Munhoz
João Vitor Antunes dos Santos
