
#include "../include/funcoes.h"

 // Executa uma campanha completa do jogo
 
void executarCampanha(Jogador *jogador, EntradaRanking **ranking, int *quantidadeRanking) {
    // Array de eventos da campanha (REQUISITO: vetor de struct)
    Evento eventos[NUM_CAPITULOS];
    
    // Inicializa eventos com narrativa
    inicializarEventos(eventos);
    
    // Exibe introdução com mapa de salas (demonstra uso de matriz)
    char salas[4][20];  // REQUISITO: Matriz bidimensional
    preencherMatrizSalas(salas, 4);
    
    printf("\n\n");
    printf(" Você está prestes a iniciar sua jornada mágica!\n");
    exibirMapaSalas(salas, 4);
    pausar();
    
    // Inicializa academia (demonstra struct aninhada)
    Academia academia;
    inicializarAcademia(&academia);
    
    printf("\n Bem-vindo à %s\n", academia.nome);
    printf("\nVocê será orientado por nossos professores:\n");
    for (int i = 0; i < academia.numProfessores; i++) {
        printf("  • %s - %s\n", 
               academia.professores[i].nome, 
               academia.professores[i].disciplina);
    }
    pausar();
    
    // Loop principal do jogo - percorre todos os capítulos
    // REQUISITO: Loop for com vetor
    for (int i = 0; i < NUM_CAPITULOS; i++) {
        exibirEvento(eventos[i], i + 1);
        
        if (!executarEvento(eventos[i], jogador)) {
            printf("\nVocê decidiu abandonar a academia...\n");
            return;
        }
        
        if (i < NUM_CAPITULOS - 1) {
            pausar();
        }
    }
    
    // Exibe resumo final
    exibirResumoFinal(*jogador);
    
    // Adiciona ao ranking
    // REQUISITO: Ponteiro para ponteiro, alocação dinâmica
    adicionarAoRanking(ranking, quantidadeRanking, *jogador);
    
    // Ordena ranking
    ordenarRanking(*ranking, *quantidadeRanking);
    
    // Salva ranking no arquivo
    salvarRanking(*ranking, *quantidadeRanking);
    
    printf(" Sua pontuação foi salva no ranking!\n");
    pausar();
}


 // Função principal do programa
 
int main() {
    // REQUISITO: Inicialização do gerador de números aleatórios
    srand(time(NULL));
    
    // REQUISITO: Declaração de ponteiro para vetor alocado dinamicamente
    EntradaRanking *ranking = NULL;
    int quantidadeRanking = 0;
    
    // REQUISITO: Carrega ranking do arquivo (alocação dinâmica + arquivo)
    ranking = carregarRanking(&quantidadeRanking);
    
    // Variável de controle do menu
    int opcao = 0;
    int continuar = 1;
    
    exibirCabecalho();
    
    printf("\n Bem-vindo ao jogo! Este é um RPG acadêmico de fantasia.\n");
    printf("   Cada decisão será testada com um dado de %d faces.\n", FACES_DADO);
    printf("   Você precisa tirar %d ou mais para ter sucesso!\n", (FACES_DADO/2) + 1);
    pausar();
    
    // REQUISITO: Loop principal do programa (while)
    while (continuar) {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        
        // REQUISITO: Estrutura de controle switch
        switch (opcao) {
            case 1: {
                // Iniciar nova campanha
                // REQUISITO: Declaração de variável struct
                Jogador jogador;
                
                // Inicializa jogador (entrada de dados)
                inicializarJogador(&jogador);
                
                // Executa campanha completa
                // REQUISITO: Passagem de ponteiros como parâmetros
                executarCampanha(&jogador, &ranking, &quantidadeRanking);
                
                break;
            }
            
            case 2: {
                // Ver ranking
                if (quantidadeRanking == 0) {
                    printf("\nAinda não há jogadores no ranking.\n");
                } else {
                    // REQUISITO: Ordenação manual antes de exibir
                    ordenarRanking(ranking, quantidadeRanking);
                    exibirRanking(ranking, quantidadeRanking);
                }
                pausar();
                break;
            }
            
            case 3: {
                // Sair
                continuar = 0;
                printf("\n Obrigado por jogar! Até a próxima aventura mágica!\n\n");
                break;
            }
            
            default: {
                // REQUISITO: Validação de entrada
                printf("\n Opção inválida! Por favor, escolha 1, 2 ou 3.\n");
                pausar();
                break;
            }
        }
    }
    
   
    // Libera memória alocada para o ranking
    liberarRanking(ranking);
    
    printf("Memória liberada com sucesso.\n");
    printf("Programa encerrado.\n\n");
    
    return 0;
}
