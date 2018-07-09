# Aluno : Vinicius Carloto Carnelocce #
# Matrícula : 201600560546 #
# Makefile #

deps_t2 = t3.o arquivo.o misc.o geometricas.o functions.o quadra.o semaforo.o hidrante.o torre.o qryfunctions.o mergesort.o
cc = gcc -fstack-protector-all -std=c99 -pedantic -g -lm -Wall

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

quadra.o : quadra.c
	$(cc) -c quadra.c -lm

semaforo.o : semaforo.c
	$(cc) -c semaforo.c -lm

hidrante.o : hidrante.c
	$(cc) -c hidrante.c -lm

torre.o : torre.c
	$(cc) -c torre.c -lm

qryfunctions.o : qryfunctions.c
	$(cc) -c qryfunctions.c -lm

mergesort.o : mergesort.c
	$(cc) -c mergesort.c -lm

clean :
	rm -f *.o
