/*
 * Universidade Federal de Lavras - UFLA
 * Algorítmos e Estruturas de Dados III
 * Professor: Dilson Lucas Pereira
 * Alunos: Alexandre Alencar Vilela
 * 	   William Odair Lima
 * Turma: 10A
 * 
 * Trabalho Prático: Sistema de manipulação de cadastros de alunos, indexado por árvore-B
 *
 * Compilador: GCC
 * IDE: Nenhuma
 * Sistema Operacional Ubuntu 14.04 LTS
 */

#include "tab_hash.h"

#include <stdio.h>
#include <stdlib.h>

char nomeIdent[] = "ArquivoAlunos_ID.dat";
char nomeMat[] = "ArquivoAlunos_MAT.dat";

// Escreve um bloco em um arquivo de índice 
void EscreveBloco(FILE *arq, Bloco *B, int RRN_bloco)
{
	fseek(arq, OFFSET_INDICE + RRN_bloco*sizeof(Bloco), SEEK_SET);
	fwrite(B, sizeof(Bloco), 1,arq);
	free(B);
}

// Escreve a tabela inteira no arquivo
void EscreveTab(FILE *arq, Bloco *tab)
{
	int i;
	//for(i = 0; i < NUM_INICIAL_BLOCOS; i++)
	//{
		fseek(arq, OFFSET_INDICE , SEEK_SET);
		fwrite(tab, sizeof(Bloco)*NUM_INICIAL_BLOCOS, 1,arq);

		//EscreveBloco(arq, &(tab[i]), i);
	//}
	//free(tab);
}

// Inicializa a tabela hash
void InicializaTab(Bloco *tab, int tamBloco, int numBlocos)
{
	int i, j;
	for(i = 0; i < numBlocos; i++)
	{
		for(j = 0; j < tamBloco; j++)
		{
			tab[i].Itens[j].RRN_dados = -1;
		}
	}
}

// Escreve o cabeçalho no disco
void EscreveCabecalho()
{
	rewind(fDados);
	fwrite(NUM_REGS, sizeof(int), 1, fDados);
	fwrite(NUM_REGS_VALIDOS, sizeof(int), 1, fDados);
}

// Lê o cabeçalho do disco
void LeCabecalho()
{
	rewind(fDados);
	fread(NUM_REGS, sizeof(int), 1, fDados);
	fread(NUM_REGS_VALIDOS, sizeof(int), 1, fDados);
}

// Gerencia a abertura de arquivos
void AbreArquivos()
{
	// Cabeçalho do arquivo de dados
	NUM_REGS = malloc(sizeof(int));
	NUM_REGS_VALIDOS = malloc(sizeof(int));

	// Tenta abrir o arquivo caso já exista
	// Se não, cria novos arquivos para índice e um para dados
	if( fopen(nomeDados, "r+b") == NULL)
	{
		// Ponteiros para os arquivos
		fDados = fopen(nomeDados, "w+b");
		fIdent = fopen(nomeIdent, "w+b");
		fMat = fopen(nomeMat, "w+b");

		// Inicializando as informações do cabeçalho
		*NUM_REGS = 0;
		*NUM_REGS_VALIDOS = 0;

		// Criando e inicializando a tabela hash
		Bloco *TabHash = (Bloco *) malloc(sizeof(Bloco)*NUM_INICIAL_BLOCOS);
		InicializaTab(TabHash, TAM_BLOCO, NUM_INICIAL_BLOCOS);

		// Escrevendo a tabela hash já inicializada nos arquivos de índice
		EscreveTab(fIdent, TabHash);
		EscreveTab(fMat, TabHash);

		// Escrevendo o cabeçalho
		//EscreveCabecalho();
	}
	else 
	{
		fIdent = fopen(nomeIdent, "r+b");
		fMat = fopen(nomeMat, "r+b");
		LeCabecalho();
	}
}


