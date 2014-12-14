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
#include <stdlib.h>
#include <string.h>

#include "tab_hash.h"

int main(int argc, char *argv[])
{
	// Concatenando os nomes dos arquivos 
	snprintf(nomeDados, sizeof(nomeDados), "%s%s", argv[1], ".dat");
	snprintf(nomeIdent, sizeof(nomeIdent), "%s%s", argv[1], "_ID.dat");
	snprintf(nomeMat, sizeof(nomeMat), "%s%s", argv[1], "_MAT.dat");

	AbreArquivos();

	char opcao[4]; 

	do
	{
		// Lê a operação a ser executada
		scanf("%s", opcao);

		// Operação Inserir: Insere um aluno no arquivo de dados e sua matrícula e identidade
		// em seu repectivos índices
		if(!strcmp(opcao, "INS")) 
		{
			// String auxiliar para receber os informações de aluno
			char entrada[100];
			Aluno *aluno = malloc(sizeof(Aluno));
			scanf("%s", entrada);
			strcpy(aluno->Nome, entrada);
			scanf("%s", entrada);
			strcpy(aluno->Identidade, entrada);
			scanf("%s", entrada);
			strcpy(aluno->CPF, entrada);
			scanf("%s", entrada);
			strcpy(aluno->Matricula, entrada);
			scanf("%lf", &aluno->CRA);
			
			// Insere o aluno no arquivo de dados
			Insere(aluno);
			// Imprime resultado da operação ( FALHA OU SUCESSO)
			ImprimeResultado();
		} // Operação Remover: remove um registro a partir de matrícula ou identidade
		else if(!strcmp(opcao, "REM"))
		{
			scanf("%s", opcao);
			int chave;
			scanf("%d", &chave);
			if(!strcmp(opcao, "ID"))
			{
				Remove(fIdent, fMat, chave);
				ImprimeResultado();
			}
			else if (!strcmp(opcao, "MAT"))
			{	
				Remove(fMat, fIdent, chave);
				ImprimeResultado();
			}
		}
		// Operação Buscar: busca a chave na árvore especificada (ID para índice, MAT para matrícula)
		// e imprime as informações do aluno que contém aquela chave
		else if(!strcmp(opcao, "BUS"))
		{
			scanf("%s", opcao);
			if(!strcmp(opcao, "ID"))
			{
				int chave;
				scanf("%d", &chave);
				BuscaRegistro(fIdent, chave);
			}
			else if (!strcmp(opcao, "MAT"))
			{	
				int chave;
				scanf("%d", &chave);
				BuscaRegistro(fMat, chave);
			}
		}
		// Operação Atualizar: atualiza os dados de um aluno especificado
		else if(!strcmp(opcao, "ATU"))
		{
			scanf("%s", opcao);
			if(!strcmp(opcao, "ID"))
			{
			}
			else if (!strcmp(opcao, "MAT"))
			{	
			}
		}
		//
		else if(!strcmp(opcao, "EXI"))
		{
			scanf("%s", opcao);
			if(!strcmp(opcao, "ID"))
			{
				ImprimeTab(fIdent);
			}
			else if(!strcmp(opcao, "MAT"))
			{	
				ImprimeTab(fMat);
			}
			else if(!strcmp(opcao, "ALU"))
			{
				ImprimeTodosAlunos();
			}
		}
		
       	}while(strcmp(opcao, "FIM"));

	Fecha();

	return 0;
}
