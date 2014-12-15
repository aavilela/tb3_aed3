# Digite apenas 'make para compilar o programa
# e 'make clean' para remover os arquivos gerados no direrório
SisAlunos: tab_hash.o cliente.o aluno.o
	gcc -g aluno.c cliente.c tab_hash.c -o SisAlunos

tab_hash.o: tab_hash.h
aluno.o: aluno.h

.PHONY: clean
clean:
	rm -f Arqui* SisAlunos *.o
