# Aluno : Vinicius Carloto Carnelocce e Luca Biagini#
# Matrícula : 201600560546 // 201600560466 #
# Makefile #

deps_siguel = main.o basicshapes.o circle.o rectangle.o miscfunctions.o filehandling.o genericlist.o btree.o cidade.o closestpair.o color.o estabelecimento.o hidrante.o moradia.o pessoa.o quadra.o query.o semaforo.o tipoestab.o torre.o auxfig.o carro.o grafo.o linkedist.o ponto.o
cc = gcc -fstack-protector-all -std=c99 -pedantic -g -Wall `pkg-config --cflags --libs gtk+-2.0`

siguel : $(deps_siguel)
	$(cc) $(deps_siguel) -lm -o siguel

main.o : main.c
	$(cc) -c main.c -lm `pkg-config --libs gtk+-2.0`

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

btree.o : btree.c
	$(cc) -c btree.c -lm

cidade.o : cidade.c
	$(cc) -c cidade.c -lm

closestpair.o : closestpair.c
	$(cc) -c closestpair.c -lm

color.o : color.c
	$(cc) -c color.c -lm

estabelecimento.o : estabelecimento.c
	$(cc) -c estabelecimento.c -lm

hidrante.o : hidrante.c
	$(cc) -c hidrante.c -lm

moradia.o : moradia.c
	$(cc) -c moradia.c -lm

pessoa.o : pessoa.c
	$(cc) -c pessoa.c -lm

quadra.o : quadra.c
	$(cc) -c quadra.c -lm

query.o : query.c
	$(cc) -c query.c -lm

semaforo.o : semaforo.c
	$(cc) -c semaforo.c -lm

tipoestab.o : tipoestab.c
	$(cc) -c tipoestab.c -lm

torre.o : torre.c
	$(cc) -c torre.c -lm

auxfig.o : auxfig.c
	$(cc) -c auxfig.c -lm

carro.o : carro.c
	$(cc) -c carro.c -lm

grafo.o : grafo.c
	$(cc) -c grafo.c -lm

linkedist.o : linkedist.c
	$(cc) -c linkedist.c -lm

ponto.o : ponto.c
	$(cc) -c ponto.c -lm

	
clean :
	rm -f *.o
