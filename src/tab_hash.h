/*
 * Universidade Federal de Lavras - UFLA
 * Algorítmos e Estruturas de Dados III
 * Professor: Dilson Lucas Pereira
 * Alunos: Alexandre Alencar Vilela
 * 	   William Odair Lima
 * Turma: 10A
 * 
 * Trabalho Prático: Sistema de manipulação de cadastros de alunos, indexado por Tabela Hash
 *
 * Compilador: GCC
 * IDE: Nenhuma
 * Sistema Operacional Ubuntu 14.04 LTS
 */

#include <stdio.h>

#include "aluno.h"

#ifndef TAB_HASH_H
#define TAB_HASH_H

#define TAM_BLOCO 3
#define NUM_INICIAL_BLOCOS 10

#define OFFSET_INDICE 0
#define OFFSET_DADOS sizeof(int)*2

#define SUCESSO 1
#define FALHA 2

// Todos ponteiros do tipo FILE usam o prefixo 'f'
// Ponteiro para o arquivo de dados
FILE *fDados; 
// Ponteiro para o arquivo de índice de identidade
FILE *fIdent; 
// Ponteiro para o arquivo de índice de matrícula
FILE *fMat; 

// Strings que receberam o nome dos arquivos fornecidos
char nomeDados[128]; 
char nomeIdent[128];
char nomeMat[128];

// Cabeçalho do arquivo de dados
int *NUM_REGS;
int *NUM_REGS_VALIDOS;

// Variavel utilizada para apresentar o resultado das operações
int RESULTADO;

// Tipo da chave
typedef char Chave[15]; 

// Item a ser utilizado dentro dos índices
typedef struct Item
{
	Chave chave;
	// RRN para o arquivo de dados
	int RRN_dados;
} Item;

// Bloco da tabela hash
typedef struct Bloco
{
	Item Itens[TAM_BLOCO];
} Bloco;

// Protótipos
// Está contida no arquivo de implementação uma
// descrição mais detalhada de cada função
void EscreveBloco(FILE*, Bloco*, int);
Bloco *CarregaBloco(FILE*, int);

void EscreveTab(FILE*, Bloco*);
void InicializaTab(Bloco*, int, int);

void EscreveCabecalho();
void LeCabecalho();

void AbreArquivos();
void Fecha();

int Hash(int);
int BuscaBloco(FILE*, int, int*);
void BuscaRegistro(FILE*, int);
int Insere(Aluno*);
void Remove(FILE*, FILE*, int);
void Atualizar(FILE*, FILE*, char*, Aluno*);
void ImprimeTab(FILE*);
void ImprimeResultado();

#endif // TAB_HASH_H
