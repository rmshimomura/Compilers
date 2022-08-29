CC = gcc -g

l7e2: lex.yy.o
	$(CC) -o $@ $^

lex.yy.o: lex.yy.c
	$(CC) -c -o $@ $<

lex.yy.c: automata.l
	flex automata.l