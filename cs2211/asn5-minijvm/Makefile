all:	minijvm.o mjava

test:	mjava
	- ./mjava testfiles/test1
	- ./mjava testfiles/test2
	- ./mjava testfiles/test3
	- ./mjava testfiles/test4
	- ./mjava testfiles/test5
	- ./mjava testfiles/test6
	- ./mjava testfiles/test7
	- ./mjava testfiles/test8

test1:	mjava
	- ./mjava testfiles/test1

test2:	mjava
	- ./mjava testfiles/test2

test3:	mjava
	- ./mjava testfiles/test3

test4:	mjava
	- ./mjava testfiles/test4

test5:  mjava
	- ./mjava testfiles/test5

test6:  mjava
	- ./mjava testfiles/test6

test7:	mjava
	- ./mjava testfiles/test7

test8:	 mjava
	- ./mjava testfiles/test8

minijvm.o:	 minijvm.c
	gcc -I include -c minijvm.c

mjava:	minijvm.o
	gcc -L lib -o mjava minijvm.o -ladt

clean:
	-rm minijvm.o mjava

