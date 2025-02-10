all: arvore_abb.o main.o
	clear

	gcc arvore_abb.o main.o -o prog
	
	./prog

arvore_abb.o: arvore_abb.c
	gcc -c arvore_abb.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog