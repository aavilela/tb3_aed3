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
#include <string.h>

int RESULTADO = FALHA;

int EscreveAluno(Aluno *aluno, int RRN_dados)
{
	fseek(fDados, OFFSET_DADOS + RRN_dados*sizeof(Aluno), SEEK_SET);
	fwrite(aluno, sizeof(Aluno), 1, fDados);

	// Verifica se houve erro ao escreve o aluno no arquivo de dados
	if(ferror(fDados)) printf("Falha ao escrever aluno\n");

	free(aluno);
}

Aluno *CarregaAluno(int RRN_dados)
{
	Aluno *aluno = (Aluno *) malloc(sizeof(Aluno));
	rewind(fDados);
	fseek(fDados, OFFSET_DADOS + RRN_dados*sizeof(Aluno), SEEK_SET);
	fread(aluno, sizeof(Aluno), 1, fDados);
	return aluno;
}

void ImprimeAluno(Aluno *A)
{
	printf("%s %s %s %s %.2lf\n", A->Nome, A->Identidade, A->CPF, A->Matricula, A->CRA);
}

void ImprimeTodosAlunos()
{
	int i;
	Aluno *A;
	for(i = 0; i < *NUM_REGS; i++)
	{
		A = CarregaAluno(i);
		if(A->Nome[0] != '#')
			ImprimeAluno(A);
	}
}

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
		//
		*NUM_REGS = 0;
		*NUM_REGS_VALIDOS = 0;

		// Criando e inicializando a tabela hash
		Bloco *TabHash = (Bloco *) calloc(NUM_INICIAL_BLOCOS, sizeof(Bloco));
		if(!TabHash) 
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
		// Abre os arquivos de índice
		fIdent = fopen(nomeIdent, "r+b");
		fMat = fopen(nomeMat, "r+b");
		if(fIdent == NULL) printf("NULL\n");
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
int BuscaBloco(FILE *fp, int chave, int *dx)
{
	int px = Hash(chave);
	// Bloco que contem um registro deletado (-2)
	if(dx != NULL) *dx = -1;	
	Bloco *B = (Bloco *) malloc(sizeof(Bloco));
	char str[32];
	sprintf(str, "%d", chave);

	int sair = 0;
	while(!sair)
	{
		B = CarregaBloco(fp, px);

		// Procura dentro do bloco
		int i;
		for(i = 0; i < TAM_BLOCO; i++)
		{
			if(B->Itens[i].RRN_dados == -2 && dx != NULL && *dx == -1)
			{
				*dx = px;
			}
			if(!strcmp(B->Itens[i].chave, str) || B->Itens[i].RRN_dados == -1) 
			{
				sair = 1;
				return px;
			}
		}
		px++;
	}
}

void BuscaRegistro(FILE *fp, int chave)
{
	
	char str[20];
	sprintf(str, "%d", chave);
	printf("%s\n",str);

	int px = BuscaBloco(fp, chave, NULL);
	Bloco *B = CarregaBloco(fp, px);

	int i;
	for(i = 0; i < TAM_BLOCO - 1 && strcmp(B->Itens[i].chave, str) != 0; i++);

	Aluno *A = CarregaAluno(B->Itens[i].RRN_dados);

	ImprimeAluno(A);

	free(A);
}

