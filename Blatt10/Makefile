CC = gcc
FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
 
OBJECTS = blatt10_alp.o 
EXECUTABLE = -o blatt10_alp



blatt10_alp: blatt10_alp.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) 
	./blatt10_alp

blatt10_alp.o: blatt10_alp.c
	gcc -c blatt10_alp.c $(FLAGS)