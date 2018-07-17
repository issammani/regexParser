main: main.o digraph.o
	gcc -o main main.o digraph.o 

main.o: main.c src/linkedlist/linkedlist.h
	gcc -c main.c

nfa.o: nfa.c nfa.h
	gcc -c nfa.c

linkedlist.o: src/linkedlist/linkedlist.c src/linkedlist/linkedlist.h
	gcc -c src/linkedlist/linkedlist.c

digraph.o: src/digraph/digraph.c src/digraph/digraph.h linkedlist.o
	gcc -c src/digraph/digraph.c

clean:
	rm -f *.o main