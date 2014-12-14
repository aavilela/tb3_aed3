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
#include "aluno.h"

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
			//InsereAluno(aluno);
			// Insere a matrícula do aluno no índice de matrícula
			//InsereIndice(fMat, aluno->Matricula, *RRN_REGISTROS, RAIZ_MAT, RRN_PAGINAS_MAT);
			// Insere a identeidade do aluno no índice de identeidade
			//InsereIndice(fIdent, aluno->Identidade, *RRN_REGISTROS, RAIZ_IDENT, RRN_PAGINAS_IDENT);
			// Imprime resultado da operação ( FALHA OU SUCESSO)
			//ImprimeResultado();
		} // Operação Remover: remove um registro a partir de matrícula ou identidade
		else if(!strcmp(opcao, "REM"))
		{
			scanf("%s", opcao);
			if(!strcmp(opcao, "ID"))
			{
			}
			else if (!strcmp(opcao, "MAT"))
			{	
			}
		}
		// Operação Buscar: busca a chave na árvore especificada (ID para índice, MAT para matrícula)
		// e imprime as informações do aluno que contém aquela chave
		else if(!strcmp(opcao, "BUS"))
		{
			scanf("%s", opcao);
			if(!strcmp(opcao, "ID"))
			{
				// Busca a identidade no índice, se encontrado imprime em seguida
				// Caso contrário imprime FALHA
			}
			else if (!strcmp(opcao, "MAT"))
			{	
				// Busca a identidade no índice, se encontrado imprime em seguida
				// Caso contrário imprime FALHA
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
				// Imprime a árvore B com índices identidade
				//ImprimeIndice(fIdent, *RAIZ_IDENT, 0);
			}
			else if (!strcmp(opcao, "MAT"))
			{	
				// Imprime a árvore B com índices matrícula
				//ImprimeIndice(fMat, *RAIZ_MAT, 0);
			}
		}
		
       	}while(strcmp(opcao, "FIM"));

	Fecha();

	return 0;
}
