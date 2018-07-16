
main: main.o nfa.o
	gcc -o main main.o nfa.o

main.o: main.c nfa.h
	gcc -c main.c

nfa.o: nfa.c nfa.h
	gcc -c nfa.c

clean:
	rm -f *.o main 