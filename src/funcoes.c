#include "../include/funcoes.h"


// FUNÇÕES DE SISTEMA DE DADO



 // rolarDado - Gera um número aleatório entre 1 e faces
 
int rolarDado(int faces) {
    return (rand() % faces) + 1;
}


 // testePericia - Testa se uma ação foi bem-sucedida
 // Regra: sucesso se valor >= (faces/2 + 1)
 // Exemplo com d6: sucesso em 4, 5 ou 6
 // Parâmetros: faces - número de faces do dado
 // Retorno: 1 para sucesso, 0 para falha
 
int testePericia(int faces) {
    int resultado = rolarDado(faces);
    int limiarSucesso = (faces / 2) + 1;  // Aritmética inteira
    
    printf("\n Rolando dado de %d faces...\n", faces);
    printf("Resultado: %d\n", resultado);
    printf("Necessário: %d ou mais\n", limiarSucesso);
    
    if (resultado >= limiarSucesso) {
        return 1;  // Sucesso
    } else {
        return 0;  // Falha
    }
}


 //mostrarResultadoDado - Exibe resultado do teste de forma visual
 
 
void mostrarResultadoDado(int valor, int sucesso) {
    if (sucesso) {
        printf("SUCESSO! Você tirou %d no dado!\n", valor);
    } else {
        printf("FALHA! Você tirou %d no dado!\n", valor);
    }
}


// FUNÇÕES DE RANKING (ARQUIVOS E ALOCAÇÃO DINÂMICA)



 // carregarRanking - Carrega ranking do arquivo
 //Parâmetros: quantidade - ponteiro para armazenar número de entradas
 //Retorno: ponteiro para vetor de EntradaRanking alocado dinamicamente
 
EntradaRanking* carregarRanking(int *quantidade) {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "r");
    *quantidade = 0;
    
    // Tratamento de erro: Caso o arquivo não exista ou não pode ser aberto
    if (arquivo == NULL) {
        printf("Arquivo de ranking não encontrado. Será criado um novo.\n");
        return NULL;
    }
    
    // Primeiro, conta quantas entradas existem
    int count = 0;
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        count++;
    }
    
    // Se arquivo está vazio
    if (count == 0) {
        fclose(arquivo);
        return NULL;
    }
    
    // ALOCAÇÃO DINÂMICA - malloc para vetor de structs
    EntradaRanking *ranking = (EntradaRanking*) malloc(count * sizeof(EntradaRanking));
    
    // Tratamento de erro: falha na alocação
    if (ranking == NULL) {
        printf("Erro ao alocar memória para ranking!\n");
        fclose(arquivo);
        return NULL;
    }
    
    // Volta ao início do arquivo para ler os dados
    rewind(arquivo);
    
    // Lê cada entrada do arquivo
    int i = 0;
    while (i < count && fscanf(arquivo, "%99[^;];%d\n", 
                                ranking[i].nome, 
                                &ranking[i].pontuacao) == 2) {
        i++;
    }
    
    *quantidade = i;
    fclose(arquivo);
    
    return ranking;  // Retorna ponteiro para área alocada
}


 //salvarRanking - Salva ranking no arquivo
 // Parâmetros: ranking - vetor de entradas, quantidade - tamanho do vetor
 
void salvarRanking(EntradaRanking *ranking, int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "w");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de ranking para escrita!\n");
        return;
    }
    
    // Loop for percorrendo vetor de structs
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%s;%d\n", ranking[i].nome, ranking[i].pontuacao);
    }
    
    fclose(arquivo);
}


 // adicionarAoRanking - Adiciona novo jogador ao ranking
 // Parâmetros: 
 //   ranking - ponteiro para ponteiro do vetor (permite modificar o ponteiro original)
 //   quantidade - ponteiro para quantidade (permite modificar)
 //   jogador - struct jogador por valor
 
void adicionarAoRanking(EntradaRanking **ranking, int *quantidade, Jogador jogador) {
    // ALOCAÇÃO DINÂMICA - realloc para expandir vetor
    int novaQuantidade = (*quantidade) + 1;
    EntradaRanking *novoRanking = (EntradaRanking*) realloc(*ranking, 
                                                             novaQuantidade * sizeof(EntradaRanking));
    
    if (novoRanking == NULL && novaQuantidade > 0) {
        printf("Erro ao realocar memória para ranking!\n");
        return;
    }
    
    // Adiciona novo jogador ao final do vetor
    strcpy(novoRanking[*quantidade].nome, jogador.nome);
    novoRanking[*quantidade].pontuacao = jogador.pontuacao;
    
    // Atualiza ponteiro e quantidade
    *ranking = novoRanking;
    *quantidade = novaQuantidade;
}

 //ordenarRanking - Ordena ranking por pontuação (decrescente)
 // Algoritmo: Bubble Sort (implementação manual)

