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
 * IDE/Editor de texto: VIM
 * Sistema Operacional Ubuntu 14.04 LTS
 */

#include "tab_hash.h"

// Gerencia a abertura de arquivos
void AbreArquivos()
{
}

// Inicializa a tabela hash
void InicializaTab(Bloco *bloco, int tamBloco, int numBlocos)
{
	int i, j;
	for(i = 0; i < numBlocos; i++)
	{
		for(j = 0; j < tamBloco; j++)
		{
			bloco[i].Itens[j].RRN_registro = -1;
		}
	}
}
