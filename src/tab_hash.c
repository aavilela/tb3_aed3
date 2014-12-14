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

#include "tab_hash.h"

#include <stdio.h>
#include <stdlib.h>

// Escreve um bloco em um arquivo de índice 
void EscreveBloco(FILE *fp, Bloco *B, int RRN_bloco)
{
	fseek(fp, OFFSET_INDICE + RRN_bloco*sizeof(Bloco), SEEK_SET);
	fwrite(B, sizeof(Bloco), 1,fp);
	free(B);
}

Bloco *CarregaBloco(FILE* fp, int RRN_bloco)
{
	Bloco *B = (Bloco *) malloc(sizeof(Bloco));
	fseek(fp, OFFSET_INDICE + RRN_bloco*sizeof(Bloco), SEEK_SET);
	fread(B, sizeof(Bloco), 1, fp);
	return B;
}

// Escreve a tabela inteira no arquivo
void EscreveTab(FILE *arq, Bloco *tab)
{
	int i;
	for(i = 0; i < NUM_INICIAL_BLOCOS; i++)
	{
		fseek(arq, OFFSET_INDICE + i*sizeof(Bloco), SEEK_SET);
		fwrite(&(tab[i]), sizeof(Bloco), 1,arq);
	}
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

// Lê o cabeçalho do arquivo de dados
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
	if( (fDados = fopen(nomeDados, "r+b")) == NULL)
	{
		// Ponteiros para os arquivos
		fDados = fopen(nomeDados, "w+b");
		fIdent = fopen(nomeIdent, "w+b");
		fMat = fopen(nomeMat, "w+b");

		// Inicializando as informações do cabeçalho
		*NUM_REGS = 0;
		*NUM_REGS_VALIDOS = 0;

		// Criando e inicializando a tabela hash
		Bloco *TabHash = (Bloco *) calloc(NUM_INICIAL_BLOCOS, sizeof(Bloco));
		if( !TabHash) 
		{
			printf("Erro! Memoria para TabHash nao alocada!\n");
			exit(0);
		}

		InicializaTab(TabHash, TAM_BLOCO, NUM_INICIAL_BLOCOS);

		// Escrevendo a tabela hash já inicializada nos arquivos de índice
		EscreveTab(fIdent, TabHash);
		EscreveTab(fMat, TabHash);

		free(TabHash);
		// Escrevendo o cabeçalho
		EscreveCabecalho();
	}
	else 
	{
		printf("a\n");
		// Abre os arquivos de índice
		fIdent = fopen(nomeIdent, "r+b");
		fMat = fopen(nomeMat, "r+b");
		// Lê o cabeçalho para realizar as operações posteriores
		LeCabecalho();
	}
}

// Salva o cabeçalho e fecha os arquivos
void Fecha()
{
	EscreveCabecalho();
	fclose(fDados);
	fclose(fIdent);
	fclose(fMat);
}

// Função hash que determina o bloco onde a chave possivelmente está
int Hash(int chave)
{
	return chave % NUM_INICIAL_BLOCOS;
}

// Busca pelo bloco onde está a chave
int BuscaBloco(FILE *fp, int chave)
{
	int RRN_bloco = Hash(chave);
	int RRN_dBloco = -1;
	Bloco *B = (Bloco *) malloc(sizeof(Bloco));

	int sair = 0;
	while(!sair)
	{
		B = CarregaBloco(fp, RRN_bloco);
		int i;
		for(i = 0; i < TAM_BLOCO; i++)
		{
			if(B->Itens[i].RRN_dados == -2)
				RRN_dBloco = RRN_bloco;
			if(B->Itens[i].RRN_dados == chave || B->Itens[i].RRN_dados == -1) 
			{
				sair = 1;
				continue;
			}
			else 
				RRN_bloco++;
		}
	}
}

