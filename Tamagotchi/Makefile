CC = gcc
FLAGS = -ggdb -Wall -Wextra -pedantic -std=c11
 

OPTIMIZATIONS = -03
OBJECTS = main.o tamagotchi.o sprites.o
EXECUTABLE = -o tamagotchi



main: main.o tamagotchi.o sprites.o
	gcc $(EXECUTABLE) $(OBJECTS) $(FLAGS) 
	

main.o: main.c
	gcc -c main.c $(FLAGS)

tamagotchi.o: tamagotchi.c 
	gcc -c tamagotchi.c $(FLAGS)

sprites.o: sprites.c 
	gcc -c sprites.c $(FLAGS)

clean:
	rm *.o tamagotchi




