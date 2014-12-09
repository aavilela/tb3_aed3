/*
 * Universidade Federal de Lavras - UFLA
 * Algorítmos e Estruturas de Dados III
 * Professor: Dilson Lucas Pereira
 * Alunos: Alexandre Alencar Vilela
 * 	   William Odair Lima
 * Turma: 10A
 * 
 * Trabalho Prático: Sistema de manipulação de cadastros de alunos, indexado por uma Tabela Hash
 *
 * Compilador: GCC
 * IDE/Editor de texto: VIM
 * Sistema Operacional Ubuntu 14.04 LTS
 */


#ifndef TAB_HASH_H
#define TAB_HASH_H

#define TAM_BLOCO 3
#define NUM_INICIAL_BLOCOS 10

FILE *ArqDados;
FILE *ArqMat;
FILE *ArqIdent;

char *nomeArqDados;

typedef char[15] Chave;

typedef struct Item
{
	Chave chave;
	int RRN_registro;
}

typedef struct Bloco
{
	Item Itens[TAM_BLOCO];
}

#endif // TAB_HASH_H
