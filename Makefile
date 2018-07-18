main: main.o digraph.o linkedlist.o
	gcc -std=c99 -o main main.o digraph.o linkedlist.o

main.o: main.c src/linkedlist/linkedlist.h src/digraph/digraph.h
	gcc -std=c99 -c main.c

nfa.o: nfa.c nfa.h
	gcc -std=c99 -c nfa.c

linkedlist.o: src/linkedlist/linkedlist.c src/linkedlist/linkedlist.h
	gcc -std=c99 -c src/linkedlist/linkedlist.c

digraph.o: src/digraph/digraph.c src/digraph/digraph.h linkedlist.o
	gcc -std=c99 -c src/digraph/digraph.c

clean:
	rm -f *.o main

test_digraph: test_digraph.o digraph.o linkedlist.o
	gcc -std=c99 -o test_digraph test_digraph.o digraph.o linkedlist.o

test_digraph.o : src/digraph/test_digraph.c src/digraph/digraph.h src/linkedlist/linkedlist.h
	gcc -std=c99 -c src/digraph/test_digraph.c