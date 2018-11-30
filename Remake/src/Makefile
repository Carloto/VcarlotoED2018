# Aluno : Vinicius Carloto Carnelocce #
# Matrícula : 201600560546 #
# Makefile #

deps_siguel = main.o basicshapes.o circle.o rectangle.o miscfunctions.o filehandling.o genericlist.o
cc = gcc -fstack-protector-all -std=c99 -pedantic -g -Wall

siguel : $(deps_siguel)
	$(cc) $(deps_siguel) -lm -o siguel

main.o : main.c
	$(cc) -c main.c -lm

basicshapes.o : basicshapes.c
	$(cc) -c basicshapes.c -lm

circle.o : circle.c
	$(cc) -c circle.c -lm

rectangle.o : rectangle.c
	$(cc) -c rectangle.c -lm

miscfunctions.o : miscfunctions.c
	$(cc) -c miscfunctions.c -lm

filehandling.o : filehandling.c
	$(cc) -c filehandling.c -lm

genericlist.o : genericlist.c
	$(cc) -c genericlist.c -lm

clean :
	rm -f *.o
