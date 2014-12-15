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

#include "aluno.h"
#include "tab_hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recebe um Aluno e grava no arquivo de dados na posição obtida pelo RRN_dados
int EscreveAluno(Aluno *aluno, int RRN_dados)
{
	fseek(fDados, OFFSET_DADOS + RRN_dados*sizeof(Aluno), SEEK_SET);
	fwrite(aluno, sizeof(Aluno), 1, fDados);

	// Verifica se houve erro ao escreve o aluno no arquivo de dados
	if(ferror(fDados)) printf("Falha ao escrever aluno\n");

	free(aluno);
}

// Recebe um RRN do aluno no arquivo de dados e o carrega 
// para a memória principal
Aluno* CarregaAluno(int RRN_dados)
{
	Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
	rewind(fDados);
	fseek(fDados, OFFSET_DADOS + RRN_dados*sizeof(Aluno), SEEK_SET);
	fread(aluno, sizeof(Aluno), 1, fDados);
	return (Aluno *)aluno;
}

// Recebe um Aluno e imprime seus dados
void ImprimeAluno(Aluno *A)
{
	printf("%s %s %s %s %.2lf\n", A->Nome, A->Identidade, A->CPF, A->Matricula, A->CRA);
}

// Imprime todos os alunos válidos (não excluídos) do arquivo de dados
void ImprimeTodosAlunos()
{
	int i;
	Aluno *A;
	for(i = 0; i < *NUM_REGS; i++)
	{
		A = CarregaAluno(i);
		// Verifica se dado aluno é válido
		if(A->Nome[0] != '#')
			ImprimeAluno(A);
	}
}
