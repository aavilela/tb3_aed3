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

#ifndef TAB_HASH_H
#define TAB_HASH_H

#define TAM_BLOCO 3
#define NUM_INICIAL_BLOCOS 10

#define OFFSET_INDICE 0

// Todos ponteiros do tipo FILE usam o prefixo 'f'
// Ponteiro para o arquivo de dados
FILE *fDados; 
// Ponteiro para o arquivo de índice de identidade
FILE *fIdent; 
// Ponteiro para o arquivo de índice de matrícula
FILE *fMat; 

// Nome do ArqDados que será recebido na linha de comando
char nomeDados[128]; 
char nomeIdent[128];
char nomeMat[128];

// Cabeçalho do arquivo de dados
int *NUM_REGS;
int *NUM_REGS_VALIDOS;

// Tipo da chave
typedef char Chave[15]; 

// Item a ser utilizado dentro dos índices
typedef struct Item
{
	Chave chave;
	int RRN_dados;
} Item;

typedef struct Bloco
{
	Item Itens[TAM_BLOCO];
} Bloco;

#endif // TAB_HASH_H
