CC = gcc -g

lexico: lex.yy.o
	$(CC) -o $@ $^

lex.yy.o: lex.yy.c
	$(CC) -c -o $@ $<

lex.yy.c: lexico.l
	flex lexico.l