void ordenarRanking(EntradaRanking *ranking, int quantidade) {
    // Bubble Sort - ordenação manual
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            // Ordem decrescente (maior pontuação primeiro)
            if (ranking[j].pontuacao < ranking[j + 1].pontuacao) {
                // Troca
                EntradaRanking temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}


 // exibirRanking - Mostra ranking formatado
 
void exibirRanking(EntradaRanking *ranking, int quantidade) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("           RANKING DOS MELHORES MAGOS!!\n");
    printf("═══════════════════════════════════════════════════════\n\n");
    
    if (quantidade == 0 || ranking == NULL) {
        printf("  Ainda não há jogadores no ranking.\n\n");
        return;
    }
    
    printf("  Posição | Nome do Mago                    | Pontos\n");
    printf("  ─────────────────────────────────────────────────────\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("  %4d    | %-30s | %6d\n", 
               i + 1, ranking[i].nome, ranking[i].pontuacao);
    }
    
    printf("\n");
}


 //liberarRanking - Libera memória alocada para o ranking
 
void liberarRanking(EntradaRanking *ranking) {
    if (ranking != NULL) {
        free(ranking);  // Libera memória alocada dinamicamente
    }
}


// FUNÇÕES DE JOGADOR



 // inicializarJogador - Inicializa dados do jogador
 
void inicializarJogador(Jogador *jogador) {
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║    Bem-vindo à UTFPR - Academia de Magia Tecnológica ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    
    printf("Digite o nome do seu mago/bruxa: ");
    limparBuffer();
    fgets(jogador->nome, MAX_NOME, stdin);
    
    // Remove newline do final
    size_t len = strlen(jogador->nome);
    if (len > 0 && jogador->nome[len - 1] == '\n') {
        jogador->nome[len - 1] = '\0';
    }
    
    jogador->pontuacao = 0;
    jogador->mana = 100;  // Mana inicial
    
    printf("\nÓtimo, %s! Sua jornada está prestes a começar!\n", jogador->nome);
}


 // exibirStatusJogador - Mostra status atual do jogador
 
void exibirStatusJogador(Jogador jogador) {
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│ Mago: %-28s │\n", jogador.nome);
    printf("│ Pontuação: %-24d │\n", jogador.pontuacao);
    printf("│ Mana: %-29d │\n", jogador.mana);
    printf("└─────────────────────────────────────┘\n");
}


 // obterTituloFinal - Retorna título baseado na pontuação

char* obterTituloFinal(int pontuacao) {
    if (pontuacao >= 200) {
        return "Arquimago Supremo";
    } else if (pontuacao >= 150) {
        return "Mago Especialista";
    } else if (pontuacao >= 100) {
        return "Feiticeiro Competente";
    } else if (pontuacao >= 50) {
        return "Aprendiz Promissor";
    } else {
        return "Iniciante em Magia";
    }
}


 // exibirResumoFinal - Mostra resumo ao final do jogo
 
