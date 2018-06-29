# Aluno : Vinicius Carloto Carnelocce #
# Matrícula : 201600560546 #
# Makefile #

deps_t2 = t3.o arquivo.o misc.o geometricas.o functions.o
cc = gcc -ansi -pedantic -g -lm -Wall

siguel : $(deps_t2)
	$(cc) $(deps_t2) -lm -o siguel

t3.o : t3.c
	$(cc) -c t3.c -lm

arquivo.o : arquivo.c
	$(cc) -c arquivo.c -lm

misc.o : misc.c
	$(cc) -c misc.c -lm

geometricas.o : geometricas.c
	$(cc) -c geometricas.c -lm

functions.o : functions.c
	$(cc) -c functions.c -lm

clean :
	rm -f *.o
