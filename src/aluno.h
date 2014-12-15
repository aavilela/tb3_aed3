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

#ifndef ALUNOS_H
#define ALUNOS_H

// Estrutura Aluno
typedef struct Aluno
{
	char Nome[15];
	char Identidade[15];
	char CPF[15];
	char Matricula[15];
	double CRA;
} Aluno;

// Protótipos
int EscreveAluno(Aluno*, int);
Aluno *CarregaAluno(int);
void ImprimeAluno(Aluno *A);
void ImprimeTodosAlunos();

#endif //ALUNOS_H
