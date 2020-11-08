run: bst
	./bst

bst: TreeType.o QueType.o TreeDr.o
	g++ -Wall -ggdb -O0 -pedantic-errors -o bst TreeType.o QueType.o TreeDr.o 

TreeType.o: TreeType.h TreeType.cpp
	g++ -g -c TreeType.cpp

QueType.o: QueType.h QueType.cpp
	g++ -g -c QueType.cpp

TreeDr.o: TreeDr.cpp
	g++ -g -c TreeDr.cpp

clean:
	rm -f *.o bst