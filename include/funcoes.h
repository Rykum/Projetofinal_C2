#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes globais do jogo
#define MAX_NOME 100
#define FACES_DADO 6
#define MAX_TEXTO 1000
#define NUM_CAPITULOS 5
#define ARQUIVO_RANKING "data/ranking.txt"


// ESTRUTURAS HETEROGÊNEAS (STRUCTS) 



 // Struct Jogador 

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
    int mana;  // Atributo adicional de RPG (energia mágica)
} Jogador;


 // Struct EntradaRanking - Representa uma entrada no ranking
 // Usada para: salvar e ordenar ranking de melhores jogadores
 
typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} EntradaRanking;


 // Struct Evento - Representa um capítulo/evento da história
 // Campos: título, texto narrativo, opções disponíveis
 // Usada para: organizar a narrativa do jogo em eventos
 
typedef struct {
    char titulo[MAX_NOME];
    char narrativa[MAX_TEXTO];
    char opcao1[200];
    char opcao2[200];
    int recompensaSucesso;   // Pontos ganhos em sucesso
    int penalidade;           // Pontos perdidos em falha
} Evento;


 // Struct Professor - Representa um professor da academia

typedef struct {
    char nome[MAX_NOME];
    char disciplina[MAX_NOME];
} Professor;


 //Struct Academia - Representa a escola de magia
 // Contém vetor de professores (exemplo de aninhamento de structs)
 
typedef struct {
    char nome[MAX_NOME];
    Professor professores[3];  // Vetor de struct Professor
    int numProfessores;
} Academia;


// PROTÓTIPOS DE FUNÇÕES 


//  Funções de Sistema de Dado 
int rolarDado(int faces);
int testePericia(int faces);
void mostrarResultadoDado(int valor, int sucesso);

//  Funções de Ranking (Manipulação de Arquivos e Alocação Dinâmica) 
EntradaRanking* carregarRanking(int *quantidade);
void salvarRanking(EntradaRanking *ranking, int quantidade);
void adicionarAoRanking(EntradaRanking **ranking, int *quantidade, Jogador jogador);
void ordenarRanking(EntradaRanking *ranking, int quantidade);
void exibirRanking(EntradaRanking *ranking, int quantidade);
void liberarRanking(EntradaRanking *ranking);

//  Funções de Jogador 
void inicializarJogador(Jogador *jogador);
void exibirStatusJogador(Jogador jogador);
void exibirResumoFinal(Jogador jogador);
char* obterTituloFinal(int pontuacao);

//  Funções de Narrativa e Eventos 
void inicializarEventos(Evento *eventos);
void exibirEvento(Evento evento, int numeroCapitulo);
int executarEvento(Evento evento, Jogador *jogador);

// Funções de Interface e Menu 
void exibirMenuPrincipal();
void exibirCabecalho();
void limparBuffer();
void pausar();

// Funções auxiliares com vetores e matrizes 
void preencherMatrizSalas(char salas[][20], int linhas);
void exibirMapaSalas(char salas[][20], int linhas);
void inicializarAcademia(Academia *academia);

#endif // FUNCOES_H
