
mainl: main.o linkedlist.o
	gcc -o mainl main.o linkedlist.o 

mainl.o: main.c src/linkedlist/linkedlist.h
	gcc -c main.c

nfa.o: nfa.c nfa.h
	gcc -c nfa.c

linkedlist.o: src/linkedlist/linkedlist.c src/linkedlist/linkedlist.h
	gcc -c src/linkedlist/linkedlist.c

digraph.o: src/digraph/digraph.c src/digraph/digraph.h
	gcc -c src/digraph/digraph.c

clean:
	rm -f *.o mainl