void exibirResumoFinal(Jogador jogador) {
    printf("\n\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("             FIM DA JORNADA ACADÊMICA \n");
    printf("═══════════════════════════════════════════════════════\n\n");
    
    printf("  Mago: %s\n", jogador.nome);
    printf("  Pontuação Final: %d pontos\n", jogador.pontuacao);
    printf("  Título Conquistado: %s\n\n", obterTituloFinal(jogador.pontuacao));
    
    if (jogador.pontuacao >= 150) {
        printf("   Parabéns! Você foi um dos melhores alunos!\n");
    } else if (jogador.pontuacao >= 100) {
        printf("   Bom trabalho! Você se formou com honra!\n");
    } else {
        printf("   Continue estudando para se tornar um mago melhor!\n");
    }
    
    printf("\n═══════════════════════════════════════════════════════\n\n");
}


// FUNÇÕES DE EVENTOS E NARRATIVA


/*
 * inicializarEventos - Preenche vetor de eventos com a narrativa
 * REQUISITOS ATENDIDOS:
 * - Vetores de struct (eventos é vetor passado como parâmetro)
 * - Strings (manipulação com strcpy)
 * - Funções com vetores como parâmetro
 */
void inicializarEventos(Evento *eventos) {
    // CAPÍTULO 1: Chegada à Academia
    strcpy(eventos[0].titulo, "Capítulo 1: A Chegada");
    strcpy(eventos[0].narrativa, 
        "Você acaba de chegar à UTFPR - Academia de Magia Tecnológica.\n"
        "O enorme castelo de pedra e circuitos mágicos se ergue diante de você.\n"
        "Na entrada, o Professor Algoritmus Magnus aguarda os novos alunos.\n"
        "Ele anuncia: 'Calouros, demonstrem sua capacidade mágica inicial!'\n");
    strcpy(eventos[0].opcao1, "1. Tentar conjurar um feitiço de luz básico");
    strcpy(eventos[0].opcao2, "2. Estudar o grimório antes de tentar");
    eventos[0].recompensaSucesso = 30;
    eventos[0].penalidade = 5;
    
    // CAPÍTULO 2: Primeira Aula
    strcpy(eventos[1].titulo, "Capítulo 2: Aula de Ponteiros Mágicos");
    strcpy(eventos[1].narrativa,
        "Sua primeira aula é com a Professora Memorya Alloc.\n"
        "Ela ensina sobre Ponteiros Mágicos - feitiços que referenciam outros feitiços.\n"
        "'Agora, alunos, vocês devem criar um ponteiro para um cristal de mana!'\n"
        "Esta é uma tarefa avançada para iniciantes.\n");
    strcpy(eventos[1].opcao1, "1. Tentar criar o ponteiro mágico com confiança");
    strcpy(eventos[1].opcao2, "2. Pedir ajuda ao colega ao lado");
    eventos[1].recompensaSucesso = 40;
    eventos[1].penalidade = 10;
    
    // CAPÍTULO 3: Prova Prática
    strcpy(eventos[2].titulo, "Capítulo 3: Prova de Estruturas Mágicas");
    strcpy(eventos[2].narrativa,
        "Chegou o dia da primeira prova prática!\n"
        "O Professor Structus Von Data apresenta o desafio:\n"
        "'Vocês devem organizar cinco elementos mágicos em uma estrutura coerente.'\n"
        "Os elementos flutuam no ar, aguardando sua manipulação.\n");
    strcpy(eventos[2].opcao1, "1. Usar magia de organização rápida (arriscado)");
    strcpy(eventos[2].opcao2, "2. Organizar cuidadosamente um por um");
    eventos[2].recompensaSucesso = 50;
    eventos[2].penalidade = 15;
    
    // CAPÍTULO 4: Desafio em Dupla
    strcpy(eventos[3].titulo, "Capítulo 4: Labirinto dos Arquivos Antigos");
    strcpy(eventos[3].narrativa,
        "Você e outros alunos foram levados ao Labirinto dos Arquivos Antigos.\n"
        "A missão: recuperar um pergaminho mágico guardado há séculos.\n"
        "O labirinto está cheio de armadilhas e enigmas de código ancestral.\n"
        "Um colega sugere dividir as tarefas.\n");
    strcpy(eventos[3].opcao1, "1. Trabalhar em equipe e compartilhar conhecimento");
    strcpy(eventos[3].opcao2, "2. Seguir sozinho confiando apenas em si mesmo");
    eventos[3].recompensaSucesso = 45;
    eventos[3].penalidade = 10;
    
    // CAPÍTULO 5: Desafio Final
    strcpy(eventos[4].titulo, "Capítulo 5: O Desafio do Dragão de Dados");
    strcpy(eventos[4].narrativa,
        "O exame final chegou! Todo o conhecimento será testado.\n"
        "Um Dragão de Dados aparece, criado magicamente pelos professores.\n"
        "Para derrotá-lo, você deve executar um feitiço supremo que combina\n"
        "ponteiros, estruturas, alocação dinâmica e manipulação de arquivos mágicos!\n");
    strcpy(eventos[4].opcao1, "1. Lançar o feitiço supremo com toda sua mana");
    strcpy(eventos[4].opcao2, "2. Usar estratégia defensiva e estudar o padrão do dragão");
    eventos[4].recompensaSucesso = 60;
    eventos[4].penalidade = 20;
}


 //exibirEvento - Mostra narrativa de um evento
 
void exibirEvento(Evento evento, int numeroCapitulo) {
    printf("\n\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("  %s\n", evento.titulo);
    printf("═══════════════════════════════════════════════════════\n\n");
    printf("%s\n", evento.narrativa);
    printf("───────────────────────────────────────────────────────\n");
    printf("%s\n", evento.opcao1);
    printf("%s\n", evento.opcao2);
    printf("───────────────────────────────────────────────────────\n");
}


 //executarEvento - Processa escolha do jogador em um evento
 //Retorna: 1 se jogador quer continuar, 0 se quer sair
int executarEvento(Evento evento, Jogador *jogador) {
    int escolha;
    
    printf("\nSua escolha (1 ou 2): ");
    scanf("%d", &escolha);
    
    // Validação de entrada
    while (escolha != 1 && escolha != 2) {
        printf("Opção inválida! Escolha 1 ou 2: ");
        scanf("%d", &escolha);
    }
    
    printf("\n");
    
    if (escolha == 1) {
        printf("Você escolheu a ação ousada!\n");
    } else {
        printf("Você escolheu a ação cautelosa!\n");
    }
    
    // Teste de perícia usando o dado
    int sucesso = testePericia(FACES_DADO);
    
    printf("\n");
    
    if (sucesso) {
        printf(" SUCESSO! Sua ação foi bem-sucedida!\n");
        jogador->pontuacao += evento.recompensaSucesso;
        printf("   +%d pontos conquistados!\n", evento.recompensaSucesso);
        
        // Bônus extra para escolha 2 bem-sucedida (mais segura)
        if (escolha == 2) {
            printf("   Bônus por estratégia: +5 pontos!\n");
            jogador->pontuacao += 5;
        }
    } else {
        printf(" FALHA! A ação não saiu como esperado...\n");
        jogador->pontuacao -= evento.penalidade;
        printf("   -%d pontos perdidos.\n", evento.penalidade);
    }
    
    // Ajuste de mana (apenas para efeito narrativo)
    if (sucesso) {
        jogador->mana = (jogador->mana < 90) ? jogador->mana + 10 : 100;
    } else {
        jogador->mana = (jogador->mana > 20) ? jogador->mana - 15 : 10;
    }
    
    exibirStatusJogador(*jogador);
    
    return 1;  // Continuar jogo
}


// FUNÇÕES DE INTERFACE E MENU



 // exibirCabecalho - Mostra cabeçalho do jogo
 
void exibirCabecalho() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║                                                      ║\n");
    printf("║         UTFPR - ACADEMIA DE MAGIA TECNOLÓGICA      ║\n");
    printf("║                                                      ║\n");
    printf("║          Uma Aventura de Programação em C           ║\n");
    printf("║                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
}


 // exibirMenuPrincipal - Mostra menu principal do jogo
 
void exibirMenuPrincipal() {
    printf("\n");
    printf("┌──────────────────────────────────────┐\n");
    printf("│          MENU PRINCIPAL              │\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│  1. Iniciar Nova Campanha            │\n");
    printf("│  2. Ver Ranking                      │\n");
    printf("│  3. Sair                             │\n");
    printf("└──────────────────────────────────────┘\n");
    printf("\nEscolha uma opção: ");
}


 // limparBuffer - Limpa buffer de entrada

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


 // pausar - Pausa execução até usuário pressionar Enter
 
void pausar() {
    printf("\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}


// FUNÇÕES AUXILIARES COM MATRIZES E VETORES



 // preencherMatrizSalas - Preenche matriz com nomes de salas
 
void preencherMatrizSalas(char salas[][20], int linhas) {
    // Matriz de strings representando salas da academia
    const char* nomesSalas[] = {
        "Biblioteca Mágica",
        "Lab. de Ponteiros",
        "Sala de Structs",
        "Torre dos Arquivos"
    };
    
    for (int i = 0; i < linhas && i < 4; i++) {
        strcpy(salas[i], nomesSalas[i]);
    }
}


 // exibirMapaSalas - Exibe mapa de salas da academia

 
void exibirMapaSalas(char salas[][20], int linhas) {
    printf("\n📍 Mapa da Academia:\n");
    for (int i = 0; i < linhas; i++) {
        printf("   %d. %s\n", i + 1, salas[i]);
    }
    printf("\n");
}


 // inicializarAcademia - Inicializa dados da academia
 
void inicializarAcademia(Academia *academia) {
    strcpy(academia->nome, "UTFPR - Academia de Magia Tecnológica");
    
    // Preenche vetor de professores (struct dentro de struct)
    strcpy(academia->professores[0].nome, "Prof. Algoritmus Magnus");
    strcpy(academia->professores[0].disciplina, "Feitiços Algorítmicos");
    
    strcpy(academia->professores[1].nome, "Profa. Memorya Alloc");
    strcpy(academia->professores[1].disciplina, "Ponteiros Mágicos");
    
    strcpy(academia->professores[2].nome, "Prof. Structus Von Data");
    strcpy(academia->professores[2].disciplina, "Estruturas de Dados Místicas");
    
    academia->numProfessores = 3;
}