int Insere(Aluno *aluno)
{
	int dx;
	// Convertendo a matricula para um int
	int mat = strtol(aluno->Matricula, (char **)NULL, 10);
	// índice do bloco em matrícula a chave possivelmente será inserida
	int pxm = BuscaBloco(fMat, mat, &dx);
	// Carregagando o bloco de matrícula de índice pxm

	if(dx != -1) pxm = dx;
	Bloco *bm = CarregaBloco(fMat, pxm);

	// Verifica se a chave já foi inserida
	int i;
	for( i = 0; i < TAM_BLOCO; i++)
	{
		if(strcmp(bm->Itens[i].chave, aluno->Matricula) == 0)
		{
			RESULTADO = FALHA;
		       	return;
		}
	}

	// Convertendo a identidade para um int
	int ident = strtol(aluno->Identidade, (char **)NULL, 10);
	int pxi = BuscaBloco(fIdent, ident, &dx);

	if(dx != -1) pxi = dx;
	Bloco *bi = CarregaBloco(fIdent, pxi);

	EscreveAluno(aluno, *NUM_REGS); 

	// Procurando a posição a inserir
	for(i = 0; i < TAM_BLOCO && bm->Itens[i].RRN_dados != -1 && bm->Itens[i].RRN_dados != -2 ; i++);
	strncpy(bm->Itens[i].chave, aluno->Matricula, sizeof(aluno->Matricula));
	bm->Itens[i].RRN_dados = *NUM_REGS;
	EscreveBloco(fMat, bm, pxm);

	for(i = 0; i < TAM_BLOCO && bi->Itens[i].RRN_dados != -1 && bi->Itens[i].RRN_dados != -2; i++);
	strncpy(bi->Itens[i].chave, aluno->Identidade, sizeof(aluno->Identidade));
	bi->Itens[i].RRN_dados = *NUM_REGS;
	EscreveBloco(fIdent, bi, pxi);

	// Incrementando o número de registros
	(*NUM_REGS)++;
	RESULTADO = SUCESSO;
}

// fp1 é o arquivo que irá verificar primeiro se a
// chave já foi adicionada, fp2 é o outro
void Remove(FILE *fp1, FILE *fp2, int chave)
{
	
	int achou = 0;
	char str[20];
	sprintf(str, "%d", chave);

	int px1 = BuscaBloco(fp1, chave, NULL);

	Bloco *b1 = CarregaBloco(fp1, px1); ;

	int RRN_dados;
	
	int i;
	for(i = 0; i < TAM_BLOCO && strcmp(str, b1->Itens[i].chave); i ++);
	
	if(i < TAM_BLOCO)
	{
		achou = 1;
		RRN_dados = b1->Itens[i].RRN_dados;
		b1->Itens[i].chave[0] = '#';
		b1->Itens[i].RRN_dados = -2;
	}

	if(!achou)
	{
		RESULTADO = FALHA;
		return;
	}
	
	Aluno *A = CarregaAluno(RRN_dados);
	
	if(fp2 == fIdent) chave = strtol(A->Identidade, (char **)NULL, 10);
	else if(fp2 == fMat) chave = strtol(A->Matricula, (char **)NULL, 10);

	int px2 = BuscaBloco(fp2, chave, NULL);

	Bloco *b2 = CarregaBloco(fp2, px2);

	sprintf(str, "%d", chave);
	
	for(i = 0; i < TAM_BLOCO && strcmp(str, b2->Itens[i].chave); i ++);
	
	if(i < TAM_BLOCO)
	{
		b2->Itens[i].chave[0] = '#';
		b2->Itens[i].RRN_dados = -2;
	}

	A->Nome[0] = '#';

	EscreveAluno(A, RRN_dados);
	EscreveBloco(fp1, b1, px1);
	EscreveBloco(fp2, b2, px2);
}

void Atualizar(FILE *fp1, FILE *fp2, char *strChave, Aluno *A)
{
	int chave = strtol(strChave, (char **)NULL, 10);

	Remove(fp1, fp2, chave);
	Insere(A);
}

void ImprimeTab(FILE *fp)
{
	int i, j;
	Bloco *B;
	for(i = 0; i < NUM_INICIAL_BLOCOS; i++)
	{
		B = CarregaBloco(fp, i);
		
		printf("[");
		for(j = 0; j < TAM_BLOCO ; j++)
		{
			if(B->Itens[j].RRN_dados != -1 && B->Itens[j].RRN_dados != -2) printf("%s,", B->Itens[j].chave);
			printf("%d", B->Itens[j].RRN_dados);
			if(j != TAM_BLOCO - 1) printf("|");
		}
		printf("]\n");
		free(B);
	}
}

void ImprimeResultado()
{
	if(RESULTADO == SUCESSO) printf("SUCESSO\n"); else printf("FALHA\n");
